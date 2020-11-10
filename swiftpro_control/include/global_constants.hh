/* 
    Limits 
*/
// base motor
#define angleRot_MAX_ANGLE     200               
#define angleRot_MIN_ANGLE     0
// left motor 
#define angleLeft_MAX_ANGLE     135
#define angleLeft_MIN_ANGLE     0
// right motor 
#define angleRight_MAX_ANGLE   100
#define angleRight_MIN_ANGLE   0
// slider 
#define SLIDER_MAX_POS   500
#define SLIDER_MIN_POS   0

/* 
    Limits of robot workspace
*/
#define min_x   30  
#define max_x   280     
#define min_y   -278
#define max_y   278
#define min_z   0
#define max_z   130


/* 
    Global parameters
*/
#define deg2rad         57.2958
#define num_of_joints   9
#define delay_time      1
#define offset_in_z     75

/* 
    Inverse parameters
*/
#define MATH_L1 				106.6
#define MATH_L2 				13.2
#define MATH_LOWER_ARM 			142.07
#define MATH_UPPER_ARM 			158.81	
#define MATH_UPPER_LOWER 		(MATH_UPPER_ARM / MATH_LOWER_ARM)
