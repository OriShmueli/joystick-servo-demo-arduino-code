#include <Arduino.h>
#include <Servo.h>

#define VRX_PIN A0;
#define VRY_PIN A1;

Servo Base_Servo;
int baseServoStartingPostion = 0;
int baseServoPin = 9;

void basicCharSending(const char* message);
void establishConnectionWithComputer();
bool connectedToComputer = false;
const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

int xValue = 0;
int yValue = 0;

int PrevValueX = 0;
int PrevValueY = 0;

void setup() {
    Serial.begin(1000000);
    Base_Servo.attach(baseServoPin);
}

void loop() {
  unsigned long currentTime = millis();
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  
  while (Serial.available() > 0)    
  {
    if(!establishConnectionWithComputer){
      establishConnectionWithComputer()
    }else{
      char getByte = Serial.read();
      if(getByte == 'c'){
        
      }
    }
    /*if(currentTime - previousTime >= eventInterval){
      previousTime = currentTime;
    }*/
   
  }
}

void basicCharSending(const char* message){
  char getByte = Serial.read();
  if(getbyte == '')
}

void establishConnectionWithComputer(){

}