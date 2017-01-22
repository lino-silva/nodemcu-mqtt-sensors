#include <MqttButton.h>

MqttButton btn(12);

void setup()
{
  btn.setup();
}

void loop()
{
  int x = btn.read();
  delay(500);
}
