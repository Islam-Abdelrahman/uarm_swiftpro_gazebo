#include "ros/ros.h"
#include "swiftpro_control/IK.h"
#include "std_srvs/Empty.h"

void move_to(ros::ServiceClient client,double coordinates[3])
{
    // Request a service and pass object postion
    swiftpro_control::IK srv;
    srv.request.x      = coordinates[0];
    srv.request.y      = coordinates[1];    
    srv.request.z      = coordinates[2];
    
    // Call the inverse_kinematics service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service inverse_kinematics");
    
    else
        {ROS_INFO("Robot moved to desired position");}
}

void manipulate_obj(ros::ServiceClient client, bool on_off_switch)
{
    // Request a service 
    std_srvs::Empty srv;
    srv.request;

    // Call the vacuum_gripper service and pass the requested joint angles
    if (on_off_switch)
        {
        if (!client.call(srv))
            ROS_ERROR("Failed to call service /swiftpro/vacuum_gripper/on");
        else
            {ROS_INFO("Object picked!");}
        }
    else
        {
        if (!client.call(srv))
            ROS_ERROR("Failed to call service /swiftpro/vacuum_gripper/off");
        else
            {ROS_INFO("Object unpicked!");}
        } 
}
