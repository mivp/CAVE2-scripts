#!/bin/sh

#This needs to be run as root
#Will take 10-40 minutes approximately to image one disk, possibly more if run in parallel

#Run on all nodes to update image
#IMG="/data/fast/johnp/image/T1 Clone.img"
IMG="/data/fast/johnp/image/n01.img"
echo ${IMG}

#Destination drive, make sure this is correct for all nodes!
DEST=sdd

#Check for mounted partitions first
if [[ $(mount |grep ${DEST}) ]]; then
    echo "there are mounted partitions on ${DEST}, aborted!"
else
    echo "no mounts found, proceeding to image copy"

    #With progress, 256K block size
    dd if="${IMG}" of=/dev/sdd bs=262144 status=progress
fi

