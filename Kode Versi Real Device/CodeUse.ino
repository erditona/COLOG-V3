#include <ESP8266WiFi.h>
#include <MQTT.h>
//#include "DHTesp.h"

//Define the relay pins
#define relay1 D1
#define relay2 D2

const char ssid[] = "Ditoo";
const char pass[] = "";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

//const int DHT_PIN = 21;

//DHTesp dhtSensor;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("erfahtech")) {
    Serial.print(".");
    delay(1000);
  }

  if (client.connected()) {
    Serial.println("\nconnected!");

    // Publish pesan dengan nilai "true" ke topik "urse/dito@gmail.com/statushadwareiot"
    client.publish("urse/dito@gmail.com/statushadwareiot", "true");
    Serial.println("Published 'true' to urse/dito@gmail.com/statushadwareiot");

    // Subscribe ke topik umum
    client.subscribe("urse/#");
  } else {
    Serial.println("\nconnection failed!");

    // Publish pesan dengan nilai "false" ke topik "urse/dito@gmail.com/statushadwareiot"
    client.publish("urse/dito@gmail.com/statushadwareiot", "false");
    Serial.println("Published 'false' to urse/dito@gmail.com/statushadwareiot");
  }
}

void pesanMasuk(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " : " + payload);

  if (topic == "urse/dito@gmail.com/kamar/lampu") {
    digitalWrite(relay1, payload.toInt() == 1 ? LOW : HIGH);
    // Serial.println("LED 1 state: " + String(digitalRead(relay1)));
  } else if (topic == "urse/dito@gmail.com/kamar/tv") {
    digitalWrite(relay2, payload.toInt() == 1 ? LOW : HIGH);
    // Serial.println("LED 2 state: " + String(digitalRead(relay2)));
  } else if (topic == "urse/dito@gmail.com/kamar/lampubaca") {
    digitalWrite(19, payload.toInt() == 1 ? HIGH : LOW);
    // Serial.println("LED 3 state: " + String(digitalRead(19)));
  } 
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin("broker.emqx.io", net);
  client.onMessage(pesanMasuk);

  connect();

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(19, OUTPUT);
//  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

void loop() {
  client.loop(); // Handle MQTT messages
  delay(10);     // Fixes some issues with WiFi stability

  // Cek koneksi WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected");

    // Publish pesan dengan nilai "false" ke topik "urse/dito@gmail.com/statushadwareiot"
    client.publish("urse/dito@gmail.com/statushadwareiot", "false");
    Serial.println("Published 'false' to urse/dito@gmail.com/statushadwareiot");

    // Reconnect WiFi dan MQTT jika diperlukan
    connect();
  }

  if (!client.connected()) {
    Serial.println("Client disconnected");
    
    // Publish pesan dengan nilai "false" ke topik "urse/dito@gmail.com/statushadwareiot"
    client.publish("urse/dito@gmail.com/statushadwareiot", "false");
    Serial.println("Published 'false' to urse/dito@gmail.com/statushadwareiot");
    
    connect();
  }

//  // Publish sensor data every 2 seconds.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

//    TempAndHumidity data = dhtSensor.getTempAndHumidity();
//    float temperature = data.temperature; // Get temperature value
//    float humidity = data.humidity;       // Get humidity value

//    client.publish("urse/dito@gmail.com/monitoring", String(temperature, 2)+'-'+String(humidity, 2));
    Serial.println("---");
  }
  // delay (1000);
}
