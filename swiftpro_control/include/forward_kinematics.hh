#include "global_constants.hh"
bool forward_kinematics(double joint_angle[9],double angle[3])
{

    if ((angle[0]>= angleRot_MIN_ANGLE && angle[0]<= angleRot_MAX_ANGLE)&&
        (angle[1]>= angleLeft_MIN_ANGLE && angle[1]<= angleLeft_MAX_ANGLE)&&
        (angle[2]>= angleRight_MIN_ANGLE && angle[2]<= angleRight_MAX_ANGLE))
        {	
            double alpha2;
            double alpha3;
    
            alpha2 = angle[1];
            alpha3 = angle[2] - 3.8;
            
            // 3 necessary joints for kinematic chain
            joint_angle[0] = angle[0] - 90;
            joint_angle[1] = 90 - alpha2;
            joint_angle[5] = alpha3;

            // 6 passive joints for display
            joint_angle[2] = (alpha2 + alpha3) - 176.11 + 90;
            joint_angle[3] = -90 + alpha2;
            joint_angle[4] = joint_angle[1];
            joint_angle[6] = 90 - (alpha2 + alpha3);
            joint_angle[7] = 176.11 - 180 - alpha3;
            joint_angle[8] = 48.39 + alpha3 - 44.55;

            return true;
        }
    else 
        {
            ROS_ERROR("Infeasible angle values!, feasible range is angleRot: [%d,%d], angleLeft: [%d:%d], angleRight: [%d,%d]",angleRot_MIN_ANGLE,angleRot_MAX_ANGLE,angleLeft_MIN_ANGLE,angleLeft_MAX_ANGLE,angleRight_MIN_ANGLE,angleRight_MAX_ANGLE);
            ROS_WARN("Requested angles are; angleRot: %f, angleLeft: %f, angleRight: %f",angle[0],angle[1],angle[2]);
            return false;
        }
}