
void setup();
void loop();
void handleRoot();
void mqtt_callback(const char* topic, byte* payload, unsigned int length);
void bindOTAEvents();
void setup_wifi();
void reconnect();
void PIR();
void Dht22();
void readHcsr04();
void readLdr();
