#include <Wire.h>
#include <Adafruit_BMP085.h>

//#include <WiFi.h> //ESP32
#include <ESP8266WiFi.h> //ESP8266
#include <PubSubClient.h> //MQTT
#include "config.h"
#include "wifiJusti.h"
#include "mqttJusti.h"

//define bmp value variables
double temperature = 0.0;  // Temperatur
double pressure    = 0.0;  // Luftdruck in hPa
double altitude    = 0.0;  // est_altitude Ungefaehre Hoehe

/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
// BMP180 is the replacement for BMP085
// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// I2C (NodeMCU SCK = D1/GPIO5, SDI = D2/GPIO4)
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

Adafruit_BMP085 bmp;
  
void setup() {
  Serial.begin(9600);
  // connecting wifi and mqtt server
  connectWifi();
  Serial.println("Connecting to MQTT");
  connectMqtt(MQTT_CLIENTID_5);

  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
}
  
void loop() {

  // get and save values from bmp reading:
  temperature   = bmp.readTemperature();
  pressure      = bmp.readPressure() / 100.0; // durch 100?
  altitude      = bmp.readAltitude(101500);

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" Pa");

  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

// you can get a more precise measurement of altitude
// if you know the current sea level pressure which will
// vary with weather and such. If it is 1015 millibars
// that is equal to 101500 Pascals.
  Serial.print("Real altitude = ");
  Serial.print(altitude);
  Serial.println(" meters");

  Serial.println();
  publishData(MQTT_BMP180_2_TOPIC_LEVEL_1, MQTT_TEMPERATURE, temperature);
  publishData(MQTT_BMP180_2_TOPIC_LEVEL_1, MQTT_PRESSURE, pressure);
  publishData(MQTT_BMP180_2_TOPIC_LEVEL_1, MQTT_ALTITUDE, altitude);
  Serial.println();

  delay(500);
}
