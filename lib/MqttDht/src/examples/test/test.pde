#include <MqttDht.h>

MqttDht dht(12,DHT22);

void setup()
{
  dht.setup();
}

void loop()
{
  float x = dht.temperature();
  float x = dht.temperature(FAHRENHEIT);//Fahrenheit
  float y = dht.humidity();
  delay(500);
}
