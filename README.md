# ESP32 Improv WiFi Basic Example

This repository contains a simple example of using the [Improv WiFi Library](https://github.com/jnthas/Improv-WiFi-Library) to configure WiFi credentials for an ESP32 via USB/Serial communication.

## Features
- Configures WiFi credentials using Improv WiFi over USB/Serial.
- Blinks the onboard LED to indicate WiFi status.
- Serves a basic webpage with ESP32 chip and network information once connected.

## Requirements
- ESP32 development board.
- [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/) installed.
- Install the following libraries:
  - [Improv WiFi Library](https://github.com/jnthas/Improv-WiFi-Library)

## Usage
1. Open the project in your preferred IDE.
2. Connect your ESP32 to your computer via USB.
3. Upload the code to your ESP32.
4. Open a Serial Monitor (baud rate: `115200`) to interact with the device.
5. Use the Improv WiFi protocol to send WiFi credentials via USB/Serial. You can use tools like the [Improv WiFi Web Serial Tool](https://improv-wifi.github.io/serial/).

## How It Works
- The onboard LED blinks during setup and connection to indicate the status:
  - **Quick Blinks**: WiFi credentials are being processed.
  - **Three Short Blinks**: WiFi connected successfully.
  - **Three Long Blinks**: Error in configuration.
- Once connected, the ESP32 starts a basic web server on port `80`.
- Visit the device's IP address (e.g., `http://192.168.1.x`) to access the webpage.
- **Note:** If your webflasher says "port failed to initialize," simply power off the ESP32 and try again.


## Example Output
The served webpage displays:
- **ESP32 Chip Information**:
  - Model
  - Cores
  - Revision
- **Network Information**:
  - SSID
  - IP Address
  - MAC Address

## Acknowledgments
- [Improv WiFi Library](https://github.com/jnthas/Improv-WiFi-Library) for seamless WiFi configuration.
- Open-source community for the libraries and inspiration.
- Special thanks to ChatGPT for assistance in documentation and code optimization.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
