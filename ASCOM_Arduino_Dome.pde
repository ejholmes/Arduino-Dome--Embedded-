// green yellow - black red

#include "Dome.h"
#include "Messenger.h"

Dome dome = Dome();
Messenger message = Messenger();

void setup(){
  Serial.begin(9600);
  Serial.flush();
  
  Serial.println("R ASCOM.Arduino.Dome");
  
  message.attach(messageCompleted);
  
}

void messageCompleted(){
  dome.interpretCommand(&message);
}

void loop(){
  while(Serial.available()) message.process(Serial.read());
}


