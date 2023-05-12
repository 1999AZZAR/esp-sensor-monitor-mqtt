// Define input pins
const int tempPin = A2;
const int firePin = A3;
const int gasPin  = A4;

// Define output pins
const int safePin = 9;
const int warningPin = 10;
const int dangerPin = 11;

int offset = 120;

// Temperature calibration constants
const float tempMin = -20.0;
const float tempMax = 70.0;
const float adcMin = 0.0;
const float adcMax = 1023.0;

// Variables for averaging temperature readings
const int numReadings = 10;  // Number of readings to average
int tempReadings[numReadings];  // Array to store temperature readings
int tempIndex = 0;  // Index of the current reading
int tempTotal = 0;  // Accumulator for summing the readings

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
  tempTotal -= tempReadings[tempIndex];  // Subtract the oldest reading from the total
  tempReadings[tempIndex] = TempSensorValue;
  tempTotal += tempReadings[tempIndex];  // Add the new reading to the total
  tempIndex = (tempIndex + 1) % numReadings;  // Move to the next reading index

  // Calculate the average temperature
  float temp = ((tempTotal / (float)numReadings) / adcMax) * 5.0;  // Convert average reading to voltage
  temp = ((temp - 0.5) * 100.0) - offset;  // Apply the offset to adjust the temperature reading
  temp = constrain(temp, tempMin, tempMax);  // Ensure temperature is within the desired range

  // Read fire sensor values
  int FireSensorValue = analogRead(firePin);
  float voltage1 = (FireSensorValue / adcMax) * 5.0; // Convert analog value to voltage
  float fireVal = voltage1 * 100.0;                  // Apply the offset to adjust the ppm reading
  byte fire = map(int(fireVal), 440, 40, 0, 100);    // Map the fire reading

  // Read gas sensor values
  int GasSensorValue = analogRead(gasPin);
  float voltage2 = (GasSensorValue / adcMax) * 5.0; // Convert analog value to voltage
  float ppm = voltage2 * 100.0;                     // Apply the offset to adjust the ppm reading

  // Fuzzy logic calculation for temperature
  float cold = max(0, 1 - (temp - 0) / (30 - 0));
  float warm = max(0, min((temp - 0) / (40 - 0), (50 - temp) / (50 - 40)));
  float hot = max(0, min((temp - 40) / (70 - 40), 1));

  // Fuzzy logic calculation for fire
  float none = max(0, 1 - (fire - 0) / (30 - 0));
  float small = max(0, min((fire - 0) / (40 - 0), (60 - fire) / (60 - 40)));
  float large = max(0, min((fire - 40) / (70 - 40), 1));

  // Fuzzy logic calculation for gas (smoke)
  float noGas = max(0, 1 - (ppm - 0) / (70 - 0));
  float lightGas = max(0, min((ppm - 0) / (80 - 0), (100 - ppm)) / (100 - 80));
  float heavyGas = max(0, min((ppm - 80) / (120 - 80), 1));

  // Fuzzy logic rules for output
  float safe = min(max(cold, warm), max(none, noGas));
  float warning = min(warm, max(max(none, small), lightGas));
  float danger = min(max(warm, hot), max(large, heavyGas));

  // Calculate the sum of safe, warning, and danger
  float sum = safe + warning + danger;

  // Adjust the values to ensure the sum is equal to 1
  if (sum > 0) {
    safe /= sum;
    warning /= sum;
    danger /= sum;
  }

  // Map fuzzy output values to the PWM range (0-255)
  int safePWM = map(safe, 0, 1, 0, 255);
  int warningPWM = map(warning, 0, 1, 0, 255);
  int dangerPWM = map(danger, 0, 1, 0, 255);

  // Output values to pins
  analogWrite(safePin, safePWM);
  analogWrite(warningPin, warningPWM);
  analogWrite(dangerPin, dangerPWM);

  // Debugging output to serial monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(", Fire: ");
  Serial.print(fire);
  Serial.print(", Gas: ");
  Serial.print(ppm);
  Serial.print(", Output: Safe=");
  Serial.print(safe);
  Serial.print(", Warning=");
  Serial.print(warning);
  Serial.print(", Danger=");
  Serial.println(danger);

  // Wait for a short time before reading inputs again
  delay(500);
}
