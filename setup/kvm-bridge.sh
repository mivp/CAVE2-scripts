#!/bin/bash
#https://www.cyberciti.biz/faq/how-to-install-kvm-on-centos-7-rhel-7-headless-server/
#https://www.tuxfixer.com/install-and-configure-kvm-qemu-on-centos-7-rhel-7-bridge-vhost-network-interface/

#On head node, bridge to bond0, other nodes use p2p2
NWDEV=bond0
HOST=`hostname`
echo "HOST: " $HOST
if [ HOST != 'head1' ]
then
  NWDEV=p2p2
fi
echo "NWDEV: " $NWDEV

sed -i '$ a BRIDGE=br0' /etc/sysconfig/network-scripts/ifcfg-$NWDEV

cat > /etc/sysconfig/network-scripts/ifcfg-br0 <<EOL
DEVICE="br0"
# Get IP from DHCP server
BOOTPROTO="dhcp"
#IPV6INIT="yes"
#IPV6_AUTOCONF="yes"
ONBOOT="yes"
TYPE="Bridge"
DELAY="0"
EOL

#systemctl stop NetworkManager
#systemctl disable NetworkManager
#systemctl restart network

# - virt-manager : Delete default network vibr0
# - virt-manager : add interface : Bridge - br0 - start on boot, enabled, copy config, STP, delay 0


