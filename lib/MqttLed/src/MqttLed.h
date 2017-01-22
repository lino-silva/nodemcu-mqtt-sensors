#ifndef MqttLed_h
#define MqttLed_h
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define MQTTLEDTYPE_GND 0
#define MQTTLEDTYPE_VCC 1
#define DEBUG 1

class MqttLed
{
  public:
    MqttLed(uint8_t dpin);
    MqttLed(uint8_t dpin,uint8_t connectionType);
    MqttLed(uint8_t dpin,uint8_t connectionType,uint8_t initialState);
    void setup();
    void on();
    void off();
    void setPin(uint8_t dpin);
    void setType(uint8_t connectionType);

  private:
    uint8_t _pin;
    uint8_t _type;
    uint8_t _initialState;
};

#endif
