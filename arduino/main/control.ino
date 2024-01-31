

float kp = 0.12;
float ki = 0.158;
float kd = 0.15;

void setupPID(StewartPlatform *platform) {
  // ArduPID pidX;
  // ArduPID pidY;
  
  platform->pidX.begin(&platform->ball.x, &platform->rot.roll, &platform->setpoint.x, kp, ki, kd);
  platform->pidX.setSampleTime(20);
  platform->pidX.setOutputLimits(-30.0, 30.0);
  platform->pidX.setWindUpLimits(-30.0, 30.0);
  platform->pidX.reverse();

  platform->pidY.begin(&platform->ball.y, &platform->rot.pitch, &platform->setpoint.y, kp, ki, kd);
  platform->pidY.setSampleTime(20);
  platform->pidY.setOutputLimits(-30.0, 30.0);
  platform->pidY.setWindUpLimits(-30.0, 30.0);
  platform->pidY.reverse();

  // platform->pidX = &pidX;
  // platform->pidY = &pidY;
}

void startPID(StewartPlatform *platform) {
  platform->pidX.reset();
  platform->pidY.reset();
  platform->pidY.start();
  platform->pidX.start();
}

void stopPID(StewartPlatform *platform) {
  platform->pidX.stop();
  platform->pidY.stop();
}

void setupGains(StewartPlatform *platform, float p, float i, float d) {
  platform->pidX.setCoefficients(p, i, d);
  platform->pidY.setCoefficients(p, i, d);
  platform->pidX.reset();
  platform->pidY.reset();
}


void computePIDs(StewartPlatform *platform) {
  platform->pidX.compute();
  platform->pidY.compute();
}