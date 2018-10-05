#!/bin/bash
#-----------------------------------------------
# 1. Install Docker

#https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-centos-7

curl -fsSL https://get.docker.com/ > /tmp/docker-install.sh

sh /tmp/docker-install.sh

systemctl start docker

systemctl status docker

systemctl enable docker

usermod -aG docker cave

#-----------------------------------------------
# 2. Install NVidia Docker

#https://github.com/NVIDIA/nvidia-docker

#https://www.server-world.info/en/note?os=CentOS_7&p=cuda&f=2

#CentOS 7 (docker), RHEL 7.4/7.5 (docker)
curl -s -L https://nvidia.github.io/nvidia-docker/centos7/nvidia-docker.repo > /etc/yum.repos.d/nvidia-docker.repo

# Install nvidia-docker2 and reload the Docker daemon configuration
yum install -y nvidia-docker2
pkill -SIGHUP dockerd

# Test nvidia-smi with the latest official CUDA image
#docker run --runtime=nvidia --rm nvidia/cuda:9.0-base nvidia-smi

