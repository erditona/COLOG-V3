#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <DHT.h> 

// Define the relay pins
#define relay1 D1
#define relay2 D2
#define relay3 D3

const char ssid[] = "Ditoo";
const char pass[] = "";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

#define DHT_PIN D5

DHT dht(DHT_PIN, DHT11); 

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
  } else if (topic == "urse/dito@gmail.com/kamar/tv") {
    digitalWrite(relay2, payload.toInt() == 1 ? LOW : HIGH);
  } else if (topic == "urse/dito@gmail.com/kamar/lampubaca") {
    digitalWrite(relay3, payload.toInt() == 1 ? HIGH : LOW);
  }
}

//void publishStatusService() {
//  const char* topicStatusService = "urse/statusaktifdevice";
//  
//  if (client.connected()) {
//    client.publish(topicStatusService, "service menyala");
//    Serial.println("Published 'service menyala' to " + String(topicStatusService));
//  }
//}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin("broker.emqx.io", net);
  client.onMessage(pesanMasuk);

  connect();

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  dht.begin(); // Initialize DHT sensor
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

  // Read DHT sensor data and publish it every 10 seconds.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
//    publishStatusService();

    float temperature = dht.readTemperature(); // Get temperature value
    float humidity = dht.readHumidity();       // Get humidity value

    client.publish("urse/dito@gmail.com/monitoring", String(temperature, 2) + '-' + String(humidity, 2));
    Serial.println("---");
  }
}
