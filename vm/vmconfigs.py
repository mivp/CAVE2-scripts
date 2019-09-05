#!/usr/bin/env python
import subprocess
import os
import socket

#Get our hostname
host = socket.gethostname()

#Just show the available cards
subprocess.call('lspci | grep NVIDIA', shell=True)

#Extract the PCI bus addresses of all NVidia GK* gpus (excludes the NVS300 and the audio device)
cmd = "lspci |grep GK.*GL | awk '{print $1;}'"
res = subprocess.check_output(cmd, shell=True)
lines = res.splitlines()
print(lines)

entry_template = """
    <hostdev mode='subsystem' type='pci' managed='yes'>
      <source>
        <address domain='0x0000' bus='0x{bus}' slot='0x{slot}' function='0x0'/>
      </source>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x{guestslot0:02x}' function='0x0'/>
    </hostdev>
    <hostdev mode='subsystem' type='pci' managed='yes'>
      <source>
        <address domain='0x0000' bus='0x{bus}' slot='0x{slot}' function='0x1'/>
      </source>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x{guestslot1:02x}' function='0x0'/>
    </hostdev>
"""
#bus 0x05
#slot 0x00
#guestslot = 0x09 0x0a 0x0b 0x0c
hostdevs = ""
devlist = ""
adevlist = ""
guest=9
for line in lines:
    #aa:bb.c ==> pci_0000_aa_bb_c
    pci = "pci_0000_%s_%s_%s" % (line[0:2], line[3:5], line[6])
    print("BUS",line[0:2])
    print("SLOT",line[0:4])
    print("GUESTSLOT ", hex(guest), hex((guest+1)))
    hostdevs += entry_template.format(bus=line[0:2], slot=line[3:5], guestslot0=guest, guestslot1=guest+1)
    guest += 2

    #Add to DEVLIST and ADEVLIST strings
    print(line[6])
    devlist += "0000:" + line + " "
    adevlist += "0000:" + line[0:5] + ".1 "

#Write the DEVICES_host file
content = """
#VFIO PCI passthrough devices

#Video devices
DEVLIST="{devs}"

#Associated HDMI Audio devices
ADEVLIST="{adevs}"
""".format(devs=devlist, adevs=adevlist)
fn = "nodeconfigs/DEVICES_" + host
with open(fn, 'w') as file:
  file.write(content)

print(hostdevs)

#Generate a mac address from the hostname
print(host)
if host[0] == 'n':
    #Node
    mac = '02:00:00:aa:bb:%02d' % int(host[1:])
else:
    #Head1
    mac = '02:00:00:aa:bb:00'

print("Generated MAC address: ", mac)


#Target strings to replace in template.xml
#    </video>
#<mac address='52:54:00:9c:c6:ff'/>
#      <source dev='bond0' mode='bridge'/>
import re

# Read in the file
with open("nodeconfigs/template.xml", 'r') as file :
    filedata = file.read()

# Replace the target strings
#filedata = filedata.replace("<mac address='[0-9a-f:]*'\/>", "<mac address='" + mac + "'/>")
filedata = re.sub("<mac address='[0-9a-f:]*'\/>", "<mac address='" + mac + "'/>", filedata)
if host != 'head1':
    #Only on nodes, replace bond0 with p2p2
    filedata = filedata.replace("dev='bond0'", "dev='p2p2'")
    #Insert host PCI devices (nodes only unless we allow head1 desktop to be killed)
    filedata = filedata.replace('</video>', '</video>\n' + hostdevs)

# Write the file out again
fn = "nodeconfigs/win10_" + host + ".xml"
with open(fn, 'w') as file:
  file.write(filedata)

#Update the VM definition
cmd = 'virsh -c qemu:///system "define ' + fn + '"'
subprocess.call(cmd, shell=True)

