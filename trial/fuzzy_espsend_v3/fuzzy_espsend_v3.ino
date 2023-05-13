#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Adafruit_MQTT_Client.h>

// SoftSerial pins
#define SOFT_SERIAL_RX_PIN D2
#define SOFT_SERIAL_TX_PIN D3

//unsigned long previousMillis = 0;
//unsigned long interval = 5000;  // 5 seconds

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
    String data = softSerial.readStringUntil('\n'); // Read data from Arduino
    // Example data format: "Temp: 25.0, Fire: 123, Gas: 456, Output: Safe=0.1, Warning=0.2, Danger=0.7"

    // Parse the received data
    float temperatureValue = getValueFromData(data, "Temp:", ",");
    float fireValue = getValueFromData(data, "Fire:", ",");
    float gasValue = getValueFromData(data, "Gas:", ",");
    float safeValue = getValueFromData(data, "Safe=", ",");
    float warningValue = getValueFromData(data, "Warning=", ",");
    float dangerValue = getValueFromData(data, "Danger=", ",");

//    unsigned long currentMillis = millis();
//    if (currentMillis - previousMillis >= interval) {
//      previousMillis = currentMillis;

      // Publish data to Adafruit IO MQTT topics
      publishValue(temp, temperatureValue);
      publishValue(fire, fireValue);
      publishValue(gas, gasValue);
      publishValue(outputSafe, safeValue);
      publishValue(outputWarning, warningValue);
      publishValue(outputDanger, dangerValue);

      // Debugging output to serial monitor
      printSensorData("Temp", temperatureValue);
      printSensorData("Fire", fireValue);
      printSensorData("Gas", gasValue);
      printSensorData("Safe", safeValue);
      printSensorData("Warning", warningValue);
      printSensorData("Danger", dangerValue);
//    }

    // Handle MQTT communication
    mqtt.processPackets(100);
    mqtt.ping();
  }
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

void publishValue(Adafruit_MQTT_Publish& feed, float value) {
  if (!feed.publish(value)) {
    Serial.println("Failed to publish data to MQTT topic");
  }
}

float getValueFromData(const String& data, const String& startTag, const String& endTag) {
  int startIndex = data.indexOf(startTag);
  int endIndex = data.indexOf(endTag, startIndex);

  if (startIndex == -1 || endIndex == -1) {
    return 0.0;
  }

  String valueString = data.substring(startIndex + startTag.length(), endIndex);
  return valueString.toFloat();
}

void printSensorData(const char* sensorName, float value) {
  Serial.print(sensorName);
  Serial.print(": ");
  Serial.println(value);
}
