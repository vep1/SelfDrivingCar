#include "motor.h"
#include <SharpIR.h>

#define FIRpin A0
#define RIRpin A1
#define Fmotor1 2
#define Fmotor2 4
#define Rmotor1 7
#define Rmotor2 8
#define model 1080

//include motor states
bool steerState = false; //state for direction of steering
bool propState = false; //state for direction of propulsion
bool steerSS = true; //state for start/stop (steering)
bool propSS = false; //state for start/stop (propulsion)
// initialize components
SharpIR Fsensor = SharpIR(FIRpin, model); //front sensor
SharpIR Rsensor = SharpIR(RIRpin, model); //rear sensor
motor Fmotor = motor(Fmotor1, Fmotor2, false); //front motor (steering)
motor Rmotor = motor(Rmotor1, Rmotor2, true); //rear motor (propulsion)

 
void setup() {
  // serial comm
  Serial.begin(9600);
}

void loop() {
  int Freading = Fsensor.distance();
  int Rreading = Rsensor.distance();
  //Conditions for changing direction or coming to full stop
  if (Freading <= 15 && Rreading <= 15) { //should stop
    propSS = true;
    propSS = Rmotor.toggle(propState, propSS); //dstState = true shoukd result in stopping
    //Serial.println(1); //debugging
  }
  else if (Freading <= 15 || Rreading <= 15){ //should switch directions
    propState = Rmotor.toggle(propState, propSS);
    delay(200);
    steerSS = false;
    steerState = Fmotor.toggle(steerState, steerSS); //turn
    delay(200);
    steerSS = true; //straighten steering orientation
    steerSS = Fmotor.toggle(steerState, steerSS);
    //Serial.println(2); //debugging
  }
  else {
    //Serial.println(3); //debugging
  }
  //serial port debugging
  /*Serial.print(Freading);
  Serial.print("  ");
  Serial.println(Rreading);*/

  /*Serial.print(digitalRead(Fmotor1));
  Serial.print("  ");
  Serial.print(digitalRead(Fmotor2));
  Serial.print("  ");
  Serial.println(steerSS);*/

  Serial.print(digitalRead(Rmotor1));
  Serial.print("  ");
  Serial.print(digitalRead(Rmotor2));
  Serial.print("  ");
  Serial.println(propSS);
  
  delay(100); //can change later
}
