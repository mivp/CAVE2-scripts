#!/bin/bash
exec X -br :0 vt1 -dpi 80 -nolisten tcp -noreset -config /etc/X11/xorg.conf.k5000 &
sleep 1
export DISPLAY=:0.0
xhost +localhost
xset  dpms force on
xset -dpms
xset -dpms s reset
xset s off s noblank
xterm &
chvt 1
