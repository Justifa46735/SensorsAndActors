/***************************************************************************
  This is a library for the BME680 gas, humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME680 Breakout
  ----> http://www.adafruit.com/products/3660
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h> https://github.com/adafruit/Adafruit_Sensor
#include "Adafruit_BME680.h" https://github.com/adafruit/Adafruit_BME680

#include <ArduinoJson.h>
//#include <WiFi.h> //ESP32
#include <ESP8266WiFi.h> //ESP8266
#include <PubSubClient.h> //MQTT
#include "config.h"
#include "wifiJusti.h"
#include "mqttJusti.h"

//define bme value variables
double humidity    = 0.0;  // Feuchtigkeit
double temperature = 0.0;  // Temperatur
double pressure    = 0.0;  // Luftdruck in hPa
double gas         = 0.0;  // Air Quality Gas/Luftqualitaet
double altitude    = 0.0;  // est_altitude Ungefaehre Hoehe

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C (NodeMCU SCK = D1/GPIO5, SDI = D2/GPIO4)
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  Serial.begin(9600); // start seriellen monitor
  while (!Serial);

  // connecting wifi and mqtt server
  connectWifi();
  Serial.println("Connecting to MQTT");
  connectMqtt();

  Serial.println("Subscribe to Topics");
  subscribeTopics();

  Serial.println(F("BME680 test"));

  if (!bme.begin(0x77)) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

char *createMQTTmessage(int co2Value , const char* DataType)
{
  //Json object for MQTT
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  JSONencoder["RoomID"] = "1";
  JSONencoder["RoomName"] = MQTT_SUBSCRIBE_TOPIC_LEVEL_1;
  JSONencoder["SensorID"] = "1";
  JSONencoder["SensorName"] = "BME680";
  JSONencoder["Value"] = String(co2Value);
  JSONencoder["Unit"] = DataType;

  char JSONmessageBuffer[512];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
  
  return JSONmessageBuffer;
}

void loop() {
  // read from BME680
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  // get and save values from bme reading:
  temperature   = bme.temperature;
  pressure      = bme.pressure / 100.0;
  humidity      = bme.humidity;
  gas           = bme.gas_resistance / 1000.0;
  altitude  = bme.readAltitude(SEALEVELPRESSURE_HPA);
 
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");
  publishData(MQTT_TEMPERATURE, createMQTTmessage(temperature, MQTT_TEMPERATURE));
  delay(500);

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");
  publishData(MQTT_PRESSURE, createMQTTmessage(pressure, MQTT_PRESSURE));
  delay(500);

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  publishData(MQTT_HUMIDITY, createMQTTmessage(humidity, MQTT_HUMIDITY));
  delay(500);

  Serial.print("Gas = ");
  Serial.print(gas);
  Serial.println(" KOhms");
  publishData(MQTT_GAS, createMQTTmessage(gas, MQTT_GAS));
  delay(500);

  Serial.print("Approx. Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");
  publishData(MQTT_ALTITUDE, createMQTTmessage(altitude, MQTT_ALTITUDE));
  delay(500);

  Serial.println();
  delay(2000);
}
