# Sensor Data Monitoring with Adafruit IO MQTT
This combined readme provides instructions on how to monitor sensor data using an Arduino board, perform fuzzy logic calculations, and publish the data to Adafruit IO MQTT for real-time tracking and visualization.

## Sensor Data Monitoring
This code is an example of sensor data monitoring using an Arduino board. It reads temperature, fire, and gas (smoke) sensor values and performs fuzzy logic calculations to determine the level of safety, warning, and danger based on the sensor readings. The code also includes a buzzer that is activated when the danger level exceeds a certain threshold.

## Requirements
To run this code, you will need the following components:

- Arduino board (tested on Arduino Uno)
- DHT11 temperature and humidity sensor
- Fire sensor (analog input)
- Gas sensor (analog input)
- Buzzer (digital output)
- Connections
- Make the following connections between the components and the Arduino board:

	- Connect the DHT11 sensor to digital pin 8 of the Arduino board.
	- Connect the fire sensor to analog pin A2 of the Arduino board.
	- Connect the gas sensor to analog pin A3 of the Arduino board.
	- Connect the buzzer to digital pin 9 of the Arduino board.
	
| arduino | Sensor |
|---------|--------|
| A2      | fire   |
| A3      | gas    |
| D8      | DHT 11 |
| D9	  | Buzzer |
| TX      | ESP D2 |
| RX      | ESP D3 |

## Usage
Follow these steps to use the code:

1. Install the required libraries:

	- dht.h (for DHT11 sensor)
	- ESP8266WiFi (for Wi-Fi connectivity)
	- SoftwareSerial (for communication with the ESP8266 module)
	- Adafruit_MQTT (for MQTT functionality)
	- Adafruit_MQTT_Client (for MQTT client implementation)
2. Upload the code to the Arduino board using the Arduino IDE or other compatible software.
3. Open the serial monitor to view the sensor readings, fuzzy logic calculations, and MQTT connection status. Make sure the baud rate is set to 115200.
4. The code will continuously read sensor data, perform calculations, and publish the data to Adafruit IO MQTT. The serial monitor will display the sensor readings, fuzzy logic calculations, and MQTT connection status.
5. Monitor the Adafruit IO dashboard to view the sensor data and track changes in real-time. The published data will be displayed in the corresponding feeds on your Adafruit IO account.

## Explanation
Here is a breakdown of the code's functionality:

1. The code begins by importing the necessary libraries and defining constants and variables for pin configurations, sensor readings, and MQTT settings.

2. The `setup()` function sets the input and output pins, initializes the serial communication for debugging purposes, and establishes a Wi-Fi connection with the ESP8266 module.

3. The `loop()` function is the main program loop that runs continuously. Within this loop, the code performs the following steps:

	a. Reads temperature and humidity from the DHT11 sensor using the DHT.read11() function.
	
	b. Checks if the DHT11 reading was successful using the DHTLIB_OK constant.
	
	c. If the reading was successful, it retrieves the temperature value from the DHT11 sensor.
	
	d. The code maintains an array of temperature readings to calculate the average temperature. It updates the array, calculates the average, and applies an offset to adjust the temperature reading.
	
	e. It reads the analog values from the fire and gas sensors and converts them to relevant units using the specified constants.
	
	f. Fuzzy logic calculations are performed for the temperature, fire, and gas levels to determine the degree of cold, warm, hot, none, small, large, noGas, lightGas, and heavyGas.
	
	g. The fuzzy logic rules are applied to determine the output levels of safety, warning, and danger.
	
	h. The output levels are adjusted to ensure their sum is equal to 1.
	
	i. The sensor readings, fuzzy logic calculations, and output levels are printed to the serial monitor for debugging and monitoring purposes.
	
	j. The buzzer is turned on if the danger level exceeds a certain threshold; otherwise, it is turned off.
	
	k. The code establishes an MQTT connection with Adafruit IO using the Wi-Fi module and the provided Adafruit IO username and key.
	
	l. Once the MQTT connection is established, the code publishes the sensor data to the corresponding MQTT topics on Adafruit IO. The topics are defined in the code and can be customized to match your Adafruit IO feeds.
	
	m. The code continuously checks for incoming MQTT messages, although no specific functionality related to message reception is implemented in this code. This section can be customized to handle incoming messages if required.
	
	n. A short delay is added before reading inputs again to avoid rapid fluctuations in readings.

The code repeats the steps in the `loop()` function indefinitely, continuously monitoring the sensor data, performing fuzzy logic calculations, and publishing the data to Adafruit IO MQTT.
Note: It is important to ensure that the necessary libraries are installed, the sensor connections are correctly made, and the Wi-Fi and Adafruit IO configurations are properly set before running the code. Also, adjust the pin configurations and calibration values according to your specific hardware setup and requirements.

## Customization
You can customize the code according to your specific needs. Here are a few possible modifications:

- Adjust the pin assignments: If you have connected the sensors or buzzer to different pins on the Arduino board, make sure to update the pin assignments in the code accordingly.

- Modify the calibration values: The code includes offset values and mapping ranges for sensor readings. You may need to adjust these values based on the characteristics of your sensors or specific application requirements.

- Change the fuzzy logic rules: The fuzzy logic calculations and rules used in the code are based on specific ranges and conditions. You can modify these rules to suit your application's safety criteria and threshold levels.

- Add additional sensors or functionalities: If you have additional sensors or actuators that need to be integrated into the system, you can add the necessary code to read their values and perform relevant actions based on the sensor readings.

- Implement additional MQTT functionality: The code currently publishes sensor data to Adafruit IO MQTT, but you can extend it to subscribe to MQTT topics and handle incoming messages if required.

- Customize the Adafruit IO dashboard: Adafruit IO provides a customizable dashboard where you can create widgets to visualize and interact with your sensor data. You can customize the dashboard to suit your preferences and display the data in a meaningful way.

- Implement data logging or remote monitoring: If you want to log the sensor data or send it to a remote server for monitoring and analysis, you can incorporate additional code to establish network connections (e.g., Wi-Fi or Ethernet) and send data over protocols like MQTT or HTTP.

## Troubleshooting
Here are a few common issues you may encounter and possible solutions:

- Incorrect sensor readings: Ensure that the sensors are connected properly, and the pin assignments are correct. Check the sensor specifications and data sheets for any specific requirements.

- Unexpected behavior: Verify that the calibration values are appropriate for your sensors and adjust them if necessary. Double-check the fuzzy logic rules and conditions to ensure they reflect your desired logic.

- Serial communication issues: Make sure the correct baud rate (115200) is set in the serial monitor. Check the connections between the Arduino board and the computer.

- Wi-Fi connection problems: Double-check the Wi-Fi credentials and ensure that the ESP8266 module is properly connected to the Wi-Fi network.

- MQTT connection issues: Verify that the Adafruit IO MQTT settings (server, port, username, key) are correct. Check the internet connection and firewall settings if you're having trouble connecting to Adafruit IO.

- MQTT topic configuration: Ensure that the MQTT topics defined in the code match the feeds you have set up on Adafruit IO. If the topics don't match, the data may not be published to the correct feeds.

- Parsing sensor data: If the sensor data format differs from the example in the code, you need to modify the parsing logic in the `loop()` function to correctly extract the sensor readings and calculate the output levels.

- Debugging using serial output: Monitor the serial output of the Arduino board to check for any error messages or connection issues. The serial output can provide valuable information for troubleshooting.

- Library compatibility: Make sure you have installed the correct versions of the required libraries and that they are compatible with each other. Incompatibilities between libraries can cause unexpected behavior.

- Check hardware connections: Verify that all hardware components are properly connected, and there are no loose wires or faulty connections. Inspect the physical connections between the Arduino board, sensors, and Wi-Fi module.

- Seek help from the community: If you have tried the troubleshooting steps and are still facing issues, consider reaching out to the respective communities or forums for assistance. Arduino and Adafruit IO have active communities where you can ask questions and get support.

- Remember to document any modifications you make to the code and keep track of the changes for future reference. Regularly test and validate the system to ensure its functionality and accuracy.

## Conclusion
By combining the functionalities of the two readme files, you now have a comprehensive guide for sensor data monitoring using an Arduino board and publishing the data to Adafruit IO MQTT. The code enables you to read sensor values, perform calculations, and determine safety levels based on fuzzy logic. Additionally, it establishes a connection with Adafruit IO MQTT to publish the sensor data for remote monitoring and analysis.

Feel free to modify and adapt the code to suit your specific needs and hardware setup. Happy coding!
