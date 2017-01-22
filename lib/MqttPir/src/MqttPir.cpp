#include "MqttPir.h"

MqttPir::MqttPir(uint8_t dpin){
  _pin = dpin;
  _calibrationsecs = CALIBRATIONSECS;
  _pause = 0;
  _lastHigh = millis();//reset
}

MqttPir::MqttPir(uint8_t dpin,unsigned long lockdownSeconds){
  _pin = dpin;
  _calibrationsecs = CALIBRATIONSECS;
  _pause = lockdownSeconds*1000;
  _lastHigh = millis()-_pause;//reset
}

void MqttPir::setup(){
  if(DEBUG) Serial.println("Setup Pir");
  pinMode(_pin, INPUT);
  digitalWrite(_pin, LOW);
  calibration();
  delay(50);
}

uint8_t MqttPir::read(){
  uint8_t value = digitalRead(_pin);
  if(DEBUG){ Serial.println("PIR: "); Serial.println(value); }
  return getMagicLockValue(value);
}

void MqttPir::setPin(uint8_t dpin){
  if(DEBUG){ Serial.println("PIR Pin: "); Serial.println(dpin); }
  _pin = dpin;
}

void MqttPir::calibration(){
    if(DEBUG){ Serial.print("calibrating sensor "); }
    for(int i = 0; i < _calibrationsecs; i++){
      if(DEBUG){ Serial.print("."); }
      delay(1000);
    }
    if(DEBUG){ Serial.println("SENSOR ACTIVE"); }
    delay(50);
}

uint8_t MqttPir::getMagicLockValue(uint8_t value){
  if(value==1){
    _lastHigh = millis();
    return 1;
  }else{
    if(millis()-_lastHigh>=_pause){
      return 0;
    }else{
      return 1;
    }
  }
}
