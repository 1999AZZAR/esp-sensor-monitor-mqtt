// Define input pins
const int tempPin = A2;
const int firePin = A3;
const int gasPin  = A4;

// Define output pins
const int safePin = 9;
const int warningPin = 10;
const int dangerPin = 11;

int fireValue = 0;
int gasValue = 0;              // Array to store gas readings
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
  Serial.println("Fire Detection System Started");
}

void loop()
{
  // Read temperature
  int TempSensorValue = analogRead(tempPin);
  float voltage0 = (TempSensorValue / 1023.0) * 5.0;   // Convert analog value to voltage
  float temperature = (voltage0 - 0.5) * 100.0;        // Apply the offset to adjust the temperature reading
  tempReadings[tempIndex] = int(temperature);          // Store temperature reading in the array
  tempIndex = (tempIndex + 1) % numReadings;           // Increment index
  averageTemp = calculateAverage(tempReadings, numReadings); // Calculate the average temperature

  // Read fire sensor values
  int FireSensorValue = analogRead(firePin);
  float voltage1 = (FireSensorValue / 1023.0) * 5.0; // Convert analog value to voltage
  float fireVal = voltage1 * 100.0;                  // Apply the offset to adjust the ppm reading
  fireValue = int(fireVal);                          // Store fire reading in the array
  byte fire = map(fireValue, 440, 40, 0, 100);       // Map the fire reading

  // Read gas sensor values
  int GasSensorValue = analogRead(gasPin);
  float voltage2 = (GasSensorValue / 1023.0) * 5.0; // Convert analog value to voltage
  float ppm = voltage2 * 100.0;                     // Apply the offset to adjust the ppm reading
  gasValue = int(ppm);                              // Store ppm reading in the array

  // Fuzzy logic calculation for temperature
  float cold = max(0, 1 - (averageTemp - 0) / (20 - 0));
  float warm = max(0, min((averageTemp - 0) / (30 - 0), (50 - averageTemp) / (50 - 30)));
  float hot = max(0, min((averageTemp - 30) / (70 - 30), 1));

  // Fuzzy logic calculation for fire
  float none = max(0, 1 - (fire - 0) / (20 - 0));
  float small = max(0, min((fire - 0) / (30 - 0), (50 - fire) / (50 - 30)));
  float large = max(0, min((fire - 30) / (70 - 30), 1));

  // Fuzzy logic calculation for gas (smoke)
  float noGas = max(0, 1 - (gasValue - 0) / (20 - 0));
  float lightGas = max(0, min((gasValue - 0) / (30 - 0), (50 - gasValue)) / (50 - 30));
  float heavyGas = max(0, min((gasValue - 30) / (70 - 30), 1));

  // Fuzzy logic rules for output
  float safe = min(cold, max(none, noGas));
  float warning = min(max(cold, warm), max(max(none, small), lightGas));
  float danger = min(max(warm, hot), max(large, heavyGas));

  // Map fuzzy output values to the PWM range (0-255)
  int safePWM = map(safe, 0, 1, 0, 255);
  int warningPWM = map(warning, 0, 1, 0, 255);
  int dangerPWM = map(danger, 0, 1, 0, 255);

  // Output values to pins
  analogWrite(safePin, safePWM);
  analogWrite(warningPin, warningPWM);
  analogWrite(dangerPin, dangerPWM);

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
