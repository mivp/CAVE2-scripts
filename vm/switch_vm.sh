#!/bin/bash

#Get device IDs from config file
source "nodeconfigs/DEVICES_$HOSTNAME"
echo "$HOSTNAME Switching Devices to GUEST(VM): " $DEVLIST $ADEVLIST

#DO NOT RUN IN X
# Xorg shouldn't run.
if [ -n "$( ps -C X | grep X )" ];
then
  echo Killing X!
  killall X
  sleep 1.0
  #exit 1
fi

#Release from nvidia driver on host
for DEV in $DEVLIST; do
    echo $DEV
    echo $DEV > /sys/bus/pci/drivers/nvidia/unbind
    #Re-attach to vfio-pci for guest
    #echo $DEV > /sys/bus/pci/drivers/vfio-pci/bind
    #Also unbind from nouveau/nvidia_drm if attached (N10)
    #echo $DEV > /sys/bus/pci/devices/$DEV/driver/unbind
    sleep 0.2
    lspci -kn | grep -A 3 ${DEV:5:4}
done

echo 1 > /sys/bus/pci/rescan
sleep 0.2

#Check the GPU is gone from host
nvidia-smi

#Start the windows 10 vm
virsh -c qemu:///system "start win10"

