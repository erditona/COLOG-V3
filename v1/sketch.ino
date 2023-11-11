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

  Serial.println("\nconnected!");

  client.subscribe("urse/#");
}

void pesanMasuk(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  if (topic == "urse/kamar/lampu") {
    digitalWrite(5, payload.toInt());
    // Serial.println("LED 1 state: " + String(digitalRead(5)));
  } else if (topic == "urse/kamar/tv") {
    digitalWrite(18, payload.toInt());
    // Serial.println("LED 2 state: " + String(digitalRead(18)));
  } else if (topic == "urse/kamar/lampubaca") {
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
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temperature = data.temperature; // Ambil nilai suhu
    float humidity = data.humidity;       // Ambil nilai kelembaban

    client.publish("urse/suhu", String(temperature, 2) + "°C");
    client.publish("urse/humidity", String(humidity, 2) + "%");
    Serial.println("---");
  }

  delay(1000); // Tunggu pembacaan baru dari sensor (DHT22 memiliki laju sampel sekitar 0,5Hz)
}
