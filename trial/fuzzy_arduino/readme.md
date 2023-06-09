# Sensor Data Monitoring

This code is an example of sensor data monitoring using an Arduino board. It reads temperature, fire, and gas (smoke) sensor values and performs fuzzy logic calculations to determine the level of safety, warning, and danger based on the sensor readings. The code also includes a buzzer that is activated when the danger level exceeds a certain threshold.

## Requirements

To run this code, you will need the following components:

- Arduino board (tested on Arduino Uno)
- DHT11 temperature and humidity sensor
- Fire sensor (analog input)
- Gas sensor (analog input)
- Buzzer (digital output)

## Connections

Make the following connections between the components and the Arduino board:

- Connect the DHT11 sensor to digital pin 3 of the Arduino board.
- Connect the fire sensor to analog pin A2 of the Arduino board.
- Connect the gas sensor to analog pin A3 of the Arduino board.
- Connect the buzzer to digital pin 9 of the Arduino board.

## Usage

Follow these steps to use the code:

1. Install the required libraries:
   - dht.h (for DHT11 sensor)
   
2. Upload the code to the Arduino board using the Arduino IDE or other compatible software.

3. Open the serial monitor to view the sensor readings and fuzzy logic calculations. Make sure the baud rate is set to 115200.

4. The code will continuously read sensor data and perform calculations. The serial monitor will display the temperature, fire level, gas level, and the output levels of safety, warning, and danger.

5. Observe the buzzer turning on when the danger level exceeds the threshold. This indicates a potentially hazardous situation.

## Explanation

Here is a breakdown of the code's functionality:

1. The code begins by importing the necessary libraries and defining constants and variables for pin configurations and sensor readings.

2. The `setup()` function sets the input and output pins as well as initializes the serial communication for debugging purposes.

3. The `loop()` function is the main program loop that runs continuously. Within this loop, the code performs the following steps:

   a. Reads temperature and humidity from the DHT11 sensor using the `DHT.read11()` function.
   
   b. Checks if the DHT11 reading was successful using the `DHTLIB_OK` constant.
   
   c. If the reading was successful, it retrieves the temperature value from the DHT11 sensor.
   
   d. The code maintains an array of temperature readings to calculate the average temperature. It updates the array, calculates the average, and applies an offset to adjust the temperature reading.
   
   e. It reads the analog values from the fire and gas sensors and converts them to relevant units using the specified constants.
   
   f. Fuzzy logic calculations are performed for the temperature, fire, and gas levels to determine the degree of cold, warm, hot, none, small, large, noGas, lightGas, and heavyGas.
   
   g. The fuzzy logic rules are applied to determine the output levels of safety, warning, and danger.
   
   h. The output levels are adjusted to ensure their sum is equal to 1.
   
   i. The sensor readings, fuzzy logic calculations, and output levels are printed to the serial monitor for debugging and monitoring purposes.
   
   j. The buzzer is turned on if the danger level exceeds a certain threshold; otherwise, it is turned off.
   
   k. A short delay is added before reading inputs again to avoid rapid fluctuations in readings.
   
5. The code repeats the steps in the `loop()` function indefinitely, continuously monitoring the sensor data and updating the outputs based on the fuzzy logic calculations.

Note: It is important to ensure that the necessary libraries are installed and the sensor connections are correctly made before running the code. Also, adjust the pin configurations and calibration values according to your specific hardware setup and requirements.

## Customization
You can customize the code according to your specific needs. Here are a few possible modifications:

- Adjust the pin assignments: If you have connected the sensors or buzzer to different pins on the Arduino board, make sure to update the pin assignments in the code accordingly.

- Modify the calibration values: The code includes offset values and mapping ranges for sensor readings. You may need to adjust these values based on the characteristics of your sensors or specific application requirements.

- Change the fuzzy logic rules: The fuzzy logic calculations and rules used in the code are based on specific ranges and conditions. You can modify these rules to suit your application's safety criteria and threshold levels.

- Add additional sensors or functionalities: If you have additional sensors or actuators that need to be integrated into the system, you can add the necessary code to read their values and perform relevant actions based on the sensor readings.

- Implement data logging or remote monitoring: If you want to log the sensor data or send it to a remote server for monitoring and analysis, you can incorporate additional code to establish network connections (e.g., Wi-Fi or Ethernet) and send data over protocols like MQTT or HTTP.

## Troubleshooting
Here are a few common issues you may encounter and possible solutions:

- Incorrect sensor readings: Ensure that the sensors are connected properly, and the pin assignments are correct. Check the sensor specifications and data sheets for any specific requirements.

- Unexpected behavior: Verify that the calibration values are appropriate for your sensors and adjust them if necessary. Double-check the fuzzy logic rules and conditions to ensure they reflect your desired logic.

- Serial communication issues: Make sure the correct baud rate (115200) is set in the serial monitor. Check the connections between the Arduino board and the computer.

- Buzzer not working: Confirm that the buzzer is connected to the correct pin, and the pin mode is set correctly. Check if the buzzer requires any additional components or circuitry.

## Conclusion
This code provides a framework for monitoring sensor data and performing fuzzy logic calculations to determine safety levels based on temperature, fire, and gas sensor readings. It demonstrates how Arduino boards can be used to process sensor data and make decisions based on predefined rules. By customizing the code to your specific requirements, you can create a robust sensor monitoring and safety system.

For more information and resources on Arduino programming, refer to the official Arduino documentation and online tutorials.

Feel free to modify and adapt the code to suit your needs, and happy coding!