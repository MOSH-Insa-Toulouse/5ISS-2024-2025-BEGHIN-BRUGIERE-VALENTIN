# Gaz Sensor Application

## Introduction
The general objective of this project is to carry out the complete implementation of a gas sensor, from its manufacture, through its integration on a PCB, to its use in a concrete IoT application. This course gives us the opportunity to put our skills into practice at every stage in the design and development of a project. In particular, it covers the main phases such as hardware design, software design and product integration. Various digital tools were used, including KiCad for PCB design, LTSpice for analogue simulations and the Arduino platform for programming.\\

The application developed detects carbon monoxide and alerts you if critical thresholds are exceeded. Three LEDs indicate the alert levels: green for a safe level, orange for a high level and red for a dangerous level requiring evacuation. An OLED screen, connected via I2C, displays CO levels in real time to check the accuracy of the measurements. These measurements are then sent via a LoRa antenna and retrieved using the NodeRed software, which displays them.\\

This Git file and the following document contain the steps required to design our application, as well as the results obtained.

## LoRa Antenna
As mentioned above, the aim is to send the data measured by the sensor via a LoRa antenna. To do this, we used the open-source LoRaWAN Network Server ChirpStack, on which we created our application and generated its identifier and access key. Via this server, it is possible to connect to the GEI's main LoRa antenna and view the data stream sent to it. 
photoooo
On the programming side, we used the LoRa RN2483. This module has the advantage of communicating via the UART, so it was easy to connect it to the Arduino and have it send and receive data. We then had to reset and configure the RN2483 microchip according to the identifiers created on ChirpStack. Once this was done, we launched the connection tests and were able to check that our antenna was indeed connected to the main antenna via ChirpStack.

## Components Integration
