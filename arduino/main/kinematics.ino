// inverse_kinematics computes the theta value for each connection for the expected rotation and position of the platform
void inverse_kinematics(StewartPlatform *plat) {
  // Matrix<3> pos = {plat->pos.x, plat->pos.y, plat->pos.z};
  float yaw = d2rad(plat->rot.yaw);
  float pitch = d2rad(plat->rot.pitch);
  float roll = d2rad(plat->rot.roll);
  // Matrix<3,3> r_z = {cos(yaw), -sin(yaw), 0, sin(yaw), cos(yaw), 0, 0, 0, 1};
  // Matrix<3,3> r_y = {cos(pitch), 0, sin(pitch), 0, 1, 0, -sin(pitch), 0, cos(pitch)};
  // Matrix<3,3> r_x = {1, 0, 0, 0, cos(roll), -sin(roll), 0, sin(roll), cos(roll)};
  // Matrix<3,3> rot = {
  //   cos(d2rad(plat->rot.yaw)) * cos(d2rad(plat->rot.pitch)), -sin(d2rad(plat->rot.yaw)) * cos(d2rad(plat->rot.roll)) + cos(d2rad(plat->rot.yaw)) * sin(d2rad(plat->rot.pitch)) * sin(d2rad(plat->rot.roll)), sin(d2rad(plat->rot.yaw)) * sin(d2rad(plat->rot.roll)) + cos(d2rad(plat->rot.yaw)) * sin(d2rad(plat->rot.pitch)) * cos(d2rad(plat->rot.roll)),
  //   sin(d2rad(plat->rot.yaw)) * cos(d2rad(plat->rot.pitch)), cos(d2rad(plat->rot.yaw)) * cos(d2rad(plat->rot.roll)) + sin(d2rad(plat->rot.yaw)) * sin(d2rad(plat->rot.pitch)) * sin(d2rad(plat->rot.roll)), -cos(d2rad(plat->rot.yaw)) * sin(d2rad(plat->rot.roll)) + sin(d2rad(plat->rot.yaw)) * sin(d2rad(plat->rot.pitch)) * cos(d2rad(plat->rot.roll)),
  //   -sin(d2rad(plat->rot.pitch)), cos(d2rad(plat->rot.pitch)) * sin(d2rad(plat->rot.roll)), cos(d2rad(plat->rot.pitch)) * cos(d2rad(plat->rot.roll))
  // };
  // Matrix<3,3> rot = r_z * r_y * r_x;
  // Matrix<3,3> rot = r_x * r_y * r_z;
  for (int i=0; i < 6; i++) {
    float px = plat->connections[i].p[0];
    float py = plat->connections[i].p[1];
    float pz = plat->connections[i].p[2];
    float p_x = (px * cos(roll) * cos(yaw)) + py * (sin(pitch) * sin(roll) * cos(roll) - cos(pitch) * sin(yaw)) + plat->pos.x;
    float p_y = (px * cos(roll) * sin(yaw)) + py * (cos(pitch) * cos(yaw) + sin(pitch) * sin(roll) * sin(yaw)) + plat->pos.y;
    float p_z = px * sin(roll) + (py * sin(pitch) * cos(roll)) + pz + plat->pos.z;
    // Matrix<3> plat_pos = {p_x, p_y, p_z};
    // Matrix<3> l_vector = {p_x - plat->connections[i].b(0), p_y - plat->connections[i].b(1), p_z - plat->connections[i].b(2)};
    // plat->connections[i].theta = rotation_for_position(pos, rot, plat->connections[i]);
    float plat_pos[3] = {p_x, p_y, p_z};
    float l_vector[3] = {p_x - plat->connections[i].b[0], p_y - plat->connections[i].b[1], p_z - plat->connections[i].b[2]};
    plat->connections[i].theta = rotation_for_position(plat_pos, l_vector, plat->connections[i]);
  }
}

float d2rad(float d) {
  return d * M_PI / 180;
}

// calculate_virtual_leg as l = T + R * p_i - b_i
// Matrix<3> calculate_virtual_leg(Matrix<3> t, Matrix<3,3> rot, Connection conn) {
//   return t + (rot*conn.p) - conn.b;
// }

// roration_for_position returns the servo motor rotation for a given displacement vector t, and a rotation matrix rot
float rotation_for_position(float plat_pos[3], float l_vector[3], Connection conn) {
  // Matrix<3> l_vector = calculate_virtual_leg(t, rot, conn);
  // Matrix<3> plat_pos = t + rot * conn.p;


  // calculate the modulus of l_vector
  float l = sqrt(pow(l_vector[0], 2) + pow(l_vector[1], 2) + pow(l_vector[2], 2));
  float beta_rad = conn.beta * M_PI / 180;
  
  // L = l^2 - (s^2 - a^2)
  float L = pow(l, 2) - (pow(conn.rod_length, 2) - pow(conn.servo_arm_length, 2));
  // 2a * (z_p - z_b)
  float M = 2*conn.servo_arm_length * (plat_pos[2] - conn.b[2]);
  
  // 2a * [cos(beta) * (x_p - x_b) + sin(beta) * (y_p - y_z)]
  float N = 2*conn.servo_arm_length * (cos(beta_rad) * (plat_pos[0] - conn.b[0]) + sin(beta_rad) * (plat_pos[1] - conn.b[1]));
  
  float aux = L / (sqrt(pow(M, 2) + pow(N, 2)));
  if (aux < -1.0) {
    aux = -1.0;
  } else if (aux > 1.0) {
    aux = 1.0;
  }
  float alfa_rad = asin(aux) - atan(N/M);
  
  #ifdef DEBUG
    Serial.print("Start Servo => ");
    Serial.println(conn.index);
    Serial.print("plat_pos = [");
    Serial.print(plat_pos[0]);
    Serial.print(", ");
    Serial.print(plat_pos[1]);
    Serial.print(", ");
    Serial.print(plat_pos[2]);
    Serial.println("]");

    Serial.print("l = [");
    Serial.print(l_vector[0]);
    Serial.print(", ");
    Serial.print(l_vector[1]);
    Serial.print(", ");
    Serial.print(l_vector[2]);
    Serial.print("] = ");
    Serial.println(l);

    Serial.print("L = ");
    Serial.println(L);

    Serial.print("M = ");
    Serial.println(M);

    Serial.print("N = ");
    Serial.println(N);

    Serial.print("alfa_rad = ");
    Serial.println(alfa_rad);
    Serial.println(alfa_rad * 180 / M_PI);
    Serial.print("END Servo => ");

  #endif
  return alfa_rad * 180 / M_PI;
}