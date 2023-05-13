# explanation 

```
void setup()
{
  pinMode(firePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(115200);
}
```

- This block of code is part of the `setup()` function.
- It sets the firePin as an input pin using `pinMode()` to read the fire sensor values.
- It sets the buzzerPin as an output pin using `pinMode()` to control the buzzer.
- It starts the serial communication at a baud rate of 115200 using `Serial.begin()` for debugging purposes.

```
void loop()
{
  int chk = DHT.read11(8);
  float temp = DHT.temperature;

  tempTotal -= tempReadings[tempIndex];
  tempReadings[tempIndex] = temp;
  tempTotal += tempReadings[tempIndex];
  tempIndex = (tempIndex + 1) % numReadings;

  float avgTemp = tempTotal / static_cast<float>(numReadings);
  float calibratedTemp = avgTemp - offset;

  int fireSensorValue = analogRead(firePin);
  float voltage1 = (fireSensorValue / adcMax) * 5.0;
  float fireVal = voltage1 * 100.0;
  byte fire = map(static_cast<int>(fireVal), 0, 500, 0, 100);

  int gasSensorValue = analogRead(gasPin);
  float voltage2 = (gasSensorValue / adcMax) * 5.0;
  float ppm = voltage2 * 100.0;
```

- Inside the `loop()` function, the code reads the temperature and humidity from the DHT11 sensor using `DHT.read11(8)`.
- The temperature value is stored in the temp variable.
- The code updates the array of temperature readings by subtracting the oldest reading from the total, storing the new reading, and adding it to the total.
- The tempIndex variable is incremented and wrapped around within the range of the number of readings.
- The average temperature is calculated by dividing the total sum of readings by the number of readings.
- The calibrated temperature is obtained by subtracting the offset from the average temperature.
- The fire sensor value is read using `analogRead(firePin)` and converted to a voltage using the adcMax constant.
- The fire value is calculated by scaling the voltage and mapping it to a range of 0-100 using `map()`.
- The gas sensor value is read using `analogRead(gasPin)` and converted to a voltage using the adcMax constant.
- The ppm (parts per million) value is obtained by scaling the voltage.

```
float cold = max(0.0, 1.0 - (calibratedTemp - 0.0) / (40.0 - 0.0));
float warm = max(0.0, min((calibratedTemp - 0.0) / (35.0 - 0.0), (55.0 - calibratedTemp) / (55.0 - 35.0)));
float hot = max(0.0, min((calibratedTemp - 50.0) / (70.0 - 50.0), 1.0));

float none = max(0.0, 1.0 - (fire - 0.0) / (40.0 - 0.0));
float small = max(0.0, min((fire - 0.0) / (35.0 - 0.0), (55.0 - fire) / (55.0 - 35.0)));
float large = max(0.0, min((fire - 50.0) / (70.0 - 50.0), 1.0));

float noGas = max(0.0, 1.0 - (ppm - 0.0) / (100.0 - 0.0));
float lightGas = max(0.0, min((ppm - 0.0) / (50.0 - 0.0), (200.0 - ppm)) / (200.0 - 50.0));
float heavyGas = max(0.0, min((ppm - 100.0) / (150.0 - 100.0), 1.0));
```

- The code calculates membership values for different fuzzy sets based on the calibrated temperature, fire, and ppm values.
- For temperature, it calculates membership values for cold, warm, and hot fuzzy sets based on the temperature ranges.
- For fire, it calculates membership values for none, small, and large fuzzy sets based on the fire value ranges.
- For gas (ppm), it calculates membership values for noGas, lightGas, and heavyGas fuzzy sets based on the ppm value ranges.

```cpp
float safe = min(max(cold, none), max(lightGas, noGas));
float warning = min(max(warm, hot), max(small, lightGas));
float danger = min(max(cold, max(warm, hot)), max(large, max(lightGas, heavyGas)));
```

- The code calculates the degree of membership for the safe, warning, and danger levels based on the fuzzy logic rules.
- It combines the membership values of relevant fuzzy sets using the `min()` and `max()` functions.

```
float sum = safe + warning + danger;
if (sum > 0 || sum < 1)
{
  safe /= sum;
  warning /= sum;
  danger /= sum;
}
```

- The code checks if the specified interval (5 seconds) has elapsed since the last sensor reading using millis().
- If the interval has passed, it creates a JSON document using the ArduinoJson library.
- It populates the JSON document with the calibrated temperature, fire value, ppm value, and the normalized safe, warning, and danger values.
- The JSON document is serialized to a string using serializeJson().
- The string containing the JSON data is sent over the serial communication using Serial.println().

```
if (danger > 0.55)
{
  tone(buzzerPin, 1000);
}
else
{
  noTone(buzzerPin);
}
```

- The code checks if the danger level is above 0.55.
- If the danger level is higher, it activates the buzzer by playing a 1kHz tone using `tone(buzzerPin, 1000)`.
- If the danger level is below or equal to 0.55, it stops the buzzer tone using `noTone(buzzerPin)`.

```
delay(100);
```

- The code introduces a delay of 100 milliseconds before starting the next iteration of the loop() function.
- This delay helps in controlling the frequency of sensor readings and reduces the processing load on the microcontroller.