#include <Servo.h>
#include "constants.h"
#include "structs.h"
#include <math.h>
#include "ArduPID.h"


Servo s1, s2, s3, s4, s5, s6;
StewartPlatform platform;


int untouched_time;
long t;

bool pid_started;

uint8_t message[20];
bool reading_command;

#define YAW_MAX 30.0
#define ROLL_MAX 30.0
#define PITCH_MAX 30.0

#define X_MAX 30.0
#define Y_MAX 30.0
#define Z_MAX 20.0

void setup() {
  initialize_platform(&platform);
  setupServos();
  setupPID(&platform);
  Serial.begin(115200);
  resetPlatform(&platform);
  t = micros();
  untouched_time = millis();
}

void loop() {
  listenToCommands(&platform);
  inverse_kinematics(&platform);
  validateThetas(&platform);
  update(&platform);
  bool touching = readTouchPosition(&platform.ball);
  if (touching) {
    if (!pid_started) {
      startPID(&platform);
      pid_started = true;
    }
    untouched_time = 0;
  } else if (untouched_time == 0) {
    untouched_time = millis();
  } else if (millis() - untouched_time > 500) {
    stopPID(&platform);
    pid_started = false;
    resetPlatform(&platform);
  }

  computePIDs(&platform);  
  // sendDataToSerial(&platform);
  // Serial.println(micros() - t);
  t = micros();
  #ifdef DEBUG
      Serial.print(platform.connections[0].theta);
      Serial.print("  ");
      Serial.print(platform.connections[1].theta);
      Serial.print("  ");
      Serial.print(platform.connections[2].theta);
      Serial.print("  ");
      Serial.print(platform.connections[3].theta);
      Serial.print("  ");
      Serial.print(platform.connections[4].theta);
      Serial.print("  ");
      Serial.println(platform.connections[5].theta);
  #endif
}
