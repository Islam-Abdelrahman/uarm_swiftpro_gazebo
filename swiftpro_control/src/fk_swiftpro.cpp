#include <string>  
#include "ros/ros.h"
#include "swiftpro_control/FK.h"
#include "std_msgs/Float64.h"
#include "global_constants.hh"
#include "forward_kinematics.hh"

double joint_angle[num_of_joints] = {0.0};

// Global joint publisher variables
ros::Publisher joints_pubs[num_of_joints];

// This callback function executes whenever a forward_kinematics service is requested
bool handle_forward_kinematics_request(swiftpro_control::FK::Request& req,
    swiftpro_control::FK::Response& res)
    {

    // get joints values
    double angles[3]={req.angleRot,req.angleLeft,req.angleRight};

    if (forward_kinematics(joint_angle,angles))
        {
        // Set the arm joint angles
        std_msgs::Float64 joint_angles[num_of_joints];
        for (int i = 0;i<num_of_joints;i++)
            {
            joint_angles[i].data = joint_angle[i]/deg2rad;
            }
        
        // Publish the arm joint angles
        for (int i = 0;i<num_of_joints;i++)
            {
            joints_pubs[i].publish(joint_angles[i]);;
            }

        // Wait delay_time seconds for arm to settle
        ros::Duration(delay_time).sleep();
        res.success = true;
        }
    return true;
    }

int main(int argc, char** argv)
{
    // Initialize the fk_swiftpro node
    ros::init(argc, argv, "fk_swiftpro");
    // Create a handle to the  node (to communicate with ros master) 
    ros::NodeHandle n;
    std::string topic_name; 
    
    // Publish the arm joint angles
    for (int i = 0;i<num_of_joints;i++)
        {
        topic_name = "/swiftpro/joint" + std::to_string(i+1) + "_position_controller/command";
        joints_pubs[i] = n.advertise<std_msgs::Float64>(topic_name,10);
        }

    // Define a forward_kinematics service with a handle_forward_kinematics_request callback function
    ros::ServiceServer service = n.advertiseService("/swiftpro_control/forward_kinematics", handle_forward_kinematics_request);
    ROS_INFO("Ready to send joint angles");

    // Handle ROS communication events
    ros::spin();

    return 0;
}