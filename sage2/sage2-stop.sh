#!/bin/bash
#Stop sage2 server, run on head1

#Stop running instance
docker stop sage2

#Remove container (use stop/start? this creates clean container)
docker rm sage2

#Kill clients
tentakel pkill -HUP chrome
#tentakel pkill -HUP electron
