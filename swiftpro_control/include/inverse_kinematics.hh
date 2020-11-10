#include "global_constants.hh"

bool inverse_kinematics(double position[3], double angle[3])
    {
	float x = position[0];
	float y = position[1];
	float z = position[2];
	float xIn, zIn, phi, rightAll, sqrtZX = 0.0;
	float angleRot, angleLeft, angleRight = 0.0;
	
	z += 74.55;
	zIn = (z - MATH_L1) / MATH_LOWER_ARM;
	
	// calculate value of theta1: the rotation angle
	if (y == 0)
		angleRot = 90;
	else if (y < 0)
		angleRot = -atan(x / y) * deg2rad;
	else if (y > 0)
		angleRot = 180 - atan(x / y) * deg2rad;

	xIn 	= (x / sin(angleRot / deg2rad) - MATH_L2 - 56.55) / MATH_LOWER_ARM;
	phi 	= atan(zIn / xIn) * deg2rad;
	sqrtZX 	= sqrt(zIn * zIn + xIn * xIn);
	rightAll   = (sqrtZX * sqrtZX + MATH_UPPER_LOWER * MATH_UPPER_LOWER  - 1) 
			   / (2 * MATH_UPPER_LOWER  * sqrtZX);
	angleRight = acos(rightAll) * deg2rad;

	// calculate value of theta2 and theta3
	rightAll   = (sqrtZX * sqrtZX + 1 - MATH_UPPER_LOWER * MATH_UPPER_LOWER ) / (2 * sqrtZX);
	angleLeft  = acos(rightAll) * deg2rad;
	angleLeft  = angleLeft + phi;
	angleRight = angleRight - phi;

	if (isnan(angleRot) || isnan(angleLeft) || isnan(angleRight))
        {
            ROS_ERROR("Inverse kinematic could not be calculated!");
            return false;
        }

	angle[0] = angleRot;
	angle[1] = angleLeft;
	angle[2] = angleRight;
	return true;
    }