# **IoT-Socket-Demo-Firmware**

This is a demo IoT project based on socket-io and express under DSC KGEC.<br>
This contains the firmware for the demonstration
For the Server side, visit [Socket-IoT-Demo](https://github.com/DSCKGEC/IoT-Socket-Demo)
<br>

## **Contents**
1. [Description](#description)
0. [Installation](#installation)
0. [Languages](#languages)
0. [Contribution](#contribution)

## **Description**

This is a demonstration on using Socket.IO Client on microcontroller for building IoT systems. Here Node MCU is used as the microcontroller. Some of the utilities used here, are described below:
- **Node MCU** provides us with WiFi connectivity for ease of its implementation in home IoT systems. It has an 32bit 80MHz processor from espressif which is pretty fast for embedded project. What attracts many hobbyist to use it in their projects, is Arduino support and presence of a lot of libraries. It is very cheap (cheaper than an Arduino Uno board) and compact in size.
- **Socket.IO** is a bi-directional and low-latency communication for every platform. It primarily uses websockets for communication, but it can also switch to other methods as well for realtime communication between server and clients.

## **Installation**
### Softwares required :

- [**Visual Studio Code**](https://code.visualstudio.com/)

- [**Platform IO**](https://platformio.org/)

- [**Arduino Framework**](https://www.arduino.cc/)

### Libraries :
- [**ArduinoJson.h**](https://github.com/bblanchon/ArduinoJson.git)
- [**WiFiManager.h**](https://github.com/tzapu/WiFiManager.git)
- [**WebSockets.h** for ESP8266](https://github.com/Links2004/arduinoWebSockets.git)
<br>

***Just install Platform IO from VS Code extensions, open the repository on VS code and start working on the main.cpp inside ```src/main.cpp```***


## **Languages**

- <img align="left" alt="C plus plus" width="60px" src="https://user-images.githubusercontent.com/72512900/146313275-30ec5b18-531f-4444-a777-025ff4deacbb.png" />
<br>

<br>

## **Contribution**
This is a concept for beginners starting with IoT. Feel free to fork, clone, create issues and/or make PRs. We will be more than happy to receive your contributions.

