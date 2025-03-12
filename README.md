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
### DSM501A
tbd.

## actors
###

After cloning this repo run:
* git submodule update --init --recursive
