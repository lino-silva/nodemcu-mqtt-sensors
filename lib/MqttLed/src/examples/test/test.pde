#include <MqttLed.h>

MqttLed led(12,MQTTLEDTYPE_GND,0);

void setup()
{
  led.setup();
}

void loop()
{
  led.on();
  delay(500);
  led.off();
  delay(500);
}
