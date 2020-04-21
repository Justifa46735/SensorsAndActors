//#include <WiFi.h> //ESP32
#include <ESP8266WiFi.h> //ESP8266
#include <PubSubClient.h> //MQTT
#include "config.h"
#include "wifiJusti.h"
#include "mqttJusti.h"

#include <SoftwareSerial.h>


SoftwareSerial mySerial(D2,D1); // TX, RX

void setup() {
// for debuging
Serial.begin(115200);

// Use software serial
mySerial.begin(9600);

// connecting wifi and mqtt server
connectWifi();
Serial.println("Connecting to MQTT");
connectMqtt(MQTT_CLIENTID_9);

}

void loop() {
// put your main code here, to run repeatedly:
static int CheckFirst=0;
static int pm_add[3][5]={0,};
static int pm_old[3]={0,};
int chksum=0,res=0;;
unsigned char pms[32]={0,};


// PROBABLY BEST NOT TO CHANGE THESE VARIABLES
byte inputHigh = 0;
byte inputLow = 0;

uint16_t concPM1_0_CF1;                             // Lots of sensor variables
uint16_t concPM2_5_CF1;
uint16_t concPM10_0_CF1;
uint16_t concPM1_0_amb;
int concPM1_0_amb_int;
uint16_t concPM2_5_amb;
int concPM2_5_amb_int;
uint16_t concPM10_0_amb;
int concPM10_0_amb_int;
int concPM10_0_amb_int_2;
uint16_t rawGt0_3um;
uint16_t rawGt0_5um;
uint16_t rawGt1_0um;
uint16_t rawGt2_5um;
uint16_t rawGt5_0um;


if(mySerial.available()>=32)
{

for(int j=0; j<32 ; j++){
pms[j]=mySerial.read();
if(j<30)
chksum+=pms[j];
}

if(pms[30] != (unsigned char)(chksum>>8)
|| pms[31]!= (unsigned char)(chksum) ){


}
if(pms[0]!=0x42 || pms[1]!=0x4d )


Serial.println("PMS7003 read data: ");
Serial.print("PM1.0 ug/m3 Standard Particle: ");
Serial.print(pms[4]);
Serial.print(pms[5]);
Serial.println();
Serial.print("PM2.5 ug/m3 Standard Particle: ");
Serial.print(pms[6]);
Serial.print(pms[7]);
Serial.println();
Serial.print("PM10  ug/m3 Standard Particle: ");
Serial.print(pms[8]);
Serial.println(pms[9]);
Serial.println("Relevant data:");
Serial.print("PM1.0 ug/m3 Atmos. Environ: ");
Serial.print(pms[10]);
Serial.print(pms[11]);
Serial.println();
concPM1_0_amb = (pms[10] << 8) + pms[11];
concPM1_0_amb_int = uint8_t(pms[10])<<8 | uint8_t(pms[11]);
Serial.println(concPM1_0_amb);
Serial.println(concPM1_0_amb_int);
Serial.println("the last two were int");
Serial.print("pms [10] BIN ");
Serial.println(pms[10], BIN);
Serial.print("pms [11] BIN ");
Serial.println(pms[11], BIN);
Serial.print("PM2.5 ug/m3 Atmos. Environ: ");
Serial.print(pms[12]);
Serial.print(pms[13]);
Serial.println();
concPM2_5_amb = (pms[12]<< 8) + (pms[13]);
concPM2_5_amb_int = uint8_t(pms[12])<<8 | uint8_t(pms[13]);
Serial.println(concPM2_5_amb);
Serial.println(concPM2_5_amb_int);
Serial.println("the last two were int");
Serial.print("pms [12] BIN ");
Serial.println(pms[12], BIN);
Serial.print("pms [13] BIN ");
Serial.println(pms[13], BIN);
Serial.print("PM10  ug/m3 Atmos. Environ: ");
Serial.print(pms[14]);
Serial.println(pms[15]);
concPM10_0_amb = (pms[14]<< 8)+(pms[15]);
concPM10_0_amb_int = (pms[14]<< 8)+(pms[15]);
concPM10_0_amb_int_2= uint8_t(pms[14])<<8 | uint8_t(pms[15]);
Serial.println(concPM10_0_amb);
Serial.println(concPM10_0_amb_int);
Serial.println(concPM10_0_amb_int_2);
Serial.println("the last three were int");
Serial.print("pms [14] BIN ");
Serial.println(pms[14], BIN);
Serial.print("pms [15] BIN ");
Serial.println(pms[15], BIN);
Serial.print("Particle beyond 0.3 um in 0.1L air: ");
Serial.print(pms[16]);
Serial.println(pms[17]);
Serial.print("Particle beyond 0.5 um in 0.1L air: ");
Serial.print(pms[18]);
Serial.println(pms[19]);
Serial.print("Particle beyond 1.0 um in 0.1L air: ");
Serial.print(pms[20]);
Serial.println(pms[21]);
Serial.print("Particle beyond 2.5 um in 0.1L air: ");
Serial.print(pms[22]);
Serial.println(pms[23]);
Serial.print("Particle beyond 5.0 um in 0.1L air: ");
Serial.print(pms[24]);
Serial.println(pms[25]);
Serial.print("Particle beyond 10  um in 0.1L air: ");
Serial.print(pms[26]);
Serial.println(pms[27]);
Serial.println();

publishData(MQTT_PMS7003_TOPIC_LEVEL_1, MQTT_PM1, concPM1_0_amb_int);
publishData(MQTT_PMS7003_TOPIC_LEVEL_1, MQTT_PM2DOT5, concPM2_5_amb_int);
publishData(MQTT_PMS7003_TOPIC_LEVEL_1, MQTT_PM10, concPM10_0_amb);

}


delay(2000);}
