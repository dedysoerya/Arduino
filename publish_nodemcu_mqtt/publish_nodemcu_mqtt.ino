#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "BT1";
const char* password = "admin123";

// Change the variable to your Server IP address, so it connects to your MQTT broker
const char* mqtt_server = "118.98.64.213";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient22;
PubSubClient client(espClient22);


// Lamp - LED - GPIO 4 = D2 on ESP-12E NodeMCU board
const int led = 13;


//Connect your NodeMCU to your router
void setup_wifi() {
  delay(10);
  
  Serial.println();
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - NodeMCU IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    
    if (client.connect("ESP8266Client22")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      //client.subscribe("room/light");
      client.publish("sensor/suhu","helo world");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);

}

// For this project, you don't need to change anything in the loop function. Basically it ensures that the NodeMCU is connected to MQTT broker
void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client22");

  }
  
