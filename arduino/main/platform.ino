void initialize_platform(StewartPlatform *plat) {
  plat->connections[0].b[0] = B1_X;
  plat->connections[0].b[1] = B1_Y;
  plat->connections[0].b[2] = B1_Z;

  plat->connections[0].p[0] = P1_X;
  plat->connections[0].p[1] = P1_Y;
  plat->connections[0].p[2] = P1_Z;

  plat->connections[0].rod_length = ROD_LENGTH;
  plat->connections[0].servo_arm_length = SERVO_ARM_LENGTH;
  plat->connections[0].index = 1;
  plat->connections[0].beta = B1_BETA;

  plat->connections[1].b[0] = B2_X;
  plat->connections[1].b[1] = B2_Y;
  plat->connections[1].b[2] = B2_Z;
  plat->connections[1].p[0] = P2_X;
  plat->connections[1].p[1] = P2_Y;
  plat->connections[1].p[2] = P2_Z;
  plat->connections[1].rod_length = ROD_LENGTH;
  plat->connections[1].servo_arm_length = SERVO_ARM_LENGTH;
  plat->connections[1].index = 2;
  plat->connections[1].beta = B2_BETA;

  plat->connections[2].b[0] = B3_X;
  plat->connections[2].b[1] = B3_Y;
  plat->connections[2].b[2] = B3_Z;
  plat->connections[2].p[0] = P3_X;
  plat->connections[2].p[1] = P3_Y;
  plat->connections[2].p[2] = P3_Z;
  plat->connections[2].rod_length = ROD_LENGTH;
  plat->connections[2].servo_arm_length = SERVO_ARM_LENGTH;
  plat->connections[2].index = 3;
  plat->connections[2].beta = B3_BETA;

  plat->connections[3].b[0] = B4_X;
  plat->connections[3].b[1] = B4_Y;
  plat->connections[3].b[2] = B4_Z;
  plat->connections[3].p[0] = P4_X;
  plat->connections[3].p[1] = P4_Y;
  plat->connections[3].p[2] = P4_Z;
  plat->connections[3].rod_length = ROD_LENGTH;
  plat->connections[3].servo_arm_length = SERVO_ARM_LENGTH;
  plat->connections[3].index = 4;
  plat->connections[3].beta = B4_BETA;

  plat->connections[4].b[0] = B5_X;
  plat->connections[4].b[1] = B5_Y;
  plat->connections[4].b[2] = B5_Z;
  plat->connections[4].p[0] = P5_X;
  plat->connections[4].p[1] = P5_Y;
  plat->connections[4].p[2] = P5_Z;
  plat->connections[4].rod_length = ROD_LENGTH;
  plat->connections[4].servo_arm_length = SERVO_ARM_LENGTH;
  plat->connections[4].index = 5;
  plat->connections[4].beta = B5_BETA;

  plat->connections[5].b[0] = B6_X;
  plat->connections[5].b[1] = B6_Y;
  plat->connections[5].b[2] = B6_Z;
  plat->connections[5].p[0] = P6_X;
  plat->connections[5].p[1] = P6_Y;
  plat->connections[5].p[2] = P6_Z;
  plat->connections[5].rod_length = ROD_LENGTH;
  plat->connections[5].servo_arm_length = SERVO_ARM_LENGTH;
  plat->connections[5].index = 6;
  plat->connections[5].beta = B6_BETA;
}

void resetPlatform(StewartPlatform *plat) {
  plat->rot.yaw = 0;
  plat->rot.pitch = 0;
  plat->rot.roll = 0;
  plat->pos.x = 0;
  plat->pos.y = 0;
  plat->pos.z = 0;
  plat->setpoint.x = TOUCH_X_SIZE_MM / 2.0;
  plat->setpoint.y = TOUCH_Y_SIZE_MM / 2.0;
}
