To use physical disk
- import existing disk image
- Storage path /dev/sdd

When setting the VM up initially, there is a checkbox near the end to say you want to further config the VM before install, this is the only time you get a dropdown for the BIOS/UEFI and chipset(i440FX/Q35), did you make OVMF available? Perhaps it's not showing firmware dropdown like the chipset if it doesn't detect OVMF? There is an AUR package ovmf-git, use that? You may need to let qemu know about it in qemu.conf file, a guide or the wiki should cover this. It's been a while but I think that's what I did.


## UEFI firmware

To install the OVMF firmware, create the file `kraxel.repo` at `/etc/yum.repos.d/` with the following contents:

```
include=https://www.kraxel.org/repos/firmware.repo
```

Then install the firmware with `yum install edk2.git-ovmf-x64`.
:browse tabnew

To advertise UEFI in `libvirt`, add the following to `/etc/libvirt/qemu.conf`:

```
nvram = [
   "/usr/share/edk2.git/ovmf-x64/OVMF_CODE-pure-efi.fd:/usr/share/edk2.git/ovmf-x64/OVMF_VARS-pure-efi.fd"
]

```

### DRIVERS

/cave/CAVE2-scripts/setup/virtio-win-0.1.171.iso

mounted as CDROM IDE

### NETWORKING

1) Use bridge on bond0 - this works with static IPs, will need availale IPS and access to DHCP with addresses on CAVE2 vlan

Alternatively

2) Use "Specifiy shared device name"

virbr0

Device model

rtl8139

This provides dynamic IPs on the virbr0 subnet 192.168.100...

### MOVING MACHINE DEFINITION TO OTHER NODES

on head1 as cave:

virsh -c qemu:///system "dumpxml win10" > win10.xml

On n20 as cave:

virsh -c qemu:///system "define win10.xml"

#Install the variable store - just copy from where original vm defined (head1)
#ln -s /var/lib/libvirt/qemu/nvram/win10_VARS.fd
#win10_VARS.fd -> /var/lib/libvirt/qemu/nvram/win10_VARS.fd
scp win10_VARS.fd n20:/var/lib/libvirt/qemu/nvram/

virsh -c qemu:///system "start win10"

virsh -c qemu:///system "shutdown win10"

[cave@n20 setup]$ lspci |grep VGA
05:00.0 VGA compatible controller: NVIDIA Corporation GK104GL [Quadro K5000] (rev a1)
09:00.0 VGA compatible controller: NVIDIA Corporation GT218 [NVS 300] (rev a2)
82:00.0 VGA compatible controller: NVIDIA Corporation GK104GL [Quadro K5000] (rev a1)

#Attempt passthrough of GPU 0 (05:00) - must also passthrough Audio device (05:01) as all devices in group need to be passed and defined in the XML using virt-manager

 - define using virt-manager on head1
 - export XML
 - delete from head1 (will crash if started)

Update VM on n20:

virsh -c qemu:///system "define win10.xml"

virsh -c qemu:///system "start win10"

#Result: vm starts, startup messages appear on screens, but then goes blank
#appears to be running fine though but no video output via nvidia

#On n20, get ip and attempt to vnc

ip a
(virbr0 192.168.122.1)
nmap -sn 192.168.122.0/24

Nmap scan report for 192.168.122.246
Host is up (0.0011s latency).
MAC Address: 52:54:00:9C:C6:FF (QEMU Virtual NIC)
Nmap scan report for 192.168.122.1
Host is up.
Nmap done: 256 IP addresses (2 hosts up) scanned in 7.28 seconds

#???
https://askubuntu.com/questions/800279/vga-passthrough-with-qemu-and-kvm-nothing-on-screen
http://vfio.blogspot.com/2015/05/vfio-gpu-how-to-series-part-4-our-first.html

The GeForce card is nearly as easy, but we first need to work around some of the roadblocks Nvidia has put in place to prevent you from using the hardware you've purchased in the way that you desire (and by my reading conforms to the EULA for their software, but IANAL).  For this step we again need to run virsh edit on the VM.  Within the <features> section, remove everything between the <hyperv> tags, including the tags themselves.  In their place add the following tags:

    <kvm>
      <hidden state='on'/>
    </kvm>


Did above, failed, got rid of KVM tags but left the hyperv stuff out and now it works... not sure if necessary or if the shutdown/reboot alone was what fixed things
