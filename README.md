# Gaz Sensor Application

## Introduction
The general objective of this project is to carry out the complete implementation of a gas sensor, from its manufacture, through its integration on a PCB, to its use in a concrete IoT application. This course gives us the opportunity to put our skills into practice at every stage in the design and development of a project. In particular, it covers the main phases such as hardware design, software design and product integration. Various digital tools were used, including KiCad for PCB design, LTSpice for analogue simulations and the Arduino platform for programming.

The application developed detects carbon monoxide and alerts you if critical thresholds are exceeded. Three LEDs indicate the alert levels: green for a safe level, orange for a high level and red for a dangerous level requiring evacuation. An OLED screen, connected via I2C, displays CO levels in real time to check the accuracy of the measurements. These measurements are then sent via a LoRa antenna and retrieved using the NodeRed software, which displays them.

This Git file and the following document contain the steps required to design our application, as well as the results obtained.

## LoRa Antenna
As mentioned above, the aim is to send the data measured by the sensor via a LoRa antenna. To do this, we used the open-source LoRaWAN Network Server ChirpStack, on which we created our application and generated its identifier and access key. Via this server, it is possible to connect to the GEI's main LoRa antenna and view the data stream sent to it.

On the programming side, we used the LoRa RN2483. This module has the advantage of communicating via the UART, so it was easy to connect it to the Arduino and have it send and receive data. We then had to reset and configure the RN2483 microchip according to the identifiers created on ChirpStack. Once this was done, we launched the connection tests and were able to check that our antenna was indeed connected to the main antenna via ChirpStack.

## Components Integration
### OLED Screen
As already mentioned, the OLED screen displays the carbon monoxide level measured by the sensor. The display is of the SSD1306 type and communicates via the I2C bus. We were therefore able to integrate it easily into our system, in particular by using adafruit libraries. By configuring the screen display, i.e. the size, colour and position of the text, we were able to display our first tests on the screen. We also used this screen as a test indicator to check the veracity and accuracy of the measurements taken by the sensor.
### Gaz Sensor
Adding the gas sensor to the application was not so easy. We had trouble understanding how the sensor worked and how to retrieve the measurements. However, after a bit of research we managed to get it to work properly.

This sensor detects the presence of carbon monoxide by a variation in resistance. First of all, the sensor has to be allowed to heat up in order to obtain values in line with reality, and then to adapt to its environment. The resistance value is recovered via a serial link and processed to obtain a usable level in ppm. We were then able to display on the screen the measurements taken in real time by the sensor.
### LEDs
To implement a visual alert, we decided to use three different coloured LEDs to symbolise our alert levels. The first level, green, means that the level of CO measured by the sensor is not toxic. The second, orange, symbolises that the quantity of gas is high and that exposure for too long can cause headaches. Finally, the red alert level lights up when the level of monoxide is above the safety threshold. Time to leave the room. We found the three thresholds in the literature on the websites of health bodies to reflect reality. The LEDs were switched on via a condition loop when the sensor measurements were retrieved.

## Node-RED Application
After that, we implemented Node-RED to visualise the data collected by the sensor. The idea was for the sensor readings transmitted via the LoRa antenna and processed by Chirpstack to be retrieved by Node-RED and displayed using its dashboard functionality. Using the MQTT protocol, we subscribed Node-RED to a Chirpstack topic in which it published the sensor measurements. This enabled us to retrieve the data transmitted on the LoRa network. The values were then displayed by creating a simple but powerful interface for viewing the gas sensor data in real time. 

For more information, read the Node-RED report here.

## The electrical circuit
Here is the complete electrical diagram of our system. It consists of the Arduino UNO shield, the three LEDs, the gas sensor, the OLED screen and an amplifier.

<img width="515" alt="Electrical Circuit" src="https://github.com/user-attachments/assets/7ff3e59e-216d-496f-a7f9-3450a9d5ef4d" />

The gas sensor produced has a very high resistance which varies according to the type and presence of gas. Its resistance is of the order of gigohms, which implies an extremely low current of the order of nanoampere (nA) flowing to the ADC. Using an Arduino with a 10-bit ADC requires the signal leaving the gas sensor to be amplified. We therefore designed an amplification circuit based on an operational amplifier and simulated it using LTSpice. To find out more, read the LT-Spice report here.

<img width="650" alt="Amplifier" src="https://github.com/user-attachments/assets/1031f84e-6b73-4b89-9ca7-6b3133a18195" />

## PCB Design
The PCB was designed using KiCad software. Starting with the previous electrical circuit, the components had to be placed on the Arduino UNO shield and then routed. This was a complex process because we had a lot of components that were quite imposing in terms of space, which did not make placement easy. The final aim was, instead of using a breadboard, to have all the components needed for our application on a single board. The OLED screen and the connectors for the LoRa module have been placed on the other side of the shield so that they can be accessed. Here is the final PCB for our project.

<img width="336" alt="PCB Design" src="https://github.com/user-attachments/assets/5e0bc044-3ee0-4059-a1eb-6147848fa1eb" />

Below, there is a 3D view of the PCB after conception.

-- Front view:

<img width="433" alt="3D view front" src="https://github.com/user-attachments/assets/1d848150-1e5a-4220-8564-61e3a3de5447" />

--Back view:

<img width="319" alt="3D view back" src="https://github.com/user-attachments/assets/5c2cdd87-7584-44ff-91ec-62e1998671b5" />

## Conclusion
The next stage of our project is to print the PCB and then solder the components. Finally, we will have to test our application by uploading our code onto the board. 

The overall objective of this module is to carry out the complete implementation of a gas sensor, from its manufacture, through its integration on a PCB, to its use in a concrete IoT application. This course thus gives us the opportunity to put our skills into practice at every stage of the design and development of a project. In particular, it covers the main phases such as hardware design, software design and product integration. 

In terms of energy consumption, we should look at the consumption of each component. If it is too high, we will have to switch to other components that consume less energy.
