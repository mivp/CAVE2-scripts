#!/bin/sh

#Run a script in current directory on all nodes

#n01-n20
tentakel -g cave2 "cd `pwd` ; ${@}"

#Head node, leave out for now
#${@}

