#include "ros/ros.h"
#include "swiftpro_control/IK.h"
#include "std_srvs/Empty.h"
#include "simple_pick.hh"

// Define a global client that can request services
ros::ServiceClient ik_client;
ros::ServiceClient gripper_on_client;
ros::ServiceClient gripper_off_client;

#define  obj_x      30.0
#define  obj_y      180.0
#define  obj_z      25.0

#define  goal_x     150.0
#define  goal_y     0.0
#define  goal_z     40.0

int main(int argc, char** argv)
{
    // Initialize the simple_picker node and create a handle to it
    ros::init(argc, argv, "simple_picker");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from inverse_kinematics
    ik_client = n.serviceClient<swiftpro_control::IK>("/swiftpro_control/inverse_kinematics");

    // Define a client service capable of requesting services from /vacuum_gripper/on
    gripper_on_client = n.serviceClient<std_srvs::Empty>("/swiftpro/vacuum_gripper/on");

    // Define a client service capable of requesting services from /vacuum_gripper/on
    gripper_off_client = n.serviceClient<std_srvs::Empty>("/swiftpro/vacuum_gripper/off");

    // move to
    double obj_coordinates[3]   = {obj_x,obj_y,obj_z};  
    move_to(ik_client,obj_coordinates);

    // pick object
    manipulate_obj(gripper_on_client,true);

    // deliver object to target
    double goal_coordinates[3]  = {goal_x,goal_y,goal_z};
    move_to(ik_client,goal_coordinates);

    // unpick object
    manipulate_obj(gripper_off_client,false);

    return 0;
}