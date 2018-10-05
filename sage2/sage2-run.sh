#!/bin/bash
#When using network=host, no port forwarding is required:
docker run -d --volumes-from=sage2Config --volumes-from=sage2Keys --volumes-from=sage2Uploads --network=host --name sage2 sage2/master
#docker run -d --volumes-from=sage2Config --volumes-from=sage2Keys --volumes-from=sage2Uploads -p 9090:9090 -p 9292:9292 --name sage2 sage2/master

#docker ps
#docker logs sage2

#Needs to be run every time on container start
docker exec -e "CONTAINER_TIMEZONE=Australia/Melbourne" sage2 /sage2/bin/docker_set_timezone.sh

chrome-browser "https://trio01.cave.monash.edu:9090/index.html"


