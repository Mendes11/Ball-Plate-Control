#include "TouchScreen.h"
TouchScreen ts = TouchScreen(X1, Y1, X2, Y2, 520);



float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getY() {
  // Pass current through Y1 (+) -> Y2 (-)
  // Read X1
  // pinMode(Y1, OUTPUT);
  // pinMode(Y2, OUTPUT);

  // pinMode(X1, INPUT);
  // pinMode(X2, INPUT);

  // digitalWrite(Y1, HIGH);
  // digitalWrite(Y2, LOW);
  // // delay(1);
  // delayMicroseconds(100);
  // int y = analogRead(X1);
  int y = ts.readTouchY();
  return mapfloat(constrain(y, 0, 1023), TOUCH_Y_MIN, TOUCH_Y_MAX, 0, TOUCH_Y_SIZE_MM);
}

void float32ToBytes(uint8_t b[4], float val) {
  // Convert a Float32 to an array of bytes in a big endian format
  b[0] = (uint8_t) val >> (32 - 8);
  b[1] = (uint8_t) val >> (32 - 16);
  b[2] = (uint8_t) val >> (32 - 24);
  b[3] = (uint8_t) val;
}

float getX() {
  // Pass current through X1 (+) -> X2 (-)
  // Read Y1
  // pinMode(X1, OUTPUT);
  // pinMode(X2, OUTPUT);

  // pinMode(Y1, INPUT);
  // pinMode(Y2, INPUT);

  // digitalWrite(X1, HIGH);
  // digitalWrite(X2, LOW);
  // // delay(1);
  // delayMicroseconds(100);
  // int x = analogRead(Y1);
  int x = ts.readTouchX();
  return mapfloat(constrain(x, 0, 1023), TOUCH_X_MIN, TOUCH_X_MAX, 0, TOUCH_X_SIZE_MM);
}

bool touching() {
  pinMode(Y1, INPUT_PULLUP);
  pinMode(X1, OUTPUT);
  pinMode(X2, OUTPUT);

  digitalWrite(X1, HIGH);
  digitalWrite(X2, LOW);
  delayMicroseconds(100);
  int x = analogRead(Y1);
  Serial.println(x);
}


void printValues() {
  Serial.print("x=");
  Serial.print(getX());
  Serial.print("   y=");
  Serial.println(getY());
}


bool readTouchPosition(Position *pos) {
  TSPoint p = ts.getPoint();
  if (ts.pressure() > ts.pressureThreshhold) {
    pos->x = TOUCH_X_SIZE_MM - mapfloat(constrain(p.x, 0, 1023), TOUCH_X_MIN, TOUCH_X_MAX, 0, TOUCH_X_SIZE_MM);
    pos->y = TOUCH_Y_SIZE_MM - mapfloat(constrain(p.y, 0, 1023), TOUCH_Y_MIN, TOUCH_Y_MAX, 0, TOUCH_Y_SIZE_MM);
    return true;
  }
  return false;
  // pos->x = getX();
  // pos->y = getY();
}
