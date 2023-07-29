#include <Arduino.h>
#include <Servo.h>

#define VRX_PIN A0
#define VRY_PIN A1

Servo Base_Servo;
int baseServoStartingPostion = 0;
int baseServoPin = 9;

void basicCharSending(const char* message);
void EstablishConnectionWithComputer(const char* message);
void TimerFunctionSendMessage(const char* message);
bool establishConnectionWithComputer = false;
bool connectedToComputer = false;
const unsigned long eventInterval = 3000;
unsigned long previousTime = 0;
unsigned long currentTime;
bool getSYN = false;
bool getACK = false;
int timesUntillDisconnection = 5;
int xValue = 0;
int yValue = 0;



int PrevValueX = 0;
int PrevValueY = 0;

enum TimingReceiveDataStates { SYN, SYNERR, ACK, ACKERR, JOY, DIS, CONNECTED, DISCONNECTED };
TimingReceiveDataStates currentState;
void setup() {
  currentState = DISCONNECTED;
  Serial.begin(1000000);
  Base_Servo.attach(baseServoPin);
}

void loop() {
  currentTime = millis();
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  
  while (Serial.available() > 0)    
  {
    if(!establishConnectionWithComputer){
      EstablishConnectionWithComputer(Serial.read());
    }else{
     
      char getByte = Serial.read();
      if(getByte == 'c'){
        
      }

      if(getByte == 'ds'){
        establishConnectionWithComputer = false;
      }
    }
    /**/
   
  }

  if(currentTime - previousTime >= eventInterval){
      switch (currentState)
      {
      case SYN:
          TimerFunctionSendMessage('SYN');
        break;
      
      case SYNERR:
          TimerFunctionSendMessage('v');
        break;

      case ACK:
          TimerFunctionSendMessage('ACK');
        break;

      case ACKERR:
          TimerFunctionSendMessage('v');
        break;

      case JOY:

        break;

      case DIS:

        break;

      case CONNECTED:
      
        break;

      case DISCONNECTED:
        
        break;
      
      default:
        break;
      }
      previousTime = currentTime;
  }
}

void BasicCharSending(const char* message){
  
}


void TimerFunctionSendMessage(const char* message){
  Serial.write(message);
  timesUntillDisconnection =-1;
  if(timesUntillDisconnection == 0){
    currentState = DISCONNECTED;
    establishConnectionWithComputer = false;
    timesUntillDisconnection = 5;
    getSYN = false;
  }
}

bool CheckReceivedMessage(const char* message, const char* requiredMessage, unsigned long eventInterval){
  unsigned long previousTime = 0;
  bool sendErrorState = true;
  while(true){
    unsigned long currentTime = millis();
    if(message == requiredMessage){
      return true;
    }else{
     sendErrorState = true;
      if(currentTime - previousTime >= eventInterval){
        sendErrorState = false;

        previousTime = currentTime;
      }
      
      if(sendErrorState){
        Serial.write('v');
      }
    }
  }
}

void EstablishConnectionWithComputer(const char* incomingByte){
  currentState = DIS;
    if(getSYN){
      if(incomingByte == 'ACK'){
        
        //Serial.write('ACK');
        establishConnectionWithComputer = true;
        currentState = CONNECTED;
         timesUntillDisconnection = 3;
      }else if(incomingByte == 'v'){
       Serial.write('ACK');
       previousTime = currentTime;
       currentState = ACK;
       timesUntillDisconnection = 3;
      }else{
        Serial.write('v');
        previousTime = currentTime;
        currentState = ACKERR;
         timesUntillDisconnection = 3;
      }
    }else{
     

      if(incomingByte == 'SYN'){
        getSYN = true;
        Serial.write('SYN');
        currentState = SYN;
        //reset timer
        previousTime = currentTime;
        timesUntillDisconnection = 3;
        /*if(currentState == SYN){
          currentState = DIS;
        }*/
       
      }else if(incomingByte == 'v'){
        Serial.write('SYN');
        currentState = SYNERR;
        timesUntillDisconnection = 3;
        //reset timer
        previousTime = currentTime;
        /*if(currentState == SYNERR){
          currentState = DIS;
        }*/
        
      }else{
        Serial.write('v');
        currentState = SYNERR;
        timesUntillDisconnection = 3;
        previousTime = currentTime;
      }
    }
  
}