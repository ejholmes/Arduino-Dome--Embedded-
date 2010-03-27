
#ifndef Dome_h
#define Dome_h

#define DEGREES_PER_STEP 1.8

#define FULLROTATION 20000
#define MINSPEED 10
#define MAXSPEED 150

#include <inttypes.h>
#include <avr/io.h>
#include "AFMotor.h"
#include "Messenger.h"
#include "Position.h"

class Dome
{
  public:
    Dome(void);
    void interpretCommand(Messenger *message);
    void Park();
    void OpenCloseShutter(int open);
    void Slew(long val);
    void AbortSlew();
    void SyncToAzimuth(long azimuth);
  private:
    void step(long val);
    long GetAzimuth();
    long GetPosition(long azimuth);
    void PrintAzimuth();
    long parkPosition;
};

#endif
