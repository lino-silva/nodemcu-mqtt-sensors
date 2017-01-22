#include "MqttRelay.h"

MqttRelay::MqttRelay(uint8_t dpin)
{
  _pin = dpin;
  _type = MQTTRELAYTYPE_GND;
  _initialState = 0;
}

MqttRelay::MqttRelay(uint8_t dpin,uint8_t connectionType){
  _pin = dpin;
  _type = connectionType;
  _initialState = 0;
}

MqttRelay::MqttRelay(uint8_t dpin,uint8_t connectionType,uint8_t initialState){
  _pin = dpin;
  _type = connectionType;
  _initialState = initialState;
}

void MqttRelay::setup(){
  if(DEBUG) Serial.println("Setup Relay");
  pinMode(_pin, OUTPUT);
  if(_initialState==1){
    on();
  }else{
    off();
  }
}

void MqttRelay::on()
{
  if(DEBUG){ Serial.println("Relay: ON"); }
  if(_type==MQTTRELAYTYPE_VCC){
    digitalWrite(_pin, HIGH);
  }else{
    digitalWrite(_pin, LOW);
  }
}

void MqttRelay::off()
{
  if(DEBUG){ Serial.println("Relay: OFF"); }
  if(_type==MQTTRELAYTYPE_VCC){
    digitalWrite(_pin, LOW);
  }else{
    digitalWrite(_pin, HIGH);
  }
}

void MqttRelay::setPin(uint8_t dpin){
  if(DEBUG){ Serial.println("RELAY Pin: "); Serial.println(dpin); }
  _pin = dpin;
}

void MqttRelay::setType(uint8_t connectionType){
  if(DEBUG){ Serial.println("RELAY type: "); Serial.println(connectionType); }
  _type = connectionType;
}
