#ifndef MqttButton_h
#define MqttButton_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define DEBUG 1

class MqttButton
{
  public:
    MqttButton(uint8_t dpin);

    void setup();
    uint8_t read();
    void setPin(uint8_t dpin);

  private:
    uint8_t _pin;
};

#endif
