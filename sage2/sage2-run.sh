#!/bin/bash
#Start sage2 server, run on head1

#First kill existing
./sage2-stop.sh
sleep 0.5

#When using network=host, no port forwarding is required:
docker run -d --volumes-from=sage2Config --volumes-from=sage2Keys --volumes-from=sage2Uploads --network=host --name sage2 sage2/master

#docker run -d --volumes-from=sage2Config --volumes-from=sage2Keys --volumes-from=sage2Uploads -p 9090:9090 -p 9292:9292 --name sage2 sage2/master

#If already running can use
#docker stop sage2
#docker start sage2

#List running instances
#docker ps
#Display logs
#docker logs sage2

#Needs to be run every time on container start
docker exec -e "CONTAINER_TIMEZONE=Australia/Melbourne" sage2 /sage2/bin/docker_set_timezone.sh

sleep 1.0
google-chrome "https://head1.cave.monash.edu:9090/index.html" --ignore-certificate-errors &

#Start client displays

server="head1.cave.monash.edu:9090"
#global_param="--window-size=1366,3072 --window-position=0,0 --kiosk --disable-popup-blocking --nfirst-run --use-gl --enable-accelerated-compositing --allow-file-access-from-files --disable-session-crashed-bubble --allow-running-insecure-content"
global_param="--window-size=1366,3072 --window-position=0,0 --kiosk --disable-popup-blocking --no-first-run --use-gl --enable-accelerated-compositing --allow-file-access-from-files --disable-session-crashed-bubble --allow-running-insecure-content --disable-infobars  --ignore-certificate-errors --no-default-browser-check --disable-web-security"

for i in {1..20}
do
	node=`printf n%02d $i`
	idx=`expr $i - 1`
	echo "================= $node: client $idx ================="
	UDD="$HOME/.config/chrome-nfs/$node"
	param="$global_param --user-data-dir=$UDD"
	
	ssh -fx $node "env DISPLAY=:0.0 google-chrome $param 'https://$server/display.html?clientID=$idx'" &
	ssh -fx $node "sleep 5; env DISPLAY=:0.0 xdotool mousemove --sync 10 10; env DISPLAY=:0.0 xdotool mousemove --sync 0 0" &
done


