#include "MqttLed.h"

MqttLed::MqttLed(uint8_t dpin)
{
  _pin = dpin;
  _type = MQTTLEDTYPE_GND;
  _initialState = 0;
}

MqttLed::MqttLed(uint8_t dpin,uint8_t connectionType){
  _pin = dpin;
  _type = connectionType;
  _initialState = 0;
}

MqttLed::MqttLed(uint8_t dpin,uint8_t connectionType,uint8_t initialState){
  _pin = dpin;
  _type = connectionType;
  _initialState = initialState;
}

void MqttLed::setup(){
  if(DEBUG) Serial.println("Setup Led");
  pinMode(_pin, OUTPUT);
  if(_initialState==1){
    on();
  }else{
    off();
  }
}

void MqttLed::on()
{
  if(DEBUG){ Serial.println("Led: ON"); }
  if(_type==MQTTLEDTYPE_VCC){
    digitalWrite(_pin, HIGH);
  }else{
    digitalWrite(_pin, LOW);
  }
}

void MqttLed::off()
{
  if(DEBUG){ Serial.println("Led: OFF"); }
  if(_type==MQTTLEDTYPE_VCC){
    digitalWrite(_pin, LOW);
  }else{
    digitalWrite(_pin, HIGH);
  }
}

void MqttLed::setPin(uint8_t dpin){
  if(DEBUG){ Serial.println("LED Pin: "); Serial.println(dpin); }
  _pin = dpin;
}

void MqttLed::setType(uint8_t connectionType){
  if(DEBUG){ Serial.println("LED type: "); Serial.println(connectionType); }
  _type = connectionType;
}
