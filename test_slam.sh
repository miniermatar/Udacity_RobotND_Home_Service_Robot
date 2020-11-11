#!/bin/sh
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_gazebo turtlebot3_world.launch world_file:=./../../map/JMWorld.world" &
sleep 5
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping" & 
sleep 5
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" 
