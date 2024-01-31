void setupServos() {
  s1.attach(B1_PIN);
  s2.attach(B2_PIN);
  s3.attach(B3_PIN);
  s4.attach(B4_PIN);
  s5.attach(B5_PIN);
  s6.attach(B6_PIN);
  update(&platform);
}

float validateTheta(float theta) {
  // if (theta > THETA_MAX) {
  //   return THETA_MAX;
  // } else if (theta < THETA_MIN) {
  //   return THETA_MIN;
  // }
  return theta;
}

int toMicroseconds(float angle) {
  // 1000 is fully counter-clockwise
  // 2000 is fully clockwise
  // Our angles are counter-clockwise, so the higher it is, the lower the returning value
  const int minimum = 1000;
  const int maximum = 2000;

  return minimum + round((maximum - minimum) * angle / 180);
  // 1000 -> 0
  // 2000 -> 180

}

void update(StewartPlatform* plat) {
  // Our thetas are defined anti-clockwise
  // 
  // b1, b3, b5 rotate anti-clockwise
  // b2, b4, b6 rotate clockwise
  // therefore, b2, b4, b6 must have their anti-clockwise angle transformed into clockwise
  // meaning, 180 - theta_x
  
  s1.writeMicroseconds(toMicroseconds(SERVOS_INITIAL_ANGLE + validateTheta(plat->connections[0].theta) + THETA1_CORRECTION));
  s2.writeMicroseconds(toMicroseconds(SERVOS_INITIAL_ANGLE - validateTheta(plat->connections[1].theta) - THETA2_CORRECTION));
  s3.writeMicroseconds(toMicroseconds(SERVOS_INITIAL_ANGLE + validateTheta(plat->connections[2].theta) + THETA3_CORRECTION));
  s4.writeMicroseconds(toMicroseconds(SERVOS_INITIAL_ANGLE - validateTheta(plat->connections[3].theta) - THETA4_CORRECTION));
  s5.writeMicroseconds(toMicroseconds(SERVOS_INITIAL_ANGLE + validateTheta(plat->connections[4].theta) + THETA5_CORRECTION));
  s6.writeMicroseconds(toMicroseconds(SERVOS_INITIAL_ANGLE - validateTheta(plat->connections[5].theta) - THETA6_CORRECTION));
}

void validateThetas(StewartPlatform* plat) {
  plat->connections[0].theta = validateTheta(plat->connections[0].theta);
  plat->connections[1].theta = validateTheta(plat->connections[1].theta);
  plat->connections[2].theta = validateTheta(plat->connections[2].theta);
  plat->connections[3].theta = validateTheta(plat->connections[3].theta);
  plat->connections[4].theta = validateTheta(plat->connections[4].theta);
  plat->connections[5].theta = validateTheta(plat->connections[5].theta);
}