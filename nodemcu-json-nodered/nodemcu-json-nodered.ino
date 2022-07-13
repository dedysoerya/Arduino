#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Mavens 2G";
const char* password =  "adminmavens";
const char* mqttServer = "172.16.100.248";
const int mqttPort = 1883;
const char* mqttUser = "admin";
const char* mqttPassword = "adminmavens";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  Serial.println();
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
}
 
void loop() {
 
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
 
  JSONencoder["noUji"] = "PBN1000QA";
  JSONencoder["tid"] = "FA";
  JSONencoder["macAdd"] = "E4:CE:8F:4A:1E:DA";
  JSONencoder["terminal_id"] = "29";
  /*JsonArray& values = JSONencoder.createNestedArray("values");
 
  values.add(20);
  values.add(21);
  values.add(23);*/
 
  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
 
  if (client.publish("tag/detection", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }
 
  client.loop();
  Serial.println("-------------");
 
  delay(10000);

  JSONencoder["noUji"] = "PBN1000QA";
  JSONencoder["tid"] = "FA";
  JSONencoder["macAdd"] = "E4:CE:8F:4A:1E:DB";
  JSONencoder["terminal_id"] = "29";

  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
 
  if (client.publish("tag/detection", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }
 
  client.loop();
  Serial.println("-------------");
 
  delay(10000);
 
}
