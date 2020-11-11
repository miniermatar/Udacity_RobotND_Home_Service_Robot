
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/UInt8.h>

uint8_t arrival_data=0;
bool finish = false;
//Arrival call back function
void arrivalfunc (const std_msgs::UInt8::ConstPtr& msg) {
  arrival_data=msg->data;
  return;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("/visualization_marker", 1);
  ros::Subscriber arrival_sub=n.subscribe("/arrived",1,arrivalfunc);
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
  
   
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    
    
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

   // if (arrival_data==0) {
    
    
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::ADD;
    
        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        n.getParam("/pick_up/px",marker.pose.position.x);
        n.getParam("/pick_up/py",marker.pose.position.y);
        n.getParam("/pick_up/pw",marker.pose.orientation.w);
        ROS_INFO("Publishing pick up marker");
    // Publish the marker
    marker_pub.publish(marker);    

	sleep(5);
   //}

  //  if (arrival_data==1) {
    
    
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::DELETE;
        ROS_INFO("Hidding pick up marker");
    // Publish the marker
    marker_pub.publish(marker);        
        sleep(5);
   // }
    
  //  if (arrival_data==2) {
    
    
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::ADD;
    
        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        n.getParam("/drop_off/px",marker.pose.position.x);
        n.getParam("/drop_off/py",marker.pose.position.y);
        n.getParam("/drop_off/pw",marker.pose.orientation.w);
        ROS_INFO("Publishing drop off marker");
    // Publish the marker
    marker_pub.publish(marker);
    

        //set finished flag
        finish=true;

 //  }

    

    marker.lifetime = ros::Duration();


    
/*
    // Cycle between different shapes
    switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }
*/

    if (finish==true) {
    break;
    }
    r.sleep();
  }
}
