#include <Wire.h>
#include <BMP180advanced.h>
#include "DHTesp.h"

//#include <WiFi.h> //ESP32
#include <ESP8266WiFi.h> //ESP8266
#include <PubSubClient.h> //MQTT
#include "config.h"
#include "wifiJusti.h"
#include "mqttJusti.h"

//define bmp value variables
double temperature = 0.0;  // Temperatur
double pressure    = 0.0;  // Luftdruck in hPa
double altitude    = 0.0;  // est. altitude Ungefaehre Hoehe

// BMP180 is the replacement for BMP085
// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// I2C (NodeMCU SCK = D1/GPIO5, SDI = D2/GPIO4)
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;
DHTesp dht_2;
BMP180advanced bmp(BMP180_ULTRAHIGHRES);

void setup()
{
  Serial.begin(9600);

  // connecting wifi and mqtt server
  connectWifi();
  Serial.println("Connecting to MQTT");
  connectMqtt(MQTT_CLIENTID_2);

  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  
  while (bmp.begin(D5, D6) != true) //sda, scl
  {
    Serial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
    delay(5000);
  }
  
  Serial.println(F("Bosch BMP180/BMP085 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory 

  // setup DHTs 
  dht.setup(D0, DHTesp::DHT22); // Connect DHT sensor to D0
  dht_2.setup(D3, DHTesp::DHT22); // Connect DHT sensor to D3
}

void loop()
{

  // get and save values from bmp reading:
  temperature   = bmp.getTemperature();
  pressure      = bmp.getPressure_hPa();
  altitude      = readAltitude(101500);

  Serial.println();
  publishData(MQTT_BMP180_TOPIC_LEVEL_1, MQTT_TEMPERATURE, temperature);
  publishData(MQTT_BMP180_TOPIC_LEVEL_1, MQTT_PRESSURE, pressure);
  publishData(MQTT_BMP180_TOPIC_LEVEL_1, MQTT_ALTITUDE, altitude);
  Serial.println();

  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float humidity_2 = dht_2.getHumidity();
  float temperature_2 = dht_2.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);

  publishData(MQTT_DHT22_TOPIC_LEVEL_1, MQTT_HUMIDITY, humidity);
  publishData(MQTT_DHT22_TOPIC_LEVEL_1, MQTT_TEMPERATURE, temperature);
  publishData(MQTT_DHT22_2_TOPIC_LEVEL_1, MQTT_HUMIDITY, humidity_2);
  publishData(MQTT_DHT22_2_TOPIC_LEVEL_1, MQTT_TEMPERATURE, temperature_2);

  delay(2000);
}

float readAltitude(float sealevelPressure) {
  float altitude;

  float pressure = bmp.getPressure();

  altitude = 44330 * (1.0 - pow(pressure /sealevelPressure,0.1903));

  return altitude;
}
