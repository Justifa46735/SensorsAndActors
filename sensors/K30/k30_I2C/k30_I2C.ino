// Sample code for K-30 CO2 sensor

// Talks via I2C to K30/K33 Sensors

#include <Wire.h>

#include <ArduinoJson.h>
//#include <WiFi.h> //ESP32
#include <ESP8266WiFi.h> //ESP8266
#include <PubSubClient.h> //MQTT
#include "config.h"
#include "wifiJusti.h"
#include "mqttJusti.h"
#include "led.h"

// We will be using the I2C hardware interface on the Arduino in
// combination with the built-in Wire library to interface.
// Arduino analog input 5 - I2C SCL NodeMCU D1
// Arduino analog input 4 - I2C SDA NodeMCU D2

// This is the time resolution of sensor readings in ms.
int readingTime = 4000;

/*
  In this example we will do a basic read of the CO2 value and checksum
verification. For more advanced applications see the I2C Comm guide.
*/
int co2Addr = 0x68;
// This is the default address of the CO2 sensor, 7bits shifted left.

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // connecting wifi and mqtt server
  connectWifi();
  Serial.println("Connecting to MQTT");
  connectMqtt();

  Serial.println("Subscribe to Topics");
  subscribeTopics();

  Serial.println("register LEDs");
  setupLED(D6);
  setupLED(D7);
  setupLED(D8);

  //initialize wire
  Wire.begin ();
  Serial.println("Application Note AN-102: Interface Arduino to K-30");
}

///////////////////////////////////////////////////////////////////
// Function : int readCO2()
// Returns : CO2 Value upon success, 0 upon checksum failure
// Assumes : - Wire library has been imported successfully.
// - CO2 sensor address is defined in co2_addr
///////////////////////////////////////////////////////////////////
int readCO2()
{
  int co2_value = 0;  // Store the CO2 value inside this variable.


  // On most Arduino platforms this pin is used as an indicator light.
  //////////////////////////
  /* Begin Write Sequence */
  //////////////////////////
  Wire.beginTransmission(co2Addr);

  Wire.write(0x22);

  Wire.write(0x00);

  Wire.write(0x08);

  Wire.write(0x2A);

  Wire.endTransmission();
  /////////////////////////
  /* End Write Sequence. */
  /////////////////////////

  /*
    Wait 10ms for the sensor to process our command. The sensors's
    primary duties are to accurately measure CO2 values. Waiting 10ms
    ensures the data is properly written to RAM
  */
  delay(20);
  /////////////////////////
  /* Begin Read Sequence */
  /////////////////////////
  /*
    Since we requested 2 bytes from the sensor we must read in 4 bytes
    This includes the payload, checksum, and command status byte.
  */
  Wire.requestFrom(co2Addr, 4);
  byte i = 0;
  byte buffer[4] = {0, 0, 0, 0};
  /*
    Wire.available() is not necessary. Implementation is obscure but we
    leave it in here for portability and to future proof our code
  */

  while (Wire.available())
  {
    buffer[i] = Wire.read();
    i++;
  }
  ///////////////////////
  /* End Read Sequence */
  ///////////////////////
  /*
    Using some bitwise manipulation we will shift our buffer
    into an integer for general consumption
  */
  co2_value = 0;
  co2_value |= buffer[1] & 0xFF;
  co2_value = co2_value << 8;
  co2_value |= buffer[2] & 0xFF;
  byte sum = 0; //Checksum Byte
  sum = buffer[0] + buffer[1] + buffer[2]; //Byte addition utilizes overflow
  if (sum == buffer[3])
  {

   // Success!
    return co2_value;
  }
  else
  {
    /*
      Checksum failure can be due to a number of factors,
      fuzzy electrons, sensor busy, etc.
    */
     return 0;
  }
}

char *createMQTTmessage(int co2Value , const char* DataType)
{
  //Json object for MQTT
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  JSONencoder["RoomID"] = "1";
  JSONencoder["RoomName"] = MQTT_SUBSCRIBE_TOPIC_LEVEL_1;
  JSONencoder["SensorID"] = "1";
  JSONencoder["SensorName"] = "K30";
  JsonArray& Value = JSONencoder.createNestedArray("Value");
  JSONencoder["Unit"] = DataType;

  Value.add(co2Value);

  char JSONmessageBuffer[512];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
  
  //sprintf (buffer, "\"%s\": plus %d is %d", "RoomID",MQTT_SUBSCRIBE_TOPIC_LEVEL_1, b, a+b);
  //sprintf (msg, "\"RoomID\":\"%d\", \"RoomName\":\"%s\", \"SensorID\":\"%d\", \"SensorName\":\"K30\", \"Value\":\"%d\", \"Unit\":\"%s\"}", 1,MQTT_SUBSCRIBE_TOPIC_LEVEL_1, 1, co2Value, MQTT_PPM);
  //{'RoomID':'1', 'RoomName': 'MQTT_SUBSCRIBE_TOPIC_LEVEL_1', 'SensorID' : '1', 'SensorName':'K30', }
  //String message = "{\"RoomID\":\"" +  "1" + "\", " + "\"RoomName\":\"" + MQTT_SUBSCRIBE_TOPIC_LEVEL_1 + "\", " + "\"SensorID\":\"" + "1" + "\", " + "\"SensorName\":\"" + "K30" + "\", " + "\"Value\":\"" + co2Value + "\", "+ "\"Unit\":\"" + MQTT_PPM + "\"}";
  //char _co2Value[64];
  //snprintf(_co2Value, 64, "%.2f", co2Value);
  //String message = "{\"RoomID\":\"" + "test" + "\", " + "\"RoomName\":\"" + MQTT_SUBSCRIBE_TOPIC_LEVEL_1 + "\", " + "\"SensorID\":\"" + "001" + "\", " + "\"SensorName\":\"" + "K30" + "\", " + "\"Value\":\"" + _co2Value + "\", " + "\"Unit\":\"" + MQTT_PPM + "\"}";
  return JSONmessageBuffer;
}

void loop() {
  // make a string for assembling the data to log:
     String dataString = "";
  
 
  
  int co2Value = readCO2();
  if (co2Value > 0)
  {

     //math to get an easibly read time (millis() must be long)
       unsigned long msTime = millis();
       int hTime = msTime/3600000;
       int mTime = msTime/60000-hTime*60;
       int sTime = msTime/1000-mTime*60;

     //output also on Serial monitor for debugging
     Serial.print("Time since startup ");
     Serial.print(hTime);
     Serial.print("h:");
     Serial.print(mTime);
     Serial.print("m:");
     Serial.print(sTime);
     Serial.println("s");
     Serial.print("CO2 Value: ");
     Serial.print(co2Value);
     Serial.println(" ppm");
     Serial.println(); //make it easy on the eyes
     publishData(MQTT_PPM, createMQTTmessage(co2Value, MQTT_PPM));
//     if(co2Value > 1500)
//     {
//      turnLedOn(D8);
//      turnLedOff(D7);
//      turnLedOff(D6);
//     }
//     else if(co2Value > 1100)
//     {
//      turnLedOn(D7);
//      turnLedOff(D8);
//      turnLedOff(D6);
//     }
//     else
//     {
//      turnLedOn(D6);
//      turnLedOff(D8);
//      turnLedOff(D7);
//     }

  }
  else
  {
   Serial.println("Checksum failed / Communication failure");
   turnLedOnForMs(D6,200);
   turnLedOnForMs(D7,200);
   turnLedOnForMs(D8,200);
  }

  delay(readingTime);
}
