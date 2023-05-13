#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>

// SoftSerial pins
#define SOFT_SERIAL_RX_PIN D2
#define SOFT_SERIAL_TX_PIN D3

// Wi-Fi settings
const char* ssid = "pixel";
const char* password = "drowssap";

// Adafruit IO settings
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "YOUR_AIO_USERNAME"
#define AIO_KEY "YOUR_AIO_KEY"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);
SoftwareSerial softSerial(SOFT_SERIAL_RX_PIN, SOFT_SERIAL_TX_PIN);  // RX, TX

// MQTT topics
Adafruit_MQTT_Publish temp(&mqtt, AIO_USERNAME "/feeds/test.temperature");
Adafruit_MQTT_Publish fire(&mqtt, AIO_USERNAME "/feeds/test.fire");
Adafruit_MQTT_Publish gas(&mqtt, AIO_USERNAME "/feeds/test.gas");
Adafruit_MQTT_Publish outputSafe(&mqtt, AIO_USERNAME "/feeds/test.output-safe");
Adafruit_MQTT_Publish outputWarning(&mqtt, AIO_USERNAME "/feeds/test.output-warning");
Adafruit_MQTT_Publish outputDanger(&mqtt, AIO_USERNAME "/feeds/test.output-danger");

void setup() {
  Serial.begin(115200);
  softSerial.begin(115200);  // Set the baud rate of your Arduino

  // Connect to Wi-Fi
  connectToWiFi();

  // Connect to Adafruit IO MQTT
  connectToMQTT();
}

void loop() {
  if (softSerial.available()) {
    String jsonStr = softSerial.readStringUntil('\n'); // Read JSON data from Arduino
    deserializeAndPublish(jsonStr);
    Serial.println(jsonStr);
  }

  // Handle MQTT communication
  mqtt.processPackets(100);
  mqtt.ping();
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void connectToMQTT() {
  int8_t ret;

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
  }

  Serial.println("MQTT connected!");
}

void deserializeAndPublish(const String& jsonStr) {
  DynamicJsonDocument jsonDoc(256);
  DeserializationError error = deserializeJson(jsonDoc, jsonStr);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
    return;
  }

  float temperatureValue = jsonDoc["t"].as<float>();
  float fireValue = jsonDoc["f"].as<float>();
  float gasValue = jsonDoc["g"].as<float>();
  float safeValue = jsonDoc["s"].as<float>();
  float warningValue = jsonDoc["w"].as<float>();
  float dangerValue = jsonDoc["d"].as<float>();

  publishValue(temp, temperatureValue);
  publishValue(fire, fireValue);
  publishValue(gas, gasValue);
  publishValue(outputSafe, safeValue);
  publishValue(outputWarning, warningValue);
  publishValue(outputDanger, dangerValue);

  printSensorData("Temp", temperatureValue);
  printSensorData("Fire", fireValue);
  printSensorData("Gas", gasValue);
  printSensorData("Safe", safeValue);
  printSensorData("Warning", warningValue);
  printSensorData("Danger", dangerValue);
}

void publishValue(Adafruit_MQTT_Publish& feed, float value) {
  if (!feed.publish(value)) {
    Serial.println("Failed to publish data to MQTT topic");
  }
}

void printSensorData(const char* sensorName, float value) {
  Serial.print(sensorName);
  Serial.print(": ");
  Serial.println(value);
}
