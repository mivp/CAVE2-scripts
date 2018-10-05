#!/bin/bash
#https://bitbucket.org/sage2/sage2/wiki/Home
#https://bitbucket.org/sage2/sage2/wiki/Install%20(Docker)
if [ $# -eq 0 ]
then
  echo "No arguments supplied, please pass json config file to use"
fi

docker pull sage2/master
docker create -v /sage2/config --name sage2Config sage2/master
docker create -v /sage2/keys --name sage2Keys sage2/master
docker create -v /root/Documents/SAGE2_Media --name sage2Uploads sage2/master
docker run --rm -it --volumes-from sage2Keys sage2/master /sage2/keys/GO-docker _.cave.monash.edu
docker run --rm -it --volumes-from sage2Config sage2/master /bin/bash

#copy config file into /sage2/config/docker-cfg.json
docker cp $1 sage2/master:/sage2/config/docker-cfg.json

#yum install ./google-chrome-stable_current_x86_64.rpm
#wget https://dl.google.com/linux/direct/google-chrome-stable_current_x86_64.rpm
#yum localinstall google-chrome-stable_current_x86_64.rpm
