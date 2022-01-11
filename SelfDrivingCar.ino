#include "motor.h"
#include <SharpIR.h>
#include <string.h>
#include "DFRobot_LedDisplayModule.h"
DFRobot_LedDisplayModule LED(Wire, 0x48); // address and Wire begin

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

//int array for 7seg board
int fill[4] ={0, 0, 0, 0};

// initialize components
SharpIR Fsensor = SharpIR(FIRpin, model); //front sensor
SharpIR Rsensor = SharpIR(RIRpin, model); //rear sensor
motor Fmotor = motor(Fmotor1, Fmotor2, false); //front motor (steering)
motor Rmotor = motor(Rmotor1, Rmotor2, true); //rear motor (propulsion)

//function prototype for 7seg display update
void updateReadings(int i, int j);

void setup() {
  // serial comm
  Serial.begin(9600);

  // Initialize 7Seg module and settings
  LED.begin4();
  LED.setDisplayArea4(1, 2, 3, 4); //82 to shut lower displays off;
  LED.setBrightness4(1);
}

void loop() {
  int Freading = Fsensor.distance();
  int Rreading = Rsensor.distance();
  //Conditions for changing direction or coming to full stop
  if (Freading <= 15 && Rreading <= 15) {               //should stop
    propSS = true;
    propSS = Rmotor.toggle(propState, propSS);          //dstState = true shoukd result in stopping
    Serial.println(1); //debugging
  }
  else if (Freading <= 15 || Rreading <= 15){           //should switch directions
    propState = Rmotor.toggle(propState, propSS);
    delay(200);
    steerSS = false;
    steerState = Fmotor.toggle(steerState, steerSS);    //turn
    delay(200);
    steerSS = true;                                     //straighten steering orientation
    steerSS = Fmotor.toggle(steerState, steerSS);
    Serial.println(2); //debugging
  }
  else {
    Serial.println(3); //debugging
  }

  //send sensor readings to 7seg
  if (Freading>99) {
    Freading = 99;                         //prevent sensor readings from overflowing double digit capacity of display
  }
  if (Rreading>99) {
    Rreading = 99;                         //prevent sensor readings from overflowing double digit capacity of display
  }
  updateReadings(Freading, Rreading); //update readings
  
  //serial port debugging
  Serial.print(Freading);
  Serial.print("  ");
  Serial.println(Rreading);

  /*Serial.print(digitalRead(Fmotor1));
  Serial.print("  ");
  Serial.print(digitalRead(Fmotor2));
  Serial.print("  ");
  Serial.println(steerSS);*/

  /*Serial.print(digitalRead(Rmotor1));
  Serial.print("  ");
  Serial.print(digitalRead(Rmotor2));
  Serial.print("  ");
  Serial.println(propSS);*/
  
  delay(100); //can change later
}

void updateReadings(int i, int j) {
   //cut readings up for each digit
      fill[0] = i%10;                     //returns ones place (i)
      fill[1] = (i-(i%10))/10;      //returns tens place (i)
      fill[2] = j%10;                     //returns ones place (j)
      fill[3] = (j-(j%10))/10;      //returns tens place (j)
      
    char dig0[] = {'0'+fill[0]}; // store individual digits in char arrays
    char dig1[] = {'0'+fill[1]};
    char dig2[] = {'0'+fill[2]};
    char dig3[] = {'0'+fill[3]};
    LED.print4(dig3, dig2, dig1, dig0); //takes int or character array
}
