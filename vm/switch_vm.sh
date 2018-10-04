#!/bin/bash

#Get device IDs from config file
source "DEVICES"
echo "Switching Devices to GUEST(VM): " $DEV $ADEV

#DO NOT RUN IN X
# Xorg shouldn't run.
if [ -n "$( ps -C X | grep X )" ];
then
  echo Don\'t run this inside Xorg!
  exit 1
fi

#killall X
#sleep 0.5

#Release from nvidia driver on host
echo $DEV > /sys/bus/pci/drivers/nvidia/unbind
#Re-attach to vfio-pci for guest
#echo $DEV > /sys/bus/pci/drivers/vfio-pci/bind
sleep 0.2

echo 1 > /sys/bus/pci/rescan
sleep 0.2

#Check the GPU is gone from host
nvidia-smi

#Start the windows 10 vm
virsh start win10

