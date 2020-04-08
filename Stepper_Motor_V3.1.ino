/********************************************************************************************
*Project:              Stepper motor control with Blynk App                                 *
*Author:               Epic Electronics                                                     *
*Youtube channel:      https://www.youtube.com/channel/UCUvW5tOMS4KRXxMFt33XYvg/featured    *
*Programming Date:     10.02.2020                                                           *
*Version:              V3.1                                                                 *
*Last Update:          08.04.2020                                                           *
*Video from project:   https://youtu.be/elKlWb9ru5o                                         *
*                                                                                           *
*About:   The program reads the actual state from the blynk app and controls a steppermotor.*
*         If the button on the blynk app is trigged, the steppermotor rotats in the given   *
*         direction 10 times for 360 degree, total 3600 degree.                             *
********************************************************************************************/

#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


Stepper my_Stepper(200, D8, D7, D6, D5);

bool Right = false;
bool Left = false;

char auth[] = "Put your auth token here";
char ssid[] = "Put your network name here";
char pass[] = "put your passwort here";


//++ Start Setup +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup(){
  
  Blynk.begin(auth, ssid, pass);                      // network information 
  my_Stepper.setSpeed(70);                            // Speed for stepper motor
  Serial.begin(9600);                                 // baudrate for serial comunication
}
//-- Setup End ---------------------------------------------------------------------------------------------------------------------


BLYNK_WRITE(V1){                                      // read input from virtual pin V1
  Right = param.asInt();                              // assigning incoming value from pin V§1 to a variable
  }
  
BLYNK_WRITE(V0){                                      // read input from virtual pin V0
  Left = param.asInt();                               // assigning incoming value from pin V0 to a variable
  }
  
void Stepper1 (int Direction, int Rotation){          // function for stepper motor control with 2 parameters
  for (int i = 0; i < Rotation; i++){                 // for loop 
  my_Stepper.step(Direction * 200);                   // 200 is 360 degree => change value if smaller then 360 degree is needing
  Blynk.run();
  }
}

//++ Start Loop +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop() {   
  
  Blynk.run();
  
  if (Right){                                          // if condition 
  Stepper1(1, 10);                                     // steppermotor rotates 10 times 360 degree right
  }
  delay(20);                                           // delay 20ms
  
  if (Left){                                           // if condition 
  Stepper1(-1, 10);                                    // steppermotor rotates 10 times 360 degree left
  }
  delay(20);                                           // delay 20ms
}
//-- Loop End ---------------------------------------------------------------------------------------------------------------------
