#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include <ESP8266WebServer.h>

const uint DEBUG = 1;

const uint MAX_MQTT_CONNECT_TRY = 30;
const char* MQTT_SERVER = "raspitagram.lan";
const int MQTT_PORT = 1883;
const int MQTT_MESSAGE_INTERVAL = 5000;
long lastMsg;

const uint MAX_WIFI_CONNECT_TRY = 60;
const char* WLAN_SSID = "Efesios 4:28";
const char* WLAN_PWD = "naohapacienciapraisso";

const char* TEMPERATURE_MQTT_TOPIC_PUB = "home/livingroom/temperature";
const char* HUMIDITY_MQTT_TOPIC_PUB = "home/livingroom/humidity";
const char* LDR_MQTT_TOPIC_PUB = "home/livingroom/ldr";
const char* LED_MQTT_TOPIC_SUB = "home/livingroom/led";
const char* RELAY_MQTT_TOPIC_SUB = "home/livingroom/relay";
const char* PIR_MQTT_TOPIC_PUB = "home/livingroom/pir";
const char* HCSR04_MQTT_TOPIC_PUB = "home/livingroom/hcsr04";

WiFiClient espClient;
PubSubClient client(espClient);

ESP8266WebServer webServer(80);

bool OTAUpdate = false;
long OTATimeout = 60*1000;
long OTAend=0;

#include "MqttRelay.h"
#include "MqttLed.h"
#include "MqttLdr.h"
#include "MqttPir.h"
#include "MqttDht.h"
#include "MqttHcsr04.h"
#include "MqttButton.h"

MqttDht dht(13,DHT22);
MqttHcsr04 hcsr04(5,3);
MqttRelay relay(4,MQTTRELAYTYPE_GND,0);
MqttLed led(12,MQTTLEDTYPE_GND,0);
MqttLdr ldr(17);
MqttPir pir(15,2);
MqttButton btn(14);

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

void setup() {
  if (DEBUG) Serial.begin(115200);

  setup_wifi();
  webServer.on("/update", handleRoot);
  webServer.begin();
  if (DEBUG) Serial.println("HTTP server started");
  bindOTAEvents();
  relay.setup();
  led.setup();
  pir.setup();
  ldr.setup();
  btn.setup();
  hcsr04.setup();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqtt_callback);
}

void loop(){
   if(OTAUpdate && millis()-OTAend>0){
     ArduinoOTA.handle();
   }else{
    OTAUpdate=false;
    webServer.handleClient();
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lastMsg > MQTT_MESSAGE_INTERVAL) {
      lastMsg = now;
      Dht22();
      readLdr();
    }
    PIR();
    readHcsr04();
  }
}

void handleRoot() {
  if (DEBUG) Serial.println("GOT OTA cmd");
  OTAUpdate = true;
  OTAend = millis()+OTATimeout;
  webServer.send(200, "text/plain", "GO");
  if (DEBUG) Serial.println("Start OTA");
}

void mqtt_callback(const char* topic, byte* payload, unsigned int length)
{
  if (DEBUG) Serial.print("Got message from ");
  if (DEBUG) Serial.println(topic);
  if (DEBUG) Serial.print("Payload: ");
  if (DEBUG) Serial.println((int) payload[0]);
  if (strcmp(topic, LED_MQTT_TOPIC_SUB)==0) {
   if ((int) payload[0] == 48) {
      led.off();
    } else {
      led.on();
    }
  }else
  if(strcmp(topic, RELAY_MQTT_TOPIC_SUB)==0){
    if ((int) payload[0] == 48) {
       relay.off();
     } else {
       relay.on();
     }
  }
}

void bindOTAEvents(){
  ArduinoOTA.onStart([]() {

    if (DEBUG) Serial.println("Start updating ");
  });

  ArduinoOTA.onEnd([]() {
    if (DEBUG) Serial.println("\nEnd");
    OTAUpdate =false;
    delay(100);
    ESP.restart();
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    if (DEBUG) Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    if (DEBUG) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
    }
    delay(100);
    ESP.restart();
  });

  ArduinoOTA.setPort(9069);
  ArduinoOTA.setPassword("M4yTh3F0rc3B3W1thY0u");
  ArduinoOTA.begin();
}

void setup_wifi() {
  int xTry = 0;
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PWD);

  while (WiFi.status() != WL_CONNECTED && ++xTry < MAX_WIFI_CONNECT_TRY) {
    delay(500);
    Serial.print(".");
  }
  if(WiFi.status() != WL_CONNECTED ){
    Serial.println("Wifi Failed.. Restarting");
    delay(100);
    ESP.restart();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  int xTry = 0;

  while (!client.connected() && ++xTry < MAX_MQTT_CONNECT_TRY) {
    Serial.print("Attempting MQTT connection...");
    Serial.print(xTry);

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");

      client.subscribe(LED_MQTT_TOPIC_SUB);
      client.subscribe(RELAY_MQTT_TOPIC_SUB);

      Serial.print("Subscribed to ");
      Serial.println(LED_MQTT_TOPIC_SUB);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
  if(!client.connected()){
    Serial.println("Mqtt Failed.. Restarting");
    delay(100);
    ESP.restart();
  }
}

void PIR(){
  char val[2];
  int x = pir.read();
  String(x).toCharArray(val,2);
  client.publish(PIR_MQTT_TOPIC_PUB, val);
  Serial.print("PIR: ");Serial.println(x);
}

void Dht22(){
  char temp[10];
  char hum[10];

  float tempVal = dht.temperature();

  if (!isnan(tempVal)) {
    String(tempVal).toCharArray(temp, 10);
    client.publish(TEMPERATURE_MQTT_TOPIC_PUB, temp);
  }
  float humidVal = dht.humidity();
  if (!isnan(humidVal)) {
    String(humidVal).toCharArray(hum, 10);
    client.publish(HUMIDITY_MQTT_TOPIC_PUB, hum);
  }
}

void readHcsr04(){
  char val[10];
  long value = hcsr04.read();
  if (!isnan(value)) {
    String(value).toCharArray(val,10);
    client.publish(HCSR04_MQTT_TOPIC_PUB, val);
  }
}

void readLdr(){
  char ldrx[10];
  long value = ldr.read();
  if (!isnan(value)) {
    String(value).toCharArray(ldrx,10);
    client.publish(LDR_MQTT_TOPIC_PUB, ldrx);
  }
}
