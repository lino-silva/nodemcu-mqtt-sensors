#include "MqttHcsr04.h"

MqttHcsr04::MqttHcsr04(uint8_t dpintrig,uint8_t dpinecho){
  _dpintrig = dpintrig;
  _dpinecho = dpinecho;
}

void MqttHcsr04::setup(){
  if(DEBUG) Serial.println("Setup hcsr04");
  pinMode(_dpintrig, OUTPUT);
	pinMode(_dpinecho, INPUT);
}

float MqttHcsr04::read(){
  float duration, distance;
	digitalWrite(_dpintrig, LOW);
	delayMicroseconds(2);
	digitalWrite(_dpintrig, HIGH);
	delayMicroseconds(10);
	digitalWrite(_dpintrig, LOW);
	duration = pulseIn(_dpinecho, HIGH);
	distance = duration/58.2;
  if(DEBUG){ Serial.println("Distance: "); Serial.println(distance); }
	return distance;
}

void MqttHcsr04::setPin(uint8_t dpintrig,uint8_t dpinecho){
  if(DEBUG){ Serial.print("Trig: "); Serial.print(dpintrig);  Serial.print(" Echo: "); Serial.println(dpinecho); }
  _dpintrig = dpintrig;
  _dpinecho = dpinecho;
}
