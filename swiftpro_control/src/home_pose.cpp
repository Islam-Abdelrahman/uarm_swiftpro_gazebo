#include "ros/ros.h"
#include "swiftpro_control/FK.h"
#include "home_pose.hh"

int main(int argc, char** argv)
{
    // Initialize the home_pose node and create a handle to it
    ros::init(argc, argv, "home_pose");
    ros::NodeHandle n;
    // Define a global client that can request services
    ros::ServiceClient client;
    // Define a client service capable of requesting services from forward_kinematics
    client = n.serviceClient<swiftpro_control::FK>("/swiftpro_control/forward_kinematics");

    // set robot to home pose
    home_pose(client);
    ROS_INFO("Robot in home pose");
    
    return 0;
}