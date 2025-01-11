# DataSheet of the gaz sensor

*This document presents the datasheet of the gaz sensor based on tungsten trioxide nanoparticles, manufactured at AIME.*

<img width="400" alt="sensor" src="https://github.com/user-attachments/assets/6396d929-52db-4200-82b4-549df42e3d62" /> 

**Main Features**             
  - Small size
  - Low cost                 
  - Detection of Ethanol (C2H6O)                               
  - Short response time
  - Integrated Temperature sensor

## Sensor Description
This gas sensor is designed to identify the presence of C2H6O in the atmosphere. It functions as a passive component that detects gas presence through variations in its internal resistance. The incorporation of tungsten trioxide nanoparticles alters the conductivity of the aluminum interdigitated combs based on the gas composition in contact with the sensor. An internal heater allows the sensor to reach temperatures of up to 250°C, enhancing the sensitivity of the nanoparticles and minimizing interference from ambient humidity. Additionally, the sensor features an aluminum resistor to monitor its temperature, enabling improved control and the potential for temperature autoregulation.

## Pin Description
<img width="195" alt="bottom_view" src="https://github.com/user-attachments/assets/25034f16-8619-4b76-9e8a-21f4df13d979" /> <img width="364" alt="image" src="https://github.com/user-attachments/assets/032c8263-4a0c-4d0a-9ad4-21c66bd3f5f4" />

| Pin Number | Usage |
|--------|--------|
|    1/6  |  Temperature sensor (Aluminium resistor)   |
|    2/4  |    Gas sensor (WO3 nanoparticles integrated on aluminium interdigital combs)    |
|    3/8  |  Heater resistor (Polysilicon resistor)   |
|    7/9  |  Gas sensor (WO3 nanoparticles integrated on aluminium interdigital combs)    |
|    5/10  |  Not connected   |

## Specifications
|  | Specificities |
|--------|--------|
|   Type  | Nanoparticle based sensor |
|    Sensor  |   Passive (power supply required) |
|    Materials  | - Silicon<br>- N-doped poly-silicon (heater)<br>- Aluminum (temperature measurement)<br>- Nanoparticles of tungsten trioxide (WO3)    |
|    Detectable gaz  | Ethanol (C2H6O) |
|    Gas measurement   |  Resistance   |
|    Temperature measurement   |  Resistance   |
|  Package  | 10-Lead TO-5 metal  |
|  Diameter | 9.5 mm |

## Standard Test Conditions
|  | Unit | Typical Values |
|--------|--------|--------|
| Temperature | °C | 20±5 |
| Humidity | % | 60±5 |
| Air quality | % N2/O2 | 80/20 |

## Electrical characteristics

<table>
  <tr>
    <th rowspan="2"></th>
    <th rowspan="2">Unit</th>
    <th colspan="3">Value</th>
  </tr>
  <tr>
    <th>Min</th>
    <th>Typical</th>
    <th>Max</th>
  </tr>
  <tr>
    <td>Gas sensor resistance</td>
    <td>GΩ</td>
    <td>-</td>
    <td>20</td>
    <td>-</td>
  </tr>
  <tr>
    <td>Temperature sensor resistance</td>
    <td>Ω</td>
    <td>84</td>
    <td>107.53</td>
    <td>108</td>
  </tr>
  <tr>
    <td>Heater resistance</td>
    <td>Ω</td>
    <td>-</td>
    <td>83.3</td>
    <td>-</td>
  </tr>
  <tr>
    <td>Gas sensor voltage</td>
    <td>V</td>
    <td>-</td>
    <td>5</td>
    <td>-</td>
  </tr>
  <tr>
    <td>Temperature sensor voltage</td>
    <td>V</td>
    <td>0</td>
    <td>5</td>
    <td>10</td>
  </tr>
  <tr>
    <td>Heater voltage</td>
    <td>V</td>
    <td>0</td>
    <td>10</td>
    <td>15</td>
  </tr>
</table>

## Temperature sensor characteristics
![grapheALUAIME](https://github.com/user-attachments/assets/1e12dd83-a2c7-419d-a8c9-1ec87ae06c0f)
From this graph representing the evolution of the temperature resistor, we obtain that the resistance is approximately : 107.53 Ω.

## Heating resistor characteristics

## Gas sensor characteristics
The gas sensor characteristic is determined by measuring the resistance evolution in presence of ethanol. When the resistance drops, the ethanol amount in the environment increases. The gap is proportionnal to the gas concetration. 
<img width="700" alt="gaz" src="https://github.com/user-attachments/assets/c0504111-511d-40ca-a4e7-ad0245d2ecaf" />

## Sensor Integration
![image](https://github.com/user-attachments/assets/e8d419f5-8612-43e6-b6a7-abd436b9a610)
<img width="485" alt="gazsensor" src="https://github.com/user-attachments/assets/5f052fbb-2310-4b57-987b-3d18a5ba74ab" />

Above, there is a typical application of the sensor in an analogic circuit. The gaz sensor is 
connected in series with a resistors and with a RC filter. This filter aims to attenuate high frequencies. The outcoming tension is amplified 
by a LTC1050 operational amplifier before being filtered by a low pass filter. The 
tension from the ADC1 label can be connected to a 5V ADC such as an Arduino’s. 
The temperature sensor at pin TempB is also used as a resistor in a dividing bridge and the 
tension can be gathered by the ADC2 label. 

## Dimensions
The gas sensor uses a 10-Lead TO-5 metal package with the following dimensions:

<img width="482" alt="dim" src="https://github.com/user-attachments/assets/0e52214f-1dcc-48ae-9e91-11d9bf43596e" />
