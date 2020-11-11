# Home Service Robot - Udacity Robotics Software Engineer Nanodegree

This project simulates a home service robot and it is the final project for the Udacity Robitics Software Engineer Nanodegree program. 

This project was developed in ros noetic and it uses Turtlebot3 (waffle pi) instead of the original Turtlebot due to compatibility with ros noetic. The Turtlebot3 packages were clone from https://github.com/ROBOTIS-GIT/turtlebot3 and the Turtlebot3 simulation package was clone from https://github.com/ROBOTIS-GIT/turtlebot3_simulations. 

To run the project, create a folder name catkin_ws under your home directory and clone this repository :

    mkdir ~/catkin_ws
    cd ~/catkin_ws 
    git clone https://github.com/miniermatar/Udacity_RobotND_Home_Service_Robot

Initialize catkin (don’t forget to source the ros setup bash file `source /opt/ros/DISTRO/setup.bash`)

    cd ~/catkin_ws/src
    catkin_init_workspace

Run rosdep to install project dependencies 

    cd ~/catkin_ws/
    rosdep install --from-paths src --ignore-src -r -y

After completion run `catkin_make`

## Scripts

Below are the details of each script created:

<b>test_slam.sh:</b> it will open the gazebo world, the gmapping terminal and teleop. This script was used to generate the world map file by driving the robot around the world. Once the map was completed, the following command was used to save the map; it creates the pgm and yaml files in the ho,emdirectory with the name "map":

    rosrun map_server map_saver -f ~/map

<b>test_navigation.sh</b>: this script is used to test the robot navigation in the gazebo world using the map created with SLAM. A goal location target can be provided using Rviz. In this script, localization is performed using the adaptative montercarlo localization (AMCL) package. 

<b>pick_object.sh</b>: this script opens the gazebo world and provide a pick up and drop up location to the robot. The coordinates for the pick up and drop up location are entered in a yaml file (/config/marker_loc.yaml). When the script runs, the pick_objects package sends the pickup location and the robot starts navigating there. Once it reached the location it waits 5 seconds before heading to the drop of location which is also provided by the pick_objects package based on the information on the marker_loc yaml file. Then the robot heads to the drop of location. This package also publishes a topic indicating if the robot arrived at the pick up or drop off locations which will be used to communicate with the add_markers package.

<b>add_marker.sh</b>: Running this script will open the Gazebo world and Rviz and it will display a marker in the pick-up location that will last 5 seconds. Then the marker will disappear and 5 seconds later it will appear in the drop of location.  The pick up and drop off locations can be adjusted by editing the yaml file at `/config/marker_loc.yaml`

<b>home_service.sh</b>: This script simulates a home service robot that picks up an object and drop it off in a different location. The script open the Gazebo world and the Adaptative Montecarlo Localization (AMCL) package to localize the robot. Then the pick_objects package sends a navigation goal (based on the details is the `/config/markers_loc.yaml`) for the pick up location. At the same time, the add_markers package will display a marker at the pick up location. Once the robot reaches the pick up location, the marker will disappear and the pick_objects package will send a navigation goal for the drop off location. Once the robot reaches the drop off location, the add_markers package will display the marker at the drop off location. 

Below is a video showing the `home_service.sh` script running.


### Notes:

The gazebo world contains object downloaded from: http://data.nvision2.eecs.yorku.ca/3DGEMS/. If you encounter problems opening the gazebo world, please copy the content of `/my_robot/gazebo_model` to `~/.gazebo/models`; that will allow the gazebo objects to load properly.

Since this development was performed using ros noetic, it is recommended to run `sudo apt update` and then `sudo apt upgrade` before running rhe scripts. Upgrading the system could solve unexpected problems. 

