# SensorsAndActors
The GitHub repository Justifa46735/SensorsAndActors focuses on interfacing with various Indoor air quality monitoring sensors and actuators. For certain sensors, the repository offers specific tags that provide initial examples without additional features like WIFI or MQTT. For instance, the SDS011_initial_example tag is available for the SDS011 sensor. But with including libraries so that you don’t have to search for a working one or the right version of it. So the intention is to get fast feedback if the sensor you bought works and get it running before diving in deeper with WIFI and MQTT to create for example a CO2 traffic light. And to visualize the readings on an RPI with Node-RED.
The repository includes an I2CScanner, nodeRed/flows, ownLibraries, pictures, sensors, sensor docs and submodules/libraries for the sensors.
## sensors
### BMP180
Checkout Tag "BMP180_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The BMP180 is a barometric pressure sensor from Bosch Sensortec

Key Features of the BMP180 Sensor:
* Measures Pressure: 300 – 1100 hPa (hectopascals).
* Altitude Calculation: Based on pressure readings.
* Temperature Sensor: Built-in with ±1°C accuracy.
* I²C and SPI Communication:
 
### BME680 / CJMCU-680
Checkout Tag "BME680_initial_example" or "CJMCU-680_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The BME680 (also known as CJMCU-680) is an advanced environmental sensor from Bosch Sensortec that combines multiple sensing capabilities into a single compact module. It measures temperature, humidity, barometric pressure, and air quality (gas/VOC levels)
      
Key Features of the BME680 / CJMCU-680 Sensor:
* Temperature Measurement: -40°C to 85°C (±1°C accuracy).
* Humidity Measurement: 0–100% RH (±3% accuracy).
* Barometric Pressure Measurement: 300–1100 hPa (±1 hPa accuracy).
* Gas Sensor: Detects Volatile Organic Compounds (VOCs) and air quality.
* I²C & SPI Communication
 
### DHT22
Checkout Tag "DHT22_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The DHT22 is a temperature and humidity sensor. It provides digital output via a single-wire communication protocol.

Key Features of the DHT22 Sensor:
* Temperature Measurement: -40°C to 80°C (±0.5°C accuracy).
* Humidity Measurement: 0–100% RH (±2–5% accuracy).
* Digital Output: Uses a single-wire communication protocol.
* Operating Voltage: 3.3V – 5V (works with Arduino & ESP).
* Sampling Rate: ~0.5 Hz 
 
### CJMCU-MICS-4514
tbd.

The CJMCU-MICS-4514 is a dual-channel gas sensor module that can detect multiple gases, making it useful for air quality monitoring and environmental sensing. It is based on the 	MICS-4514 sensor from SGX Sensortech.
	
Key Features of the CJMCU-MICS-4514 Sensor:
* Dual-channel sensing: 
	Reducing gases: CO (Carbon Monoxide), Hydrocarbons (CH₄, C₂H₆, etc.), Ethanol, Ammonia (NH₃), Hydrogen (H₂). 
* Oxidizing gases: Nitrogen Dioxide (NO₂). 
* Analog Output: Provides voltage corresponding to gas concentration. 
* Pre-calibrated: Requires minimal calibration. 
* Heater Element: Preheats the sensor for stable readings.
 
### CJMCU-MICS-6814
tbd.

The CJMCU-MICS-6814 is a multi-gas sensor module that can detect various gases, making it ideal for air quality monitoring and environmental sensing. It is based on the MICS-6814 sensor from SGX Sensortech.

Key Features of the CJMCU-MICS-6814 Sensor:
* Detects Reducing gases: Carbon monoxide (CO), Ammonia (NH₃), Hydrogen (H₂), Methane (CH₄), Propane (C₃H₈), Iso-butane (C₄H₁₀). 
* Detects Oxidizing gases: Nitrogen dioxide (NO₂). 
* Detects NH₃-sensitive: Special sensitivity to Ammonia.
* Analog Output: Provides separate voltage signals for different gas types.
      
### MQ135
Checkout Tag "MQ135_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### TGS2600
tbd.

The TGS2600 is a semiconductor gas sensor developed by Figaro for detecting air contaminants such as carbon monoxide (CO), hydrogen (H₂), and volatile organic compounds (VOCs).
  
Key Features of the TGS2600 Sensor:
* Detects a range of gases (Hydrogen, Carbon Monoxide, VOCs).
* Analog Output (resistance changes based on gas concentration).
* Pre-calibrated for indoor air quality applications.
 
### CCS811
tbd.
### K30 / K30-FR
Checkout Tag "K30_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The K30 or K30-FR (fast response) is a high-performance NDIR (Non-Dispersive Infrared) CO₂ sensor manufactured by SenseAir.
	
Key Features of the K30 CO₂ Sensor:
* CO₂ Measurement Range: 0–10,000 ppm (with models available for different ranges). 
* Accuracy: ±30 ppm + 3% of the reading. 
* NDIR Technology: Provides stable and reliable CO₂ detection. 
* Automatic Baseline Calibration (ABC): Ensures long-term stability by adjusting the baseline 	over time.
* I²C Interface
 
### MG811
tbd.

The MG811 is a carbon dioxide (CO₂) gas sensor that operates using a solid-state electrochemical principle.

Key Features of the MG811 Sensor:
* CO₂ Measurement Range: ~350 – 10,000 ppm.
* High Sensitivity & Stability: Uses an electrochemical reaction for CO₂ detection.
* Analog Voltage Output: Requires an amplifier circuit for accurate readings.
* Built-in Heater: Enhances sensor performance (requires 6V heating voltage).
 
### MH-Z14A
Checkout Tag "MHZ14A_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The MH-Z14A is an NDIR (Non-Dispersive Infrared) CO₂ sensor designed for accurate carbon dioxide (CO₂) measurement.

Key Features of the MH-Z14A Sensor:
* CO₂ Measurement Range: 0–5000 ppm.
* Accuracy: ±(50 ppm + 5% of the reading).
* NDIR Technology: Provides high stability.
* Automatic Baseline Calibration (ABC): Adjusts sensor drift over time.
* Multiple Communication Options:
UART (Serial TTL, 9600 baud) 
PWM (Pulse Width Modulation) 
Analog Output (0.4–2V proportional to CO₂ concentration)
 
### MH-Z19B
Checkout Tag "MHZ19B_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The MH-Z19B is a NDIR (Non-Dispersive Infrared) CO₂ sensor designed for accurate and stable carbon dioxide (CO₂) measurements.
	
Key Features of the MH-Z19B Sensor:
* CO₂ Measurement Range: 0–5000 ppm.
* Accuracy: ±(50 ppm + 5% of the reading).
* NDIR Technology: High stability and long lifespan (~5 years).
* Automatic Baseline Calibration (ABC): Adjusts sensor drift over time.
* Multiple Communication Options: UART (Serial TTL, 9600 baud) and PWM (Pulse Width Modulation)
 
### SCD41
Checkout Tag "SCD41_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The SCD41 is a high-accuracy CO₂, temperature, and humidity sensor from Sensirion. 

Key Features of the SCD41:
* CO₂ Measurement: Measures 400–5000 ppm (parts per million) with an accuracy of ±(40 ppm + 5% of the reading). 
* Temperature Sensor: Built-in, accurate to ±(1°C). 
* Humidity Sensor: Measures relative humidity with ±3% accuracy. 
* I²C Interface
  
### PMS7003
Checkout Tag "PMS7003_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The PMS7003 is a laser-based particulate matter (PM) sensor from Plantower
      
Key Features of the PMS7003 Sensor:
* Measures PM1.0, PM2.5, and PM10 (in µg/m³).
* Laser Scattering Technology for accurate particle detection.
* Serial Communication (UART at 9600 baud) for easy interfacing.
* Built-in Fan for continuous air sampling.
 
### SDS011
Checkout Tag "SDS011_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The SDS011 is a laser-based particulate matter (PM) sensor from Nova Fitness, designed to measure PM2.5 and PM10 concentrations in the air.
              
Key Features of the SDS011 Sensor:
* Measures PM2.5 & PM10 (in µg/m³).
* Laser Scattering Technology for high accuracy.
* UART (serial) communication.
* Operating Voltage: 5V.
* Built-in Fan for continuous air sampling.
    
### DSM501A
tbd.

The DSM501A is an optical dust sensor designed to measure airborne particulate matter (PM)
      
Key Features of the DSM501A Sensor:
* Detects PM2.5 and PM10 (particulate matter sizes).
* Optical Detection: Uses an infrared LED and photodetector.
* Digital PWM Output

## actors
###

## Getting started:
After cloning this repo run:
* git submodule update --init --recursive
* Change the creditals in the file config.h in the folder ownLibrary
* create symbolic links within the sensor folder that you want to flash on the esp8266 for the ownLibary files 
  (ln -sf ~/git/SensorsAndActors/ownLibrary/config.h ~//git/SensorsAndActors/sensors/XXX/config.h)
* add Esp8266 to the Ardunio preferences https://github.com/esp8266/Arduino
* install espsoftwareserial (Beim Esp8266 muss die SoftwareSerial library ausgetauscht werden damit UART funktioniert.)
