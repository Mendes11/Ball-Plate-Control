#define PACKAGE_SIZE 64
uint8_t buffer[PACKAGE_SIZE];
uint8_t buffer_bytes_read = 0;

void addDouble(uint8_t *p, double value) {
  DOUBLEUNION_t valueBytes;
  valueBytes.number = value;
  memcpy(p, valueBytes.bytes, sizeof(valueBytes.bytes));
}

void addFloat(uint8_t *p, float value) {
  FLOATUNION_t valueBytes;
  valueBytes.number = value;
  memcpy(p, valueBytes.bytes, sizeof(valueBytes.bytes));
}


// create the packet to be sent to the UI
void packet(uint8_t *p, StewartPlatform *plat) {
  addFloat(p + (0 * 4), (float) plat->ball.x);
  addFloat(p + (1 * 4), (float) plat->ball.y);
  addFloat(p + (2 * 4), (float) plat->setpoint.x);
  addFloat(p + (3 * 4), (float) plat->setpoint.y);
  addFloat(p + (4 * 4), (float) plat->rot.roll);
  addFloat(p + (5 * 4), (float) plat->rot.pitch);
  addFloat(p + (6 * 4), (float) plat->pidX.pIn);
  addFloat(p + (7 * 4), (float) plat->pidX.iIn);
  addFloat(p + (8 * 4), (float) plat->pidX.dIn);
}

void sendDataToSerial(StewartPlatform *plat) {
  if (Serial.availableForWrite() >= 63) {
    uint8_t buf[64];
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    packet(buf + 2, plat);
    Serial.write(buf, sizeof(buf));
  }
}

void processSetGains(StewartPlatform *plat, uint8_t data[61]) {
  // Expects 3 float32 values (P, I, D)
  FLOATUNION_t pBytes;
  FLOATUNION_t iBytes;
  FLOATUNION_t dBytes;
  uint8_t p[4] = { data[0], data[1], data[2], data[3] };
  uint8_t i[4] = { data[4], data[5], data[6], data[7] };
  uint8_t d[4] = { data[8], data[9], data[10], data[11] };
  memcpy(pBytes.bytes, p, 4);
  memcpy(iBytes.bytes, i, 4);
  memcpy(dBytes.bytes, d, 4);
  setupGains(plat, pBytes.number, iBytes.number, dBytes.number);
}


void processSetSetpoint(StewartPlatform *plat, uint8_t data[61]) {
  // Set Setpoint
  // Expects 2 float32 values and ignore the rest
  FLOATUNION_t xBytes;
  FLOATUNION_t yBytes;
  uint8_t x[4] = { data[0], data[1], data[2], data[3] };
  uint8_t y[4] = { data[4], data[5], data[6], data[7] };
  memcpy(xBytes.bytes, x, 4);
  memcpy(yBytes.bytes, y, 4);
  plat->ball.x = xBytes.number;
  plat->ball.y = yBytes.number;
  Serial.print("Setpoint set to ");
  Serial.print("x=");
  Serial.print(xBytes.number);
  Serial.print(" and y=");
  Serial.println(yBytes.number);
}


void listenToCommands(StewartPlatform *plat) {
  if (Serial.available() > 0) {
    if (buffer_bytes_read == 0) {
      if (Serial.readBytes(buffer, 1) != 0 && buffer[0] == 0xFF) {
        Serial.println("Found start of package");
        buffer_bytes_read ++;
      }
    } else {  // Start of message detected, continue reading until reading the whole package
      Serial.print("Continuing Reading for buffer");
      Serial.println(buffer_bytes_read);
      buffer_bytes_read += Serial.readBytes(buffer+buffer_bytes_read, PACKAGE_SIZE - buffer_bytes_read);
      Serial.print("Current Buffer bytes count is");
      Serial.println(buffer_bytes_read);
      if (buffer_bytes_read == PACKAGE_SIZE) {
        buffer_bytes_read = 0; // make sure to "clear" the counter, so we can fill with the next package

        char command[2] = { buffer[1], buffer[2] };
        Serial.print("Command is ");
        Serial.println(command);
        if (strcmp(command, "SG") == 0) {
          // Set Gains
          processSetGains(plat, (buffer + 3));
        } else if (strcmp(command, "SS") == 0) {
          processSetSetpoint(plat, (buffer + 3));
        } else {
          Serial.print("Command not found:");
          Serial.println(command);
        }
      }
    }
  }
}
