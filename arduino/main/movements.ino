void circle(double *a, double *b, double max_a, double max_b, double freq) {
  double w = 2 * M_PI * freq;
  
  double t = millis() / 1000.0;
  *a = max_a * sin(w * t);
  *b = max_b * cos(w * t);
}

void linear1d(double *a, double *incr, double max_value) {
  if (abs(*a) > max_value) {
    *incr *= -1;
  }
  *a += *incr;
}

void sine_movement(double *a, double max_value, double freq) {
  *a = max_value * sin(2 * M_PI * freq * millis() / 1000.0);
}