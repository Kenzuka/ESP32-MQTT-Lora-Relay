# Why this project
This project aims to create a LoRa-based remote thermostat for a heating system located 300 meters away from the main living area. Due to the distance, direct Wi-Fi connectivity is impractical, so we use LoRa radio technology to facilitate remote communication. This setup leverages an existing Home Assistant and MQTT integration to control a relay, enabling the remote control of the heating system.

The project is Arduino-compatible and can be opened and edited in the Arduino IDE.
## General Schema

### Components Used

1. **2x ESP32 WROOM 32**  
   (Any version of ESP32 should be compatible.)
   
2. **2x Ra-02 LoRa Modules**  
   (One for the transmitter and one for the receiver.)

3. **1x 3V Relay with Optocoupler**  
   (Used to control the heating system’s on/off functionality.)

### Libraries Required

1. **LoRa** by Sandeep Mistry: [GitHub Link](https://github.com/sandeepmistry/arduino-LoRa)  
   Handles LoRa communication between the ESP32 boards.

2. **PubSubClient** by Nick O’Leary: [Documentation](https://pubsubclient.knolleary.net/)  
   Enables MQTT communication with Home Assistant.

3. **ESP32 WiFi Library**  
   Bundled with the Arduino IDE and used for network connectivity.

All libraries can be installed via the Arduino IDE Library Manager.


## Project Structure and Configuration

The project is organized into two ESP32 modules:

1. **`mqttESP`**: Acts as the MQTT client, receiving commands from Home Assistant via MQTT and transmitting them via LoRa to the relay controller.
2. **`releESP`**: Functions as the relay controller, receiving on/off signals from `mqttESP` over LoRa and controlling the relay to turn the heating system on or off.


### General System Diagram

The overall system architecture is shown in the following diagram:

![System Diagram](https://github.com/user-attachments/assets/4ba15109-57bc-4f7f-90d3-6e03bf4c38f8)



### Wiring and Pin Configuration

#### Relay Board Setup (`releESP`)

![Relay Board Wiring](https://github.com/user-attachments/assets/8f2df546-56ef-4fdc-b85d-5578c653a28d)

The relay board (`releESP`) controls the on/off state of the heating system.

| Device | Device Pin | ESP Pin |
|--------|------------|---------|
| Ra-02  | 3.3V       | 3.3V    |
| Ra-02  | GND        | GND     |
| Ra-02  | NSS        | D5      |
| Ra-02  | DIO0       | D2      |
| Ra-02  | SCK        | D18     |
| Ra-02  | MISO       | D19     |
| Ra-02  | MOSI       | D23     |
| Ra-02  | RST        | D14     |

#### MQTT Board Setup (`mqttESP`)

![MQTT Board Wiring](https://github.com/user-attachments/assets/5ccb5b86-fdc9-4d5d-86a9-5a70ffdb9e7b)

The MQTT board (`mqttESP`) acts as the bridge between Home Assistant and the LoRa-controlled relay.

| Device  | Device Pin | ESP Pin |
|---------|------------|---------|
| Ra-02   | 3.3V       | 3.3V    |
| Ra-02   | GND        | GND     |
| Ra-02   | NSS        | G4      |
| Ra-02   | DIO0       | G2      |
| Ra-02   | SCK        | G18     |
| Ra-02   | MISO       | G19     |
| Ra-02   | MOSI       | G23     |
| Ra-02   | RST        | G5      |
| Relay3V | 3.3V       | 3.3V    |
| Relay3V | GND        | GND     |
| Relay3V | IN         | G21     |

## Setup Instructions

**IMPORTANT**:  
LoRa communicates via radio frequencies (433-870 MHz). For this project, I used 433 MHz (notated as `433E6`, where "E6" expresses the frequency in MHz) because it's the legal frequency in my country. You can check the legal LoRa frequencies by country [here](https://www.thethingsnetwork.org/docs/lorawan/frequencies-by-country/).

To use this project in your country, replace the `433E6` value in `lora.ino` (on both boards) with your country’s allowed frequency. Make sure the frequency used for communication matches on both boards.

1. **Clone or download** this repository and open it in the Arduino IDE.
2. **Configure header files** in the `mqttESP` and `releESP` directories to suit your setup.
   - For `mqttESP`: Set up MQTT server details and topic names for communication with Home Assistant.
   - For `releESP`: Specify LoRa parameters to match the `mqttESP` board.
3. **Install required libraries** via the Arduino Library Manager if not already installed.
4. **Upload the code** to each ESP32 board:
   - `mqttESP` for the MQTT client.
   - `releESP` for the relay controller.

## Future Enhancements

- Add support for bidirectional communication to monitor relay status.
- Explore adding additional sensors (e.g., temperature) to enhance functionality.
- Optimize LoRa transmission settings for better range or reliability as needed.



# How To Use
Configure the header file of mqttESP and releESP folder
