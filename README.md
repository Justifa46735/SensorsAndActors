# SensorsAndActors
The GitHub repository Justifa46735/SensorsAndActors focuses on interfacing with various Indoor air quality monitoring sensors and actuators. For certain sensors, the repository offers specific tags that provide initial examples without additional features like WIFI or MQTT. For instance, the SDS011_initial_example tag is available for the SDS011 sensor. But with including libraries so that you don’t have to search for a working one or the right version of it. So the intention is to get fast feedback if the sensor you bought works and get it running before diving in deeper with WIFI and MQTT to create for example a CO2 traffic light. And to visualize the readings on an RPI with Node-RED.
The repository includes an I2CScanner, nodeRed/flows, ownLibraries, pictures, sensors, sensor docs and submodules/libraries for the sensors.
## sensors
### BMP180
Checkout Tag "BMP180_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### BME680 / CJMCU-680
Checkout Tag "BME680_initial_example" or "CJMCU-680_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### DHT22
Checkout Tag "DHT22_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### CJMCU-MICS-4514
tbd.
### CJMCU-MICS-6814
tbd.
### MQ135
Checkout Tag "MQ135_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### TGS2600
tbd.
### CCS811
tbd.
### K30 / K30-FR
Checkout Tag "K30_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### MG811
tbd.
### MH-Z14A
Checkout Tag "MHZ14A_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### MH-Z19B
Checkout Tag "MHZ19B_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### SCD41
Checkout Tag "SCD41_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### PMS7003
Checkout Tag "PMS7003_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works
### SDS011
Checkout Tag "SDS011_initial_example" for an initial example (without wifi, mqtt and etc.) to check if the Sensor works

The SDS011 is a laser-based particulate matter (PM) sensor from Nova Fitness, designed to measure PM2.5 and PM10 concentrations in the air.
              
  Key Features of the SDS011 Sensor:
	  Measures PM2.5 & PM10 (in µg/m³).
	  Laser Scattering Technology for high accuracy.
	  UART (serial) communication.
	  Operating Voltage: 5V.
	  Built-in Fan for continuous air sampling.
### DSM501A
tbd.

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
