#!/bin/bash

#Installed on head1
#Installed on nodes with command:
#tentakel "cd /cave/CAVE2-scripts/setup; ./kvm-install.sh"

#https://www.cyberciti.biz/faq/how-to-install-kvm-on-centos-7-rhel-7-headless-server/
#https://www.tuxfixer.com/install-and-configure-kvm-qemu-on-centos-7-rhel-7-bridge-vhost-network-interface/

yum install -y qemu-kvm libvirt libvirt-python libguestfs-tools virt-install virt-manager

systemctl enable libvirtd
systemctl start libvirtd

lsmod | grep -i kvm

#In CentOS 7, append the kernel command line parameters to the GRUB_CMDLINE_LINUX entry in 
#/etc/default/grub
sed -i 's/GRUB_CMDLINE_LINUX="[^"]*/& intel_iommu=on/' /etc/default/grub

#BIOS
#grub2-mkconfig -o /boot/grub2/grub.cfg

#UEFI
grub2-mkconfig -o /boot/efi/EFI/centos/grub.cfg


#Permissions: allow virtual machine managment by cave user
usermod -a -G kvm cave

#Append rule to /etc/polkit-1/rules.d/49-polkit-pkla-compat.rules
cat >> /etc/polkit-1/rules.d/49-polkit-pkla-compat.rules <<EOL

polkit.addRule(function(action, subject) {
    if (action.id == "org.libvirt.unix.manage" &&
        subject.isInGroup("kvm")) {
            return polkit.Result.YES;
        }
});
EOL

