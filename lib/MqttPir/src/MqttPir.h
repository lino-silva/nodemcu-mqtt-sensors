#ifndef MqttPir_h
#define MqttPir_h
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define CALIBRATIONSECS 30
#define DEBUG 1

class MqttPir
{
  public:
    MqttPir(uint8_t dpin);
    MqttPir(uint8_t dpin,unsigned long lockdownSeconds);
    void setup();
    uint8_t read();
    void setPin(uint8_t dpin);

  private:
    uint8_t _pin;
    uint8_t _calibrationsecs;
    unsigned long _pause;
    unsigned long _lastHigh;
    void calibration();
    uint8_t getMagicLockValue(uint8_t value);
};

#endif
