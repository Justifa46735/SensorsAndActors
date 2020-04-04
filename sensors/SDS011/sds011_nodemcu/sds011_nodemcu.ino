//#include <SdsDustSensor.h>

#include "SdsDustSensor.h" // https://github.com/lewapek/sds-dust-sensors-arduino-library

//#include <WiFi.h> //ESP32
#include <ESP8266WiFi.h> //ESP8266
#include <PubSubClient.h> //MQTT
#include "config.h"
#include "wifiJusti.h"
#include "mqttJusti.h"

//define sds011 value variables
double pm2dot5  = 0.0;  // Feuchtigkeit
double pm10   = 0.0;  // Temperatur

int rxPin = D1;
int txPin = D2;
SdsDustSensor sds(rxPin, txPin);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // connecting wifi and mqtt server
  connectWifi();
  Serial.println("Connecting to MQTT");
  connectMqtt(MQTT_CLIENTID_6);

  sds.begin();

  Serial.println(sds.queryFirmwareVersion().toString()); // prints firmware version
  Serial.println(sds.setActiveReportingMode().toString()); // ensures sensor is in 'active' reporting mode
  Serial.println(sds.setContinuousWorkingPeriod().toString()); // ensures sensor has continuous working period - default but not recommended
}

void loop() {
  PmResult pm = sds.readPm();
  if (pm.isOk())
  {

    // save values from sds011 reading:
    pm2dot5 = pm.pm25;
    pm10 = pm.pm10;

    Serial.print("PM2.5 = ");
    Serial.print(pm2dot5);
    Serial.print(", PM10 = ");
    Serial.println(pm10);

    // if you want to just print the measured values, you can use toString() method as well
    Serial.println(pm.toString());

    publishData(MQTT_SDS011_TOPIC_LEVEL_1, MQTT_PM2DOT5, pm2dot5);
    publishData(MQTT_SDS011_TOPIC_LEVEL_1, MQTT_PM10, pm10);

  }
  else
  {
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }

  delay(500);
}
