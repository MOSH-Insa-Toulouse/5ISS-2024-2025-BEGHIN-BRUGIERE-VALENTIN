# Node-RED in the Gas Sensor Monitoring Project

## Introduction

As part of our project, we implemented Node-RED to visualize data collected by a gas sensor. The sensor readings, transmitted via LoRa and processed by Chirpstack, were retrieved in Node-RED and displayed using its dashboard capabilities. This document outlines how we configured Node-RED for real-time data visualization.

---

## Role of Node-RED in Our Project

In our project, we used Node-RED for the visualization of gas sensor data. Its role was focused on:

1. **Data Retrieval**: Using an MQTT node, Node-RED subscribed to a Chirpstack topic to receive the sensor data transmitted over the LoRa network.
2. **Data Visualization**: The `node-red-dashboard` package allowed us to create a user interface for real-time monitoring of the gas concentration, specifically CO levels.

---

## Configuration of Node-RED for Data Visualization

To integrate Node-RED into our workflow, we followed the steps below:

### 1. Connecting to Chirpstack via MQTT
We used the `mqtt in` node to subscribe to the topic where Chirpstack published the gas sensor data. The node was configured with the following:
- The broker URL and port of Chirpstack.
- The correct topic for sensor data.
- Authentication details where required.

**mettre photo de config mqtt**

### 2. Parsing the Data
The raw payload received from the MQTT node was in JSON format. We processed this data as follows:
- A `JSON` node was used to parse the payload into a structured format for easy handling.
- Function nodes were added to extract specific details such as gas concentration values and to reformat the data for better compatibility with dashboard widgets.

*Image suggestion*: Include a screenshot of the Node-RED flow showing the MQTT node and JSON parser in action.

### 3. Dashboard Configuration
For the visualization, we installed and configured the `node-red-dashboard` package:
- **Gauges** were used to display the current gas concentration levels.
- **Charts** plotted historical trends of gas readings over time.

*Image suggestion*: Add a screenshot of the Node-RED dashboard showing the gauge and chart widgets in real-time operation.

---

## Node-RED Flow Overview

Our Node-RED flow consisted of the following key components:

1. **Input Node**:
   - `mqtt in`: Subscribed to the Chirpstack topic for gas sensor data.
2. **Processing Node**:
   - `json`: Converted the raw payload into structured data.
3. **Visualization Nodes**:
   - `ui_gauge`: Displayed the current gas concentration level.
   - `ui_chart`: Graphed the real-time trends of gas readings.
   - `ui_text`: Added labels and contextual information.

*Image suggestion*: Provide a screenshot of the complete flow diagram from Node-RED to help visualize the workflow.

---

## Conclusion

Through Node-RED, we successfully created a simple yet powerful interface for visualizing gas sensor data in real time. The combination of MQTT integration and interactive dashboard widgets enabled us to effectively monitor CO levels transmitted via the LoRa network. This experience highlighted Node-RED’s suitability for rapid prototyping and student projects like ours, where simplicity and efficiency are key.

---

*Image suggestion*: Include a final screenshot of the dashboard showing live sensor data to showcase the outcome of the project.
