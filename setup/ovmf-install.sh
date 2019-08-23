#!/bin/bash

## UEFI firmware for KVM/Qemu

#(run as root)

#Installed on head1
#Installed on nodes with command:
#tentakel "cd /cave/CAVE2-scripts/setup; ./ovmf-install.sh"

#To install the OVMF firmware, create the file `kraxel.repo` at `/etc/yum.repos.d/` with the following contents:
#Append repo
cat > /etc/yum.repos.d/kraxel.repo <<EOL
include=https://www.kraxel.org/repos/firmware.repo
EOL

#Then install the firmware with `yum install edk2.git-ovmf-x64`.
yum install -y edk2.git-ovmf-x64

#To advertise UEFI in `libvirt`, add the following to `/etc/libvirt/qemu.conf`:
#(just append to end)
cat >> /etc/libvirt/qemu.conf <<EOL

#Enable OVMF for qemu uefi
nvram = [
   "/usr/share/edk2.git/ovmf-x64/OVMF_CODE-pure-efi.fd:/usr/share/edk2.git/ovmf-x64/OVMF_VARS-pure-efi.fd"
]

EOL

