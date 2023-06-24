#include <Arduino.h>
#include <Servo.h>

Servo Base_Servo;
int baseServoStartingPostion = 0;
int baseServoPin = 9;

void basicCharSending(const char* message);
void establishConnectionWithComputer();

void setup() {
    Serial.begin(1000000);
    Base_Servo.attach(baseServoPin);
}

void loop() {
  while (Serial.available() > 0)    
  {
    
  }
}

void basicCharSending(const char* message){

}

void establishConnectionWithComputer(){

}