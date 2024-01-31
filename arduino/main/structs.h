#include "ArduPID.h"

typedef union
{
    float number;
    uint8_t bytes[4];
} FLOATUNION_t;

typedef union
{
    double number;
    uint8_t bytes[8];
} DOUBLEUNION_t;

typedef struct {
  double x;
  double y;
  double z;
} Position;

typedef struct {
  double yaw;
  double pitch;
  double roll;
} Rotation;

typedef struct {
  float theta1;
  float theta2;
  float theta3;
  float theta4;
  float theta5;
  float theta6;
} Angles;

typedef struct {
  int index;
  float b[3]; // b_i
  float p[3]; // p_i
  float rod_length;
  float servo_arm_length;
  float theta;
  float beta;
} Connection; // Represents a physical connection between base and platform
 
typedef struct {
  Position pos;
  Rotation rot;
  Connection connections[6];
  Position ball;
  Position setpoint;
  ArduPID pidX;
  ArduPID pidY;
} StewartPlatform;
