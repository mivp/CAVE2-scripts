#!/bin/bash

#X already running? Don't run this again
if [ -n "$( ps -C X | grep X )" ];
then
  echo "X already running, no need to switch to host"
  exit
fi

#Get device IDs from config file
source "nodeconfigs/DEVICES_$HOSTNAME"
echo "$HOSTNAME Switching Devices to HOST: " $DEVLIST $ADEVLIST

#Ensure no VM running
#Grep returns 1 if not found
virsh -c qemu:///system "list" | grep "running"
if [ $? -ne 1 ]
then
  echo "Virtual machines still running, attempting shutdown"
  # Wait until all are shut down or timeout.
  TIMEOUT=180
  for sec in $(seq 1 $TIMEOUT); do
    #Attempt to shutdown
    virsh -c qemu:///system "shutdown win10"

    #Check for running
    #virsh -c qemu:///system "list" | grep "running"
    #if [ $? -eq 1 ]
    virsh -c qemu:///system "list --all" | grep "shut off"
    if [ $? -eq 0 ]
    then
      break
    fi
    echo "Virtual machine still running, waiting for shutdown to finish! $sec"
    # Pause 1 sec
    sleep 1
  done

  #Don't continue the script if timeout reached
  if [ $sec -ge ${TIMEOUT} ]
  then
    echo "TIMEOUT, vm shutdown failed on ${HOSTNAME}"
    #virsh -c qemu:///system "destroy win10"
    #./switch_host.sh
    exit
  fi
  echo "Shutdown succeeded"
  # Pause, just in case
  sleep 3
fi

##############
echo "SWITCHING DEVICES"
#exit

#Release from vfio-pci
for DEV in $DEVLIST; do
    echo $DEV
    ##??
    echo > /sys/bus/pci/devices/${DEV}/driver_override
    ##??
    echo 1 > /sys/bus/pci/devices/${DEV}/remove

    #Previous method:
    #echo $DEV > /sys/bus/pci/drivers/vfio-pci/unbind
    #Re-attach to nvidia on host
    #echo $DEV > /sys/bus/pci/drivers/nvidia/bind
done

sleep 1


echo 1 > /sys/bus/pci/rescan
sleep 0.2

#Check visible on host now
#nvidia-smi

#Restart X server
/root/runX.sh >&- 2>&- <&-

