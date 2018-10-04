## Setup scripts:

### nvidia-docker-setup.sh

Run on every node to install docker and enable NVidia GPU powered docker containers

run on head? yes

### kvm-install.sh

Run on every node to setup virtualisation and iommu and vfio pci passthrough 

### kvm-bridge.sh

Run on every node to setup network bridge for virtual machines
(Still a work in progress, requires testing)
