// #define DEBUG false

#define B1_PIN 11
#define B2_PIN 10
#define B3_PIN 9
#define B4_PIN 6
#define B5_PIN 5
#define B6_PIN 3

//Servos Correction Factor ##
// Correction factor to match the expected angle
#define THETA1_CORRECTION 10 
#define THETA2_CORRECTION -2 
#define THETA3_CORRECTION -6 
#define THETA4_CORRECTION 0 
#define THETA5_CORRECTION 7 
#define THETA6_CORRECTION 0
//END Servos Correction Factor 

// Initial angle of the servo, do not mistake this for theta_n
// theta_n is summed on this when writing to the servo.
#define SERVOS_INITIAL_ANGLE 90


#define THETA_MAX 90
#define THETA_MIN -90


// Platform Construction Constants
// Values in mm
// Angles in degrees

#define ROD_LENGTH 153
#define SERVO_ARM_LENGTH 25

// Simulator Axis orientation

// #define B1_X 56.2439
// #define B1_Y 67.0289
// #define B1_Z 0.0

// #define B2_X 86.1707
// #define B2_Y 15.1942
// #define B2_Z 0.0

// #define B3_X 29.9268
// #define B3_Y -82.2231
// #define B3_Z 0.0

// #define B4_X -29.9268
// #define B4_Y -82.2231
// #define B4_Z 0.0

// #define B5_X -86.1707
// #define B5_Y 15.1942
// #define B5_Z 0.0

// #define B6_X -56.2439
// #define B6_Y 67.0289
// #define B6_Z 0

// #define P1_X 42.4264
// #define P1_Y 42.4264
// #define P1_Z 150.8

// #define P2_X 57.9555
// #define P2_Y 15.5291
// #define P2_Z 150.8

// #define P3_X 15.5291
// #define P3_Y -57.9555
// #define P3_Z 150.8

// #define P4_X -15.5291
// #define P4_Y -57.9555
// #define P4_Z 150.8

// #define P5_X -57.9555
// #define P5_Y 15.5291
// #define P5_Z 150.8

// #define P6_X -42.4264
// #define P6_Y 42.4264
// #define P6_Z 150.8

// #define B1_BETA  180// Angle of servo arm plane relative to the x-axis
// #define B2_BETA  -120// Angle of servo arm plane relative to the x-axis
// #define B3_BETA  60// Angle of servo arm plane relative to the x-axis
// #define B4_BETA  120// Angle of servo arm plane relative to the x-axis
// #define B5_BETA  -60// Angle of servo arm plane relative to the x-axis
// #define B6_BETA  0// Angle of servo arm plane relative to the x-axis

//END Simulator Axis Orientation

// Resistive Panel Axis Orientation

#define B1_X 88.9675
#define B1_Y -15.6874
#define B1_Z 0.0

#define B2_X 58.0694
#define B2_Y -69.2045
#define B2_Z 0.0

#define B3_X -58.0694
#define B3_Y -69.2045
#define B3_Z 0.0

#define B4_X -88.9675
#define B4_Y -15.6874
#define B4_Z 0.0

#define B5_X -30.8981
#define B5_Y 84.8918
#define B5_Z 0.0

#define B6_X 30.8981
#define B6_Y 84.8918
#define B6_Z 0

#define P1_X 62.7852
#define P1_Y -16.8232
#define P1_Z 150.8

#define P2_X 45.9619
#define P2_Y -45.9619
#define P2_Z 150.8

#define P3_X -45.9619
#define P3_Y -45.9619
#define P3_Z 150.8

#define P4_X -62.7852
#define P4_Y -16.8232
#define P4_Z 150.8

#define P5_X -16.8232
#define P5_Y 62.7852
#define P5_Z 150.8

#define P6_X 16.8232
#define P6_Y 62.7852
#define P6_Z 150.8

#define B1_BETA  120// Angle of servo arm plane relative to the x-axis
#define B2_BETA  180// Angle of servo arm plane relative to the x-axis
#define B3_BETA  0// Angle of servo arm plane relative to the x-axis
#define B4_BETA  60// Angle of servo arm plane relative to the x-axis
#define B5_BETA  -120// Angle of servo arm plane relative to the x-axis
#define B6_BETA  -60// Angle of servo arm plane relative to the x-axis

//END Resistive Panel Axis Orientation


// Resistive Touch Sensor Constants
#define Y1 A0
#define X2 A1
#define Y2 A2
#define X1 A3
#define TOUCH_X_MIN 60
#define TOUCH_X_MAX 940
#define TOUCH_Y_MIN 90
#define TOUCH_Y_MAX 900

#define TOUCH_X_SIZE_MM 214.50
#define TOUCH_Y_SIZE_MM 160.30

// End Resistive Touch Sensor Constants