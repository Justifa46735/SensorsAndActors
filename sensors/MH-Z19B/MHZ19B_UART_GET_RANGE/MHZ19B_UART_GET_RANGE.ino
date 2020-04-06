/**
 * CO2-Messung mit Sensor Typ MHZ19B
 * Der Sketch ermittelt den eingestellten Messbereich
 * von 0-2000ppm oder 0-5000ppm
 * Es ist eine UART-Verdrahtung notwendig
 */

// Die SoftwareSerial-Klasse gehört zu den Arduino-Standardklassen.
// Wenn du diese Programm mit dem esp8266 nutzen willst
// musst du diese gegen die ESPSoftwareSerial libary tauschen)

#include <SoftwareSerial.h>

//set SoftwareSerial for Esp to pin D2 and D1
SoftwareSerial co2Serial(5, 4); // define MH-Z19 RX TX

// Der Befehl ist im Datenblatt nicht dokumentiert, hier gefunden:
// https://revspace.nl/MH-Z19B
byte cmd_getrange[9] = {0xFF,0x01,0x9B,0x00,0x00,0x00,0x00,0x00,0x64};

void setup() {
  Serial.begin(9600);
  co2Serial.begin(9600);
  delay(2000);
  readRange();
}

void loop() {
  // do nothing here.
}

void readRange() {
  byte response[9]; // for answer
  co2Serial.write(cmd_getrange, 9); //request range
  memset(response, 0, 9);
  int i = 0;
  while (co2Serial.available() == 0) {
    i++;
  }
  if (co2Serial.available() > 0) {
      co2Serial.readBytes(response, 9);
  }
  unsigned int range = response[4] * 256 + response[5];
  Serial.print("Range: ");
  Serial.println(range);
}
