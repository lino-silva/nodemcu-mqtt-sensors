#include "MqttLdr.h"

MqttLdr::MqttLdr(uint8_t apin){
  _pin = apin;
  _bottomLimit = BOTTOMLIMIT;
  _topLimit = TOPLIMIT;
  _minVoltage = MINVOLTAGE;
  _maxVoltage = MAXVOLTAGE;
}

MqttLdr::MqttLdr(uint8_t apin,long bottomLimit,long topLimit){
  _pin = apin;
  _bottomLimit = bottomLimit;
  _topLimit = topLimit;
  _minVoltage = MINVOLTAGE;
  _maxVoltage = MAXVOLTAGE;
}

MqttLdr::MqttLdr(uint8_t apin,long bottomLimit,long topLimit,long minVoltage, long maxVoltage){
  _pin = apin;
  _bottomLimit = bottomLimit;
  _topLimit = topLimit;
  _minVoltage = minVoltage;
  _maxVoltage = maxVoltage;
}

void MqttLdr::setup(){
  if(DEBUG) Serial.println("Setup Ldr");
}

long MqttLdr::read(){
  int value = analogRead(_pin);
  if(DEBUG){ Serial.print("LDR: "); Serial.println(value); }
  return map(value, _minVoltage, _maxVoltage, _bottomLimit, _topLimit);
}

void MqttLdr::setPin(int dpin){
  if(DEBUG){ Serial.print("LDR Pin: "); Serial.println(dpin); }
  _pin = dpin;
}

void MqttLdr::setVoltage(long minVoltage, long maxVoltage){
  if(DEBUG){ Serial.print("LDR voltage ["); Serial.print(minVoltage); Serial.print(","); Serial.print(maxVoltage); Serial.println("]"); }
  _minVoltage = minVoltage;
  _maxVoltage = maxVoltage;
}

void MqttLdr::setLimits(long bottomLimit,long topLimit){
  if(DEBUG){ Serial.print("LDR limit ["); Serial.print(bottomLimit); Serial.print(","); Serial.print(topLimit); Serial.println("]"); }
  _bottomLimit = bottomLimit;
  _topLimit = topLimit;
}
