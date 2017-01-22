#include <MqttPir.h>

MqttPir pir(12,2);//Lock 2s

void setup()
{
  pir.setup();
}

void loop()
{
  int x = pir.read();
  delay(500);
}
