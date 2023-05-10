// Fuzzy logic calculation for temperature, fire, and gas (smoke)

// Define input pins
const int tempPin = A2;
const int firePin = A1;
const int gasPin = A0;

// Define output pins
const int safePin = 9;
const int warningPin = 10;
const int dangerPin = 11;

void setup() {
  // Set input pins as inputs
  pinMode(tempPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(gasPin, INPUT);
  
  // Set output pins as outputs
  pinMode(safePin, OUTPUT);
  pinMode(warningPin, OUTPUT);
  pinMode(dangerPin, OUTPUT);
  
  // Start serial communication for debugging purposes
  Serial.begin(115200);
}

void loop() {
  // Read input values and map them to a range of 0-100
  int temp = map(analogRead(tempPin), 0, 1023, 0, 100);
  int fire = map(analogRead(firePin), 0, 1023, 0, 100);
  int gas = map(analogRead(gasPin), 0, 1023, 0, 100);
  
  // Fuzzy logic calculation for temperature
  float cold = max(0, 1 - (temp - 0)/(20 - 0));
  float warm = max(0, min((temp - 0)/(30 - 0), (50 - temp)/(50 - 30)));
  float hot = max(0, min((temp - 30)/(70 - 30), 1));
  
  // Fuzzy logic calculation for fire
  float none = max(0, 1 - (fire - 0)/(5 - 0));
  float small = max(0, min((fire - 0)/(10 - 0), (30 - fire)/(30 - 10)));
  float large = max(0, min((fire - 20)/(50 - 20), 1));
  
  // Fuzzy logic calculation for gas (smoke)
  float noGas = max(0, 1 - (gas - 0)/(10 - 0));
  float lightGas = max(0, min((gas - 0)/(20 - 0), (40 - gas)/(40 - 20)));
  float heavyGas = max(0, min((gas - 30)/(70 - 30), 1));
  
  // Fuzzy logic rules for output
  float safe = min(cold, max(none, noGas));
  float warning = min(max(cold, warm), max(max(none, small), lightGas));
  float danger = min(max(warm, hot), max(large, heavyGas));
  
  // Map output values to a range of 0-100 and output to pins
  analogWrite(safePin, map(safe * 1023, 0, 1023, 0, 100));
  analogWrite(warningPin, map(warning * 1023, 0, 1023, 0, 100));
  analogWrite(dangerPin, map(danger * 1023, 0, 1023, 0, 100));
  
  // Debugging output to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(", Fire: ");
  Serial.print(fire);
  Serial.print(", Gas: ");
  Serial.print(gas);
  Serial.print(", Output: Safe=");
  Serial.print(safe);
  Serial.print(", Warning=");
  Serial.print(warning);
  Serial.print(", Danger=");
  Serial.println(danger);
  
  // Wait for a short time before reading inputs again
  delay(100);
}
