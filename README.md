# Fire Detection System

This code implements a fire detection system using an Arduino board. The system monitors temperature, fire, and gas (smoke) levels to determine the safety level and provide corresponding outputs. The outputs are controlled using pulse-width modulation (PWM) on specific pins.

## Hardware Setup

- Connect the following input pins:
  - Temperature Sensor: A2
  - Fire Sensor: A3
  - Gas Sensor: A4

- Connect the following output pins:
  - Safe Output: 9
  - Warning Output: 10
  - Danger Output: 11

- Ensure the Arduino and necessary sensors are properly connected.

## Code Explanation

1. Define the input and output pins used by the system.

2. Set up the necessary variables and constants.

3. In the `setup()` function:
   - Set the input pins as inputs.
   - Set the output pins as outputs.
   - Initialize serial communication for debugging.

4. The `loop()` function performs the main logic of the system:
   - Read the temperature sensor value and calculate the average temperature using an array.
   - Convert the temperature reading to Celsius and constrain it within the desired range.
   - Read the fire and gas sensor values, and adjust the readings accordingly.
   - Apply fuzzy logic calculations to determine the output levels (safe, warning, and danger) based on the sensor readings.
   - Adjust the output values to ensure their sum is equal to 1.
   - Map the fuzzy output values to the PWM range (0-255) for the corresponding output pins.
   - Output the PWM values to the pins.
   - Print the sensor readings, fuzzy output values, and PWM outputs to the serial monitor for debugging.
   - Delay for a short time before reading inputs again.

**Note:** Ensure that the Arduino board is properly connected to the sensors and output devices. Adjust the pin assignments if necessary based on your hardware setup. You can modify the code to add additional functionality or customize the system behavior according to your requirements.
