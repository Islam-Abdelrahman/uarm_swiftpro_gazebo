#include <string>  
#include "ros/ros.h"
#include "swiftpro_control/IK.h"
#include "std_msgs/Float64.h"
#include "global_constants.hh"
#include "forward_kinematics.hh"
#include "inverse_kinematics.hh"

double joint_angle[num_of_joints] = {0.0};

// Global joint publisher variables
ros::Publisher joints_pubs[num_of_joints];

bool check_requested_position (swiftpro_control::IK::Request& req)
    {
        if ((req.x>= min_x && req.x<= max_x)&&
        (req.y>= min_y && req.y<= max_y)&&
        (req.z>= min_z && req.z<= max_z))
        {return true;}

        else
        {
            ROS_ERROR("Infeasible requested position!, feasible range is x: [%d,%d], y: [%d:%d], z: [%d,%d]",min_x,max_x,min_y,max_y,min_z,max_z);
            return false;
        }
        
    }

// This callback function executes whenever a inverse_kinematics service is requested
bool handle_inverse_kinematics_request(swiftpro_control::IK::Request& req,
    swiftpro_control::IK::Response& res)
{

    if (check_requested_position(req))
    {
        double position[3];
        double angle[3];
        // in mm 
        position[0] = req.x;
        position[1] = req.y;
        position[2] = req.z;
        
        if (inverse_kinematics(position,angle))
        {
            if (forward_kinematics(joint_angle,angle))
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
        }
    }
    return true;
}
int main(int argc, char** argv)
{
    // Initialize the ik_swiftpro node
    ros::init(argc, argv, "ik_swiftpro");
    // Create a handle to the  node (to communicate with ros master) 
    ros::NodeHandle n;
    std::string topic_name; 

    // Publish the arm joint angles
    for (int i = 0;i<num_of_joints;i++)
        {
        topic_name = "/swiftpro/joint" + std::to_string(i+1) + "_position_controller/command";
        joints_pubs[i] = n.advertise<std_msgs::Float64>(topic_name,10);
        }

    // Define a inverse_kinematics service with a handle_inverse_kinematics_request callback function
    ros::ServiceServer service = n.advertiseService("/swiftpro_control/inverse_kinematics", handle_inverse_kinematics_request);
    ROS_INFO("Ready to send x y z coordinates");

    // Handle ROS communication events
    ros::spin();

    return 0;
}
