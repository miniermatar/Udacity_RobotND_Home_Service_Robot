#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  std_msgs::UInt8 arrival_msg;  // arrival message
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  //Publisher to indicate robot reached location. 1 = pick_up location and 2= drop off location
  ros::Publisher arrival_pub = n.advertise<std_msgs::UInt8>("/arrived", 0);
  arrival_msg.data = 0;
  arrival_pub.publish(arrival_msg);
  
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define the pick_up position and orientation for the robot to reach
  n.getParam("/pick_up/px",goal.target_pose.pose.position.x);
  n.getParam("/pick_up/py",goal.target_pose.pose.position.y);
  n.getParam("/pick_up/pw",goal.target_pose.pose.orientation.w);

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Arrived at pick up location");
    arrival_msg.data = 1; //picked up - hide marker
    // publishing arrival message
    arrival_pub.publish(arrival_msg);
    }
  else {
    ROS_INFO("The robot failed to reach the assigned pick up location");
  }


  // wait 5 seconds for drop off location
  ros::Duration(5.0).sleep();

  // Define the drop off position and orientation for the robot to reach
  n.getParam("/drop_off/px",goal.target_pose.pose.position.x);
  n.getParam("/drop_off/py",goal.target_pose.pose.position.y);
  n.getParam("/drop_off/pw",goal.target_pose.pose.orientation.w);

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Arrived at drop off location");
    arrival_msg.data = 2; //drop off - marker visible
    // publishing arrival message
    arrival_pub.publish(arrival_msg);
    }
  else {
    ROS_INFO("The robot failed to reach the assigned drop off location");
  }
  ros::Duration(5.0).sleep();
  return 0;
}
