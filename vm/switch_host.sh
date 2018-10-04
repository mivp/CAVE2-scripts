#!/bin/bash

#Get device IDs from config file
source "DEVICES"
echo "Switching Devices to HOST: " $DEV $ADEV

#Ensure no VM running
virsh list | grep "running"
FOUND=$? #Grep returns 1 if not found
if [ $FOUND -ne 1 ]
then
  echo "Virtual machines still running, aborted!"
  #Attempt to shutdown
  virsh shutdown win10
  exit
fi

#Release from vfio-pci
##??
echo > /sys/bus/pci/devices/${DEV}/driver_override
##??
echo 1 > /sys/bus/pci/devices/${DEV}/remove

#Previous method:
#echo $DEV > /sys/bus/pci/drivers/vfio-pci/unbind
#Re-attach to nvidia on host
#echo $DEV > /sys/bus/pci/drivers/nvidia/bind
sleep 0.2


echo 1 > /sys/bus/pci/rescan
sleep 0.2

#Check visible on host now
nvidia-smi

#Ready to start X server
#./x.sh
#./runX.sh

