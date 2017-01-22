#include <MqttHcsr04.h>

MqttHcsr04 hcsr04(12);

void setup()
{
  hcsr04.setup();
}

void loop()
{
  float x = hcsr04.read();
  delay(500);
}
