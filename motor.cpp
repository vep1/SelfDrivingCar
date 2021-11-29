#include <arduino.h>
#include "motor.h"

motor::motor(int pin1, int pin2) {
  relay1 = pin1;
  relay2 = pin2;
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}
bool motor::toggle(bool state, bool SS) { //true is backward, false is forward
  if (state == true && SS == false) { //switch from backward to forward
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    delay(500);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    delay(500);
    return false;
  }
  else if (state == false && SS == false) { //switch from forward to backward
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    delay(500);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    delay(500);
    return true;
  }
  else { //stop mode is activated
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    return false;
  }
}
