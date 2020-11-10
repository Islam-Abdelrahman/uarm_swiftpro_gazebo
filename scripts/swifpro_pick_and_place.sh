#!/bin/sh
xterm -e "roslaunch swiftpro_control swiftpro_pick.launch"&
sleep 7
xterm -e "rosrun swiftpro_control home_pose"&
sleep 5
xterm -e "rosrun swiftpro_control simple_picker"