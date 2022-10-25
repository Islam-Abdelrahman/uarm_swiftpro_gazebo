# Uarm swiftpro in Gazebo
## Forward/Inverse kinematics
roslaunch swiftpro_control swiftpro_control.launch

	1-Homing
		rosrun swiftpro_control home_pose

	2-Forward kinematics
		rosservice call /swiftpro_control/forward_kinematics "angleRot: 0.0
		angleLeft: 0.0
		angleRight: 0.0" 

	3-Inverse kinematics
		rosservice call /swiftpro_control/inverse_kinematics "x: 0.0
		y: 0.0
		z: 0.0" 

## Pick and place
	cd ~/catkin_ws/src/uarm_swiftpro_gazebo/scripts
	source swifpro_pick_and_place.sh
## Plan
1. add rviz
2. add real robot