#include <MQUnifiedsensor.h>
#include <EEPROM.h>

// Define input pins
const int tempPin = A2;
const int firePin = A0;
const int gasPin = A3; // Modified pin for gas (smoke) sensor

// Define output pins
const int safePin = 9;
const int warningPin = 10;
const int dangerPin = 11;

// Declare variables at global scope
const String Board = "Arduino UNO";
const String Type = "MQ-2"; // MQ2
#define Voltage_Resolution (5)
#define ADC_Bit_Resolution (10) // For Arduino UNO/MEGA/NANO
#define RatioMQ2CleanAir (9.83) // RS / R0 = 9.83 ppm

MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, gasPin, Type); // MQ2 sensor object

const int numReadings = 5;     // Number of readings to average
int tempReadings[numReadings]; // Array to store temperature readings
int tempIndex = 0;             // Index of the current temperature reading
float averageTemp = 0;         // Average temperature value

void setup()
{
  // Set input pins as inputs
  pinMode(tempPin, INPUT);
  pinMode(firePin, INPUT);

  // Set output pins as outputs
  pinMode(safePin, OUTPUT);
  pinMode(warningPin, OUTPUT);
  pinMode(dangerPin, OUTPUT);

  // Start serial communication for debugging purposes
  Serial.begin(115200);

  // MQ Init
  MQ2.setRegressionMethod(1);
  MQ2.setA(574.25);
  MQ2.setB(-2.222);
  MQ2.init();
  MQ2.setR0(RatioMQ2CleanAir);
  MQ2.serialDebug(true);
}

void loop()
{
  // Read temperature
  int sensorValue = analogRead(tempPin);
  float voltage = (sensorValue / 1024.0) * 5.0; // Convert analog value to voltage
  float temperature = voltage * 100.0; // Apply the offset to adjust the temperature reading
  tempReadings[tempIndex] = int(temperature);                // Store temperature reading in the array
  tempIndex = (tempIndex + 1) % numReadings;                 // Increment index
  averageTemp = calculateAverage(tempReadings, numReadings); // Calculate the average temperature

  // Read fire and gas (smoke) sensor values
  int fire = analogRead(firePin);
  MQ2.update();        // Update data, the Arduino will read the voltage from the analog pin
  MQ2.readSensor();    // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  // Fuzzy logic calculation for temperature
  float cold = max(0, 1 - (averageTemp - 0) / (20 - 0));
  float warm = max(0, min((averageTemp - 0) / (30 - 0), (50 - averageTemp) / (50 - 30)));
  float hot = max(0, min((averageTemp - 30) / (70 - 30), 1));

  // Fuzzy logic calculation for fire
  float none = max(0, 1 - (fire - 0) / (5 - 0));
  float small = max(0, min((fire - 0) / (10 - 0), (30 - fire) / (30 - 10)));
  float large = max(0, min((fire - 20) / (50 - 20), 1));

  // Fuzzy logic calculation for gas (smoke)
  float gasValue = MQ2.readSensor();
  float noGas = max(0, 1 - (gasValue - 0) / (10 - 0));
  float lightGas = max(0, min((gasValue - 0) / (20 - 0), (40 - gasValue)) / (40 - 20));
  float heavyGas = max(0, min((gasValue - 30) / (70 - 30), 1));

  // Fuzzy logic rules for output
  float safe = min(cold, max(none, noGas));
  float warning = min(max(cold, warm), max(max(none, small), lightGas));
  float danger = min(max(warm, hot), max(large, heavyGas));

  // Output values to pins
  analogWrite(safePin, safe * 255);
  analogWrite(warningPin, warning * 255);
  analogWrite(dangerPin, danger * 255);

  // Debugging output to serial monitor
  Serial.print("Temperature: ");
  Serial.print(averageTemp);
  Serial.print(", Fire: ");
  Serial.print(fire);
  Serial.print(", Gas: ");
  Serial.print(gasValue);
  Serial.print(", Output: Safe=");
  Serial.print(safe);
  Serial.print(", Warning=");
  Serial.print(warning);
  Serial.print(", Danger=");
  Serial.println(danger);

  // Wait for a short time before reading inputs again
  delay(100);
}

// Function to calculate the average value from an array
float calculateAverage(int *array, int length)
{
  float sum = 0;
  for (int i = 0; i < length; i++)
  {
    sum += array[i];
  }
  return sum / length;
}
