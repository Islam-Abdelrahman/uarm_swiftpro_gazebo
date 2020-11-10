/*
Home Pose
angleRot: 90.0
angleLeft: 90.0
angleRight: 0.0
*/
#define  AngRot       90.0
#define  AngLeft      90.0
#define  AngRight     0.0

void home_pose(ros::ServiceClient client)
{
    // Request a service and pass the home pose angles
    swiftpro_control::FK srv;
    srv.request.angleRot        = AngRot;
    srv.request.angleLeft       = AngLeft;    
    srv.request.angleRight      = AngRight;
    
    // Call the forward_kinematics service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service forward_kinematics");
}