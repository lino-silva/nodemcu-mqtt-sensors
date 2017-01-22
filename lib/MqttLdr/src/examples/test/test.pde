#include <MqttLdr.h>

MqttLdr ldr(12);

void setup()
{
  ldr.setup();
}

void loop()
{
  long x = ldr.read();
  delay(500);
}
