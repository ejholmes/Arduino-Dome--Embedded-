

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "WProgram.h"
#include "Dome.h"

AF_Stepper motor(360 / DEGREES_PER_STEP, 2); // Create our stepper motor. I have mine on port 2 of the motor shield.

long parkPosition = 0;
Position position(FULLROTATION);

//
// Constructor
// 
Dome::Dome(void)
{
  motor.setSpeed(100); // Set a default RPM of 10
  //position = 0;
}

//
// Function for interpreting a command string of the format ": COMMAND <ARGUMENT> #"
//
void Dome::interpretCommand(Messenger *message)
{
  message->readChar(); // Reads ":"
  char command = message->readChar(); // Read the command
  
  switch(command){
    case 'P':
      Park();
      break;
    case 'O':
      OpenCloseShutter(message->readInt());
      break;
    case 'S':
      Slew(message->readLong());
      break;
    case 'H':
      AbortSlew();
      break;
    case 'T':
      SyncToAzimuth(message->readInt());
      break;
  }
}

void Dome::step(long val)
{
  long lastAz = 0;
  if (val > 0) { // If move is positive, move forward
    while(val--)
    {
      if(Serial.available() > 0)
        break;
      motor.step(1, BACKWARD, DOUBLE);
      position++;
    }
  }
  else if (val < 0) { // else if move is negative, move backward
    long counter = abs(val);
    while(counter--)
    {
      if(Serial.available() > 0)
        break;
      motor.step(1, FORWARD, DOUBLE);
      position--;
    }
  } 
}

void Dome::AbortSlew()
{
}

void Dome::Slew(long azimuth)
{
  step(position.Quickest(azimuth));
  
  PrintAzimuth();
}

void Dome::PrintAzimuth()
{
  Serial.print("P ");
  Serial.println(position.Degrees());
}

void Dome::Park()
{
  Slew(parkPosition);
}

void Dome::OpenCloseShutter(int open)
{
  switch(open)
  {
    case 1:
      Serial.println("SHUTTER OPEN");
      break;
    case 0:
      Serial.println("SHUTTER CLOSED");
      break;
  }
}

void Dome::SyncToAzimuth(long azimuth)
{
  PrintAzimuth();
}
