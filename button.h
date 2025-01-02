//////// BUTTON CLASS ////////
#include "Arduino.h"

byte button(void) {
  if (analogRead(0) < 100) return 5;
  else if (analogRead(0) < 200) return 3;
  else if (analogRead(0) < 400) return 4;
  else if (analogRead(0) < 500) return 2;
  else if (analogRead(0) < 800) return 1;
  else return 0;
}