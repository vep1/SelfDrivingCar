#include <arduino.h>
#include "motor.h"

motor::motor(int pin1, int pin2, bool prop) {
  relay1 = pin1;
  relay2 = pin2;
  PorS = prop;
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}
bool motor::toggle(bool state, bool SS) { //true is backward, false is forward
  //state is used for switching directions. SS stands for start/stop.
  //prop is used to differentiate propulsion from steering motors.
  if (state == true && SS == false) { //switch from backward to forward
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    delay(200);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    //protect steering motors from grinding motion
    if (PorS==false) {
      delay(400);
      digitalWrite(relay1, LOW);
    }
    return false;
  }
  else if (state == false && SS == false) { //switch from forward to backward
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    delay(200);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    //protect steering motors from grinding motion
    if (PorS==false) {
      delay(400);
      digitalWrite(relay2, HIGH);
    }
    return true;
  }
  else { //stop mode is activated. only really useful for propulsion motors
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    return false;
  }
}
