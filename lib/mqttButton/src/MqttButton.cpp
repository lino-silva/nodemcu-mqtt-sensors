#include "MqttButton.h"

#define MIN_INTERVAL 2000

MqttButton::MqttButton(uint8_t dpin){
  _pin = dpin;
}

void MqttButton::setup(){
  if(DEBUG) Serial.println("Setup Button");
  pinMode(_pin, INPUT_PULLUP);
}

uint8_t MqttButton::read(){
  uint8_t value = digitalRead(_pin);
  if(DEBUG){ Serial.println("Button: "); Serial.println(value); }
  return value;
}

void MqttButton::setPin(uint8_t dpin){
  if(DEBUG){ Serial.println("Button Pin: "); Serial.println(dpin); }
  _pin = dpin;
}
