#!/bin/sh
cd /cave/CAVE2-scripts/vm

#Update the template config xml from that on head1
cp nodeconfigs/template.{xml,backup."$(date +%Y%m%d-%H%M%S)"}
virsh -c qemu:///system "dumpxml win10" > nodeconfigs/template.xml

#Run a script in current directory on all nodes
./all.sh ./vmconfigs.py

#Fix permissions
chown -R cave:users .

