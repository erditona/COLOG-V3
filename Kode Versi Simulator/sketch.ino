#include <WiFi.h>
#include <MQTT.h>
#include "DHTesp.h"

const char ssid[] = "Wokwi-GUEST";
const char pass[] = "";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

const int DHT_PIN = 21;

DHTesp dhtSensor;

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

    // Publish pesan dengan nilai "true" ke topik "urse/email@gmail.com/statushadwareiot"
    client.publish("urse/email@gmail.com/statushadwareiot", "true");
    Serial.println("Published 'true' to urse/email@gmail.com/statushadwareiot");

    // Subscribe ke topik umum
    client.subscribe("urse/#");
  } else {
    Serial.println("\nconnection failed!");

    // Publish pesan dengan nilai "false" ke topik "urse/email@gmail.com/statushadwareiot"
    client.publish("urse/email@gmail.com/statushadwareiot", "false");
    Serial.println("Published 'false' to urse/email@gmail.com/statushadwareiot");
  }
}


void pesanMasuk(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " : " + payload);

  if (topic == "urse/email@gmail.com/kamar/lampu") {
    digitalWrite(5, payload.toInt());
    // Serial.println("LED 1 state: " + String(digitalRead(5)));
  } else if (topic == "urse/email@gmail.com/kamar/tv") {
    digitalWrite(18, payload.toInt());
    // Serial.println("LED 2 state: " + String(digitalRead(18)));
  } else if (topic == "urse/email@gmail.com/kamar/lampubaca") {
    digitalWrite(19, payload.toInt());
    // Serial.println("LED 3 state: " + String(digitalRead(19)));
  } 
}



void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin("broker.emqx.io", net);
  client.onMessage(pesanMasuk);

  connect();

  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

void loop() {
  client.loop(); // Handle MQTT messages
  delay(10);     // Fixes some issues with WiFi stability

  // Cek koneksi WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected");

    // Publish pesan dengan nilai "false" ke topik "urse/email@gmail.com/statushadwareiot"
    client.publish("urse/email@gmail.com/statushadwareiot", "false");
    Serial.println("Published 'false' to urse/email@gmail.com/statushadwareiot");

    // Reconnect WiFi dan MQTT jika diperlukan
    connect();
  }

  if (!client.connected()) {
    Serial.println("Client disconnected");
    
    // Publish pesan dengan nilai "false" ke topik "urse/email@gmail.com/statushadwareiot"
    client.publish("urse/email@gmail.com/statushadwareiot", "false");
    Serial.println("Published 'false' to urse/email@gmail.com/statushadwareiot");
    
    connect();
  }

  // Publish sensor data every 2 seconds.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temperature = data.temperature; // Get temperature value
    float humidity = data.humidity;       // Get humidity value

    client.publish("urse/email@gmail.com/monitoring", String(temperature, 2)+'-'+String(humidity, 2));
    Serial.println("---");
  }
  // delay (1000);
}

