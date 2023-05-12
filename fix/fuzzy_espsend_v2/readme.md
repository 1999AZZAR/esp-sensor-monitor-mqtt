# Sensor Data to Adafruit IO MQTT Readme

This code allows you to read sensor data from an Arduino board and publish it to Adafruit IO MQTT. The code uses an ESP8266 Wi-Fi module and SoftwareSerial for communication with the Arduino board.

## Requirements

To use this code, you will need the following components:

- Arduino board (compatible with ESP8266)
- ESP8266 Wi-Fi module
- Sensors connected to the Arduino board (e.g., temperature, fire, gas)
- Adafruit IO account with MQTT access (username and key)

## Installation

To install and set up the code, follow these steps:

1. Install the necessary libraries:
   - `ESP8266WiFi`: This library enables the ESP8266 module to connect to Wi-Fi networks.
   - `SoftwareSerial`: This library provides software serial communication between the Arduino board and the ESP8266 module.
   - `Adafruit_MQTT`: This library provides MQTT functionality for interacting with Adafruit IO.
   - `Adafruit_MQTT_Client`: This library provides the MQTT client implementation.

2. Configure Wi-Fi and Adafruit IO settings:
   - Replace `"YOUR_WIFI_SSID"` with the SSID (name) of your Wi-Fi network.
   - Replace `"YOUR_WIFI_PASSWORD"` with the password of your Wi-Fi network.
   - Replace `"YOUR_AIO_USERNAME"` with your Adafruit IO username.
   - Replace `"YOUR_AIO_KEY"` with your Adafruit IO key.

3. Connect the Arduino board to the ESP8266 module using SoftwareSerial:
   - Define the RX and TX pins for the SoftwareSerial communication in the code (`SOFT_SERIAL_RX_PIN` and `SOFT_SERIAL_TX_PIN`).
   - Connect the RX pin of the ESP8266 module to the TX pin of the Arduino board, and vice versa.

4. Define the MQTT topics in the code:
   - Adjust the MQTT topics according to your Adafruit IO feeds. These topics will be used to publish sensor data.

5. Upload the code to the Arduino board.

## Usage

To use the code and publish sensor data to Adafruit IO MQTT, follow these steps:

1. Ensure that the Arduino board is powered and connected to the ESP8266 module.

2. Monitor the serial output of the Arduino board to verify the Wi-Fi and MQTT connections.
   - The serial output will provide information about the connection status and any errors that may occur.

3. Connect the sensors to the Arduino board and ensure they are providing data in the expected format.
   - The code expects the data format to be similar to: `"Temp: 25.0, Fire: 123, Gas: 456, Output: Safe=0.1, Warning=0.2, Danger=0.7"`.
   - Modify the parsing logic in the `loop()` function if your data format differs.

4. Once the Arduino board receives sensor data, it will publish the data to the corresponding MQTT topics on Adafruit IO.
   - The MQTT topics defined in the code (`temperature`, `fire`, `gas`, `outputSafe`, `outputWarning`, `outputDanger`) will be used to publish the respective sensor data.

5. Monitor the Adafruit IO dashboard to view the sensor data and track changes in real-time.
   - The published data will be displayed in the corresponding feeds on your Adafruit IO account.

## Troubleshooting

If you encounter any issues while using the code, consider the following troubleshooting steps:

- Check the Wi-Fi credentials and ensure that the ESP8266 module is properly connected to the Wi-Fi network.
- Verify that the Adafruit IO MQTT settings are correct (server, port, username, key).
- Double-check the MQTT topic configurations and ensure they match your Adafruit IO feeds.
- Verify the connections between the Arduino board, ESP8266 module, and sensors.
- Monitor the serial output of the Arduino board for any error messages or connection issues.
- Make sure the sensor data is being received and parsed correctly in the loop() function.
- Check the Adafruit IO dashboard to ensure that the data is being published to the correct feeds.
- If you still encounter issues, refer to the documentation of the libraries used or seek help from the respective communities or forums.

## Customization
You can customize the code according to your specific requirements:

- Modify the sensor data parsing logic in the `loop()` function if the data format differs from the example.
- Adjust the MQTT topics and feeds in the code to match your Adafruit IO setup.
- Extend the code to support additional sensors or functionalities by adding appropriate code sections.
- Implement error handling and notifications to handle exceptional situations or send alerts.

## License
This code is released under the MIT License. Feel free to modify and use it for your own projects.

## Acknowledgments
- This code utilizes the ESP8266WiFi, SoftwareSerial, and Adafruit_MQTT libraries, which are open-source and widely used in the Arduino community.
- The code is inspired by Adafruit IO and the MQTT protocol, providing an easy way to connect and publish sensor data to Adafruit IO.

## Author
This code was developed by azzar. You can contact me at azzar.mr.zs@gmail.com for any questions or feedback.
