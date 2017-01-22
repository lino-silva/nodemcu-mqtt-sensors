#ifndef MqttLdr_h
#define MqttLdr_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define MINVOLTAGE 1024
#define MAXVOLTAGE 0
#define BOTTOMLIMIT 0
#define TOPLIMIT 100000
#define DEBUG 1

class MqttLdr
{
  public:
    MqttLdr(uint8_t apin);
    MqttLdr(uint8_t apin,long bottomLimit,long topLimit);
    MqttLdr(uint8_t apin,long bottomLimit,long topLimit,long minVoltage, long maxVoltage);
    void setup();
    long read();
    void setPin(int dpin);
    void setVoltage(long minVoltage, long maxVoltage);
    void setLimits(long bottomLimit,long topLimit);

  private:
    uint8_t _pin;
    long _bottomLimit;
    long _topLimit;
    long _minVoltage;
    long _maxVoltage;
};

#endif
