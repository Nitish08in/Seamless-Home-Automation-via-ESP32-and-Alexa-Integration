# Seamless-Home-Automation-via-ESP32-and-Alexa-Integration

## Project Overview

This project demonstrates a smart home automation system using the ESP32 microcontroller to control lights and a fan through **Alexa** and **Blynk**. The system also integrates sensors for monitoring temperature, humidity, and air quality (smoke level) using a **DHT11** sensor and an **MQ-135** smoke sensor. Key features include controlling two bulbs and a fan with Alexa, controlling a third bulb and monitoring sensor data via the Blynk app, and automatically activating the fan when smoke is detected.

## Features

- **Voice Control via Alexa**: Control two bulbs and the fan using voice commands through Alexa.
- **Mobile Control via Blynk**: Control the third bulb and the fan, and monitor sensor readings (temperature, humidity, smoke level) through the Blynk app.
- **Automatic Fan Activation**: The fan automatically turns on when the smoke sensor detects a certain threshold of smoke in the air.
- **Real-time Sensor Data**: Monitor temperature, humidity, and smoke levels on an OLED display and through the Blynk app.

## Components Used

- **ESP32** (Wi-Fi module for microcontroller)
- **4-channel relay module** (to control bulbs and fan)
- **DHT11 sensor** (to monitor temperature and humidity)
- **MQ-135 smoke sensor** (to detect smoke levels)
- **16x2 LCD display** (for local display of sensor readings)
- **220V fan** (controlled via relay)
- **30W bulbs** (controlled via relays)
- **Alexa integration** via SinricPro
- **Blynk IoT app** for mobile control and monitoring

## Circuit Diagram

*(Add a diagram of your circuit here)*

## Connections

Below are the connections of the ESP32 with the various components used in the project:

| **Component**         | **ESP32 Pin** | **Description**                          |
|-----------------------|---------------|------------------------------------------|
| Relay for Bulb 1       | GPIO 26       | Controlled by Alexa (SinricPro)           |
| Relay for Bulb 2       | GPIO 25       | Controlled by Alexa (SinricPro)           |
| Relay for Bulb 3       | GPIO 33       | Controlled by Blynk (manual via app)      |
| Relay for Fan          | GPIO 32       | Controlled by Alexa (SinricPro) and Blynk |
| DHT11 Data Pin         | GPIO 14       | Reads temperature and humidity            |
| MQ-135 Smoke Sensor    | GPIO 34       | Reads smoke levels (analog input)         |
| OLED Display (SDA)     | GPIO 21       | Serial Data for I2C (OLED display)        |
| OLED Display (SCL)     | GPIO 22       | Serial Clock for I2C (OLED display)       |
| GND                    | GND           | Common Ground                             |
| VCC                    | 3.3V/5V       | Power supply                              |

- **Relay Module**: Each relay controls one of the home appliances (bulbs or fan). The ESP32 sends high/low signals to the relay module to turn the appliances on or off.
  
- **DHT11 Sensor**: This sensor monitors the temperature and humidity. It sends digital signals to the ESP32, which are displayed on the OLED and sent to the Blynk app.
  
- **MQ-135 Smoke Sensor**: This sensor detects smoke and gas levels in the air. When the air quality worsens beyond a threshold, the fan is automatically turned on.
  
- **OLED Display**: Displays real-time temperature, humidity, and smoke levels for local monitoring.

## How to Control

1. **Alexa**: Use Alexa voice commands to turn on/off the bulbs and the fan. Alexa is connected via SinricPro.
2. **Blynk App**: Control the third bulb and the fan, and view sensor readings (temperature, humidity, smoke level) using the Blynk app.
3. **Automatic Fan Activation**: The fan will automatically turn on when the smoke sensor detects a certain threshold of smoke in the air.

## How to Run

### Step 1: Set Up the Hardware

- Connect the ESP32 to the relay module and sensors according to the circuit diagram.
- Ensure the relays are connected to the 220V bulbs and fan.

### Step 2: Configure the Code

- Open the Arduino IDE.
- Install the required libraries:
  - BlynkSimpleEsp32
  - DHT
  - Adafruit GFX
  - Adafruit SSD1306
  - SinricPro
- Insert your Wi-Fi, Blynk, and SinricPro credentials in the code.
- Upload the code to your ESP32 board.

### Step 3: Set Up Blynk

- Download the Blynk app on your phone.
- Create a new project and add the necessary widgets:
  - **Value Display** for temperature, humidity, and smoke level.
  - **Buttons** to control the third bulb and fan.

### Step 4: Set Up SinricPro for Alexa

- Create a free account on SinricPro.
- Add devices (bulbs and fan) to your SinricPro dashboard.
- Copy the device IDs and paste them into your Arduino code.
- Connect SinricPro to your Alexa account.

### Step 5: Power On and Test

- Power on the ESP32 and ensure it connects to Wi-Fi.
- Open the Blynk app to monitor and control devices.
- Use Alexa to control devices with voice commands (e.g., "Alexa, turn on Bulb 1").

## Project Images

1. **Completed Setup**
   Project Photos/Image 1.jpeg
   *(Insert a clear image of your fully assembled project here)*

3. **Blynk App Interface**  
   *(Include screenshots of the Blynk app interface showing control buttons and sensor readings)*

4. **OLED Display**  
   *(Show the OLED displaying temperature, humidity, and smoke levels)*

## Code Explanation

### Main Components

- **SinricPro Integration**: Alexa is connected to the relays for the first two bulbs and the fan using SinricPro. The ESP32 receives commands from Alexa to turn the relays on or off.
  
- **Blynk Virtual Pins**: Control the third bulb and fan through Blynk. Monitor temperature, humidity, and smoke levels through the app. The values are sent from the ESP32 to Blynk using virtual pins.

- **Sensors**: Data from the DHT11 and MQ-135 sensors are continuously read and displayed on the OLED screen. The data is also sent to the Blynk app for real-time monitoring.

### Automatic Fan Control

- The fan will automatically turn on when the smoke sensor detects a certain threshold of smoke. This is done by reading the analog value from the MQ-135 sensor and comparing it with a pre-defined threshold.

### OLED Display

- The OLED screen is used to display real-time temperature, humidity, and smoke levels. The screen is updated every 2 seconds to ensure the display remains current.

## Required Libraries

Before running the project, ensure you have installed the following libraries in your Arduino IDE:

1. **BlynkSimpleEsp32**: For ESP32-based projects connected to Blynk.
2. **DHT**: To read data from the DHT11 sensor.
3. **Adafruit GFX**: For OLED display graphics.
4. **Adafruit SSD1306**: To control the OLED display.
5. **SinricPro**: For Alexa integration via SinricPro.

## Future Improvements

- Add more sensors (e.g., motion detection, light sensors) to increase the system's functionality.
- Add remote over-the-air (OTA) updates to the ESP32 to allow for firmware updates without needing to physically connect the board.

## Conclusion

This project demonstrates a fully functional smart home automation system using ESP32, Blynk, and Alexa integration via SinricPro. It showcases the ease of controlling home appliances via voice commands, mobile apps, and automation based on sensor readings, making it a robust IoT-based solution for home automation.
