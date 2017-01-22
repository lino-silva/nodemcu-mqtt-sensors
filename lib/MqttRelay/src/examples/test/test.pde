#include <MqttRelay.h>

MqttRelay relay(4,MqttRelayType_GND,0);

void setup()
{
  relay.setup();
}

void loop()
{
  relay.on();
  delay(500);
  relay.off();
  delay(500);
}
