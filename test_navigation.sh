#!/bin/sh
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_gazebo turtlebot3_world.launch world_file:=./../../map/JMWorld.world" &
sleep 5
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$(pwd)/src/map/JMWorld.yaml" & 
sleep 5
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" 

