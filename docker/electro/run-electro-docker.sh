#!/bin/bash

#Rebuild any changes to the image
docker build -t electro .

#Run the image
#(interactive for testing)
docker run -it --network=host --mount type=bind,source=/cave/Electro/examples,target=/Electro/examples --mount type=bind,source=/cave/Electro/config,target=/Electro/config electro
