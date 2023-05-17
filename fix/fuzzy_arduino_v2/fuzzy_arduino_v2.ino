#include <dht.h>
#include <ArduinoJson.h>

unsigned long previousMillis = 0;
unsigned long interval = 5000;  // 5 seconds

// Define input pins
const int firePin = A2;
const int gasPin = A3;
const int buzzerPin = 9;

int offset = 2;

const float adcMin = 0.0;
const float adcMax = 1023.0;

// Variables for averaging temperature readings
const int numReadings = 5; // Number of readings to average
int tempReadings[numReadings]; // Array to store temperature readings
int tempIndex = 0; // Index of the current reading
int tempTotal = 0; // Accumulator for summing the readings

// Create an instance of the dht class
dht DHT;

void setup()
{
  // Set input pins as inputs
  pinMode(firePin, INPUT);

  // Set the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);

  // Start serial communication for debugging purposes
  Serial.begin(115200);
}

void loop()
{
  // Read temperature and humidity from DHT11 sensor
  int chk = DHT.read11(8);

  // Retrieve temperature value from DHT11
  float temp = DHT.temperature;

  // Update the temperature readings
  tempTotal -= tempReadings[tempIndex]; // Subtract the oldest reading from the total
  tempReadings[tempIndex] = temp; // Store the new reading
  tempTotal += tempReadings[tempIndex]; // Add the new reading to the total
  tempIndex = (tempIndex + 1) % numReadings; // Move to the next reading index

  // Calculate the average temperature
  float avgTemp = tempTotal / static_cast<float>(numReadings);

  // Apply the offset to adjust the temperature reading
  float calibratedTemp = avgTemp - offset;

  // Read fire sensor values
  int fireSensorValue = analogRead(firePin);
  float voltage1 = (fireSensorValue / adcMax) * 5.0; // Convert analog value to voltage
  float fireVal = voltage1 * 100.0; // Apply the offset to adjust the fire reading
  byte fire = map(static_cast<int>(fireVal), 0, 500, 0, 100); // Map the fire reading

  // Read gas sensor values
  int gasSensorValue = analogRead(gasPin);
  float voltage2 = (gasSensorValue / adcMax) * 5.0; // Convert analog value to voltage
  float ppm = voltage2 * 100.0; // Apply the offset to adjust the ppm reading

  // Fuzzy logic calculation for temperature
  float cold = max(0.0, 1.0 - (calibratedTemp - 0.0) / (40.0 - 0.0));
  float warm = max(0.0, min((calibratedTemp - 0.0) / (35.0 - 0.0), (55.0 - calibratedTemp) / (55.0 - 35.0)));
  float hot = max(0.0, min((calibratedTemp - 50.0) / (70.0 - 50.0), 1.0));

  // Fuzzy logic calculation for fire
  float none  = max(0.0, 1.0 - (fire - 0.0) / (40.0 - 0.0));
  float small = max(0.0, min((fire - 0.0) / (35.0 - 0.0), (55.0 - fire) / (55.0 - 35.0)));
  float large = max(0.0, min((fire - 50.0) / (70.0 - 50.0), 1.0));

  // Fuzzy logic calculation for gas (smoke)
  float noGas = max(0.0, 1.0 - (ppm - 0.0) / (100.0 - 0.0));
  float lightGas = max(0.0, min((ppm - 0.0) / (50.0 - 0.0), (200.0 - ppm)) / (200.0 - 50.0));
  float heavyGas = max(0.0, min((ppm - 100.0) / (150.0 - 100.0), 1.0));

  // Fuzzy logic rules for output
  float safe = min(max(cold, none), max(lightGas, noGas));
  float warning = min(max(warm, hot), max(small, lightGas));
  float danger = min(max(cold, max(warm, hot)), max(large, max(lightGas, heavyGas)));

  // Calculate the sum of safe, warning, and danger
  float sum = safe + warning + danger;

  // Adjust the values to ensure the sum is equal to 1
  if (sum > 0 || sum < 1)
  {
    safe /= sum;
    warning /= sum;
    danger /= sum;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Create a JSON document
    DynamicJsonDocument jsonDoc(256);

    // Populate the JSON document
    jsonDoc["t"] = String(calibratedTemp, 2);
    jsonDoc["f"] = String(fire, 2);
    jsonDoc["g"] = String(ppm, 2);
    jsonDoc["s"] = String(safe, 2);
    jsonDoc["w"] = String(warning, 2);
    jsonDoc["d"] = String(danger, 2);

    // Serialize the JSON document to a string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Send the JSON data over serial
    Serial.println(jsonString);
  }

  // Play tones based on danger level
  if (danger > 0.55)
  {
    tone(buzzerPin, 1000);  // Play a 1kHz tone
  }
  else
  {
    noTone(buzzerPin);  // Stop playing the tone
  }

  // Wait for a short time before reading inputs again
  delay(100);
}
