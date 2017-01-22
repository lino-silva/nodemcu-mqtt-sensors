#ifndef MqttRelay_h
#define MqttRelay_h
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define MQTTRELAYTYPE_GND 0
#define MQTTRELAYTYPE_VCC 1
#define DEBUG 1

class MqttRelay
{
  public:
    MqttRelay(uint8_t dpin);
    MqttRelay(uint8_t dpin,uint8_t connectionType);
    MqttRelay(uint8_t dpin,uint8_t connectionType,uint8_t initialState);
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
