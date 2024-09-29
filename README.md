# ESP Projects Repository
This repository contains multiple ESP-based projects, each designed to showcase specific functionalities such as integration with ThingsBoard, UART communication for LED control, and RFID handling. These codes were developed as part of our IoT course projects.

## Projects

### 1. ThingsBoard Integration
This project demonstrates how to connect an ESP device to **ThingsBoard**, an open-source IoT platform. It enables monitoring and controlling various devices via the ThingsBoard dashboard.

- **Features**:
  - ESP communicates with the ThingsBoard server.
  - Data from sensors (e.g., temperature, humidity) can be sent to the ThingsBoard dashboard.
  - Remote control of connected devices through the dashboard.

- **Key Components**:
  - ESP device
  - ThingsBoard platform
  - Sensor modules

### 2. UART LED Control
This project uses **UART** (Universal Asynchronous Receiver/Transmitter) to control an LED. Commands are sent through UART to turn the LED on or off.

- **Features**:
  - Control an LED via UART communication.
  - Simple on/off command set.
  
- **Key Components**:
  - ESP device
  - LED
  - UART interface for communication

### 3. RFID Handling
This project demonstrates how to use an **RFID module** with an ESP to detect and read RFID tags. The data from the RFID tag can be processed and used for authentication or identification purposes.

- **Features**:
  - Read RFID tags using the ESP.
  - Display or process RFID tag data.
  
- **Key Components**:
  - ESP device
  - RFID module
  - RFID tags

## License
This repository is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
