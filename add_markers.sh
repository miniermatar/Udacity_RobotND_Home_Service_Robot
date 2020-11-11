#!/bin/sh
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_gazebo turtlebot3_world.launch world_file:=./../../map/JMWorld.world" &
sleep 5
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; roslaunch turtlebot3_navigation turtlebot3_navigation_marker.launch map_file:=$(pwd)/src/map/JMWorld.yaml initial_pose_x:=3 initial_pose_y:=-6.0 initial_pose_a:=1.59" & 
sleep 5
xterm  -e  "cd ~/catkin_ws/; source devel/setup.bash; export TURTLEBOT3_MODEL=waffle_pi; rosparam load $(pwd)/src/config/marker_loc.yaml; rosrun add_markers add_markers_time" 

