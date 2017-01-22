#ifndef MqttHcsr04_h
#define MqttHcsr04_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define DEBUG 1

class MqttHcsr04
{
  public:
    MqttHcsr04(uint8_t dpintrig,uint8_t dpinecho);

    void setup();
    float read();
    void setPin(uint8_t dpintrig,uint8_t dpinecho);

  private:
    uint8_t _dpintrig;
    uint8_t _dpinecho;
};

#endif
