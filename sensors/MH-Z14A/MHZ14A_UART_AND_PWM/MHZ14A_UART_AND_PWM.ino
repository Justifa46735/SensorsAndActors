/**
 * CO2-Messung mit Sensor Typ MHZ14A
 * Messdatenerfassung über UART (serielle Schnittstelle)
 * und
 * Messwerterfassung durch PWM-Signal
 */

//#include <WiFi.h> //ESP32
#include <ESP8266WiFi.h> //ESP8266
#include <PubSubClient.h> //MQTT
#include "config.h"
#include "wifiJusti.h"
#include "mqttJusti.h"

//define bme value variables
int ppm    = 0.0;  // PPM from UART
int temperature = 0.0;  // Temperatur from Uart
int ppm_pwm    = 0.0;  // PPM from PWM

// Da die Hardware-UART des Arduino vom USB-Kabel belegt
// und über die Funktionen der Serial-Klasse schon 
// verwendet werden, braucht es die SoftwareSerial-Klasse
// (gehört zu den Arduino-Standardklassen, 
//  wenn du diese Programm mit dem esp8266 nutzen willst
//  musst du diese gegen ESPSoftwareSerial tauschen)
// mit deren Hilfe
// beliebige Pins als RX/TX-Verbindungen verwendet werden
// können (mit Ausname von Pin 0 und Pin 1)

#include "SoftwareSerial.h"

// Hier wird eine Instanz der Klasse mit den Pins 2 (RX) und 3 (TX)
// initialisiert ESP8266 D2 und D1 


// Die Befehlskette zum Einlesen des PPM-Wertes laut Datenblatt und
// Speicherplatzreservierung von 9 Byte für die Antwort des Sensors.
// Alles Befehle und Antworten des Sensors haben eine Länge von
// 9 Byte, wobei das letzte Byte eine Prüfsumme zur Kontrolle
// der Übermittlung darstellt.

byte mhzResp[9];    // 9 bytes bytes response  
byte mhzCmdReadPPM[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
byte mhzCmdCalibrateZero[9] = {0xFF,0x01,0x87,0x00,0x00,0x00,0x00,0x00,0x78};
byte mhzCmdReset[9] = {0xFF,0x01,0x8d,0x00,0x00,0x00,0x00,0x00,0x72};

// Set Range
byte mhzCmdMeasurementRange1000[9] = {0xFF,0x01,0x99,0x00,0x00,0x00,0x03,0xE8,0x7B};
byte mhzCmdMeasurementRange2000[9] = {0xFF,0x01,0x99,0x00,0x00,0x00,0x07,0xD0,0x8F};
byte mhzCmdMeasurementRange3000[9] = {0xFF,0x01,0x99,0x00,0x00,0x00,0x0B,0xB8,0xA3};
byte mhzCmdMeasurementRange5000[9] = {0xFF,0x01,0x99,0x00,0x00,0x00,0x13,0x88,0xCB};

// Enable and Disable Auto Base Correction
byte mhzCmdABCEnable[9] = {0xFF,0x01,0x79,0xA0,0x00,0x00,0x00,0x00,0xE6};
byte mhzCmdABCDisable[9] = {0xFF,0x01,0x79,0x00,0x00,0x00,0x00,0x00,0x86};


SoftwareSerial co2Serial(5, 4); // define MH-Z19 RX TX 

// Die PWM hängt an Pin 16

const int pwmpin = D0;

// Der eingestellte Messbereich (0-5000ppm)

const int range = 5000;

// In der setup()-Funktion werden sowohl die Hardware-
// als auch die Software UART initialisiert
 
void setup() {
  
  Serial.begin(9600);

  // PWM-Pin auf Eingang setzen
  pinMode(pwmpin, INPUT);
  
  co2Serial.begin(9600);

  // connecting wifi and mqtt server
  connectWifi();
  Serial.println("Connecting to MQTT");
  connectMqtt(MQTT_CLIENTID_8);
  
}

// Die loop() Funktion liest mit Hilfe der eigenen
// Funktion readSensor() die
// Sensorwerte aus und schreibt sie über die serielle
// USB-Verbindung auf den angeschlossenen Computer.
 
void loop() {

  // Messung der PWM-Länge mittels einer eigenen Funktion

  ppm_pwm = readCO2PWM();

  // Ausgabe der Werte über die serielle USB-Verbindung

  Serial.print("PPM PWM: ");
  Serial.println(ppm_pwm);
  publishData(MQTT_MHZ14A_TOPIC_LEVEL_1, MQTT_PPM_PWM, ppm_pwm);
  delay(1000);
  
  readSensor(&ppm, &temperature);

  Serial.print("PPM: ");
  Serial.print(ppm);
  Serial.print(" Temperature: ");
  Serial.println(temperature);
  publishData(MQTT_MHZ14A_TOPIC_LEVEL_1, MQTT_PPM, ppm);
  publishData(MQTT_MHZ14A_TOPIC_LEVEL_1, MQTT_TEMPERATURE, temperature);
  
  delay(4000);
}

// Die Messung der PWM-Länge erfolgt in einer eigenen
// Funktion readCO2PWM(), was die loop()-Schleife etwas "aufgeräumter"
// erscheinen lässt. Die Funktion gibt eine Ganzzahl zurück (int).

int readCO2PWM() {

  // Es werden die für die Umrechnung der Zeitdauer auf
  // die PPM-Werte benötigten Variablen definiert.
  // Da es sich bei th um große Werte handeln kann - die verwendete
  // Arduino-Funktion gibt Mikrosekunden zurück - wird diese Variable
  // als vorzeichenlose (unsigned) große Ganzzahl (long) definiert.

  unsigned long th;
  int ppm_pwm = 0;
  float pulsepercent;

  // Alles, was in der do ... while-Schleife steht, wird
  // solange ausgeführt, bis der Ausdruck nach while, hier
  // th == 0 als zutreffend (wahr) erkannt wird.
  // Da die Arduino-Funktion pulseIn() 0 zurückgibt, solange
  // sie am Messen ist, dient die Schleife dazu, auf den
  // Messwert zu warten.

  do {

    // pulseIn gibt die Dauer des am Pin (pwmpin) anliegenden
    // Signals in Mikrosekunden an. Da die maximale Signallänge
    // 1004ms ist, wird als timeoutwert 1004000µs angegeben.
    // Die Ausgabe der pulseIn()-Funktion wird durch 1000 geteilt
    // und ergibt so für th die Signallänge in Millisekunden (ms).

    th = pulseIn(pwmpin, HIGH, 1004000) / 1000;

    // Pulslänge in Prozent (%)

    float pulsepercent = th / 1004.0;

    // PPM-Werte bei gegebenem Range

    ppm_pwm = range * pulsepercent;

  } while (th == 0);

  // Der gemessene Wert wird an die loop()-Funktion zurückgegeben,
  // wo er dann ausgegeben wird.

  return ppm_pwm;
}

// Die Funktion liest die CO2-Werte über die UART des
// Sensors ein und schreibt die ermittelten Werte mit
// Hilfe der übergebenen Pointer in die Variablen ppm
// und temperature.

void readSensor(int *ppm, int *temperature){

  // Befehl zum Auslesen schreiben
  
  co2Serial.write(mhzCmdReadPPM, 9);

  // Zuerst den Eingangsbuffer löschen (mit 0 füllen) und
  // danach in einer while-Schleife darauf warten, bis 
  // die Funktion co2Serial.available() einen Wert ungleich 0
  // zurückgibt.
  
  memset(mhzResp, 0, 9);
  while (co2Serial.available() == 0) {
    delay(1000);
  }

  // Die Antwort wird in den Speicher eingelesen.
  
  co2Serial.readBytes(mhzResp, 9);

  // Die Prüfsumme mit Hilfe einer eigenen Funk-
  // tion errechnen, um zu klären, ob die 
  // Übertragung fehlerfrei abgelaufen ist.
  
  byte check = getCheckSum(mhzResp);
  
  if (mhzResp[8] != check) {
    Serial.println("Fehler in der Übertragung!");
    return;
  }
 
  // PPM-Wert errechnen, sie finden sind
  // im 3. und 4. Byte der Antwort im Format
  // HIGH-Byte und LOW-Byte und müssen über die
  // folgende Formel zu einem Word (int) verkettet
  // werden.
  
  *ppm = 256 * (int)mhzResp[2] + mhzResp[3];

  // Temperaturwert wird als 5. Byte der Response
  // übermittelt (im Datenblatt nicht angegeben).
  // Damit auch negative Temperaturen übertragen 
  // werden können, wurde der Wert 40 dazuaddiert,
  // der jetzt wieder entfernt werden muss.
  
  *temperature = mhzResp[4] - 40;

}

// Die Funktion errechnet eine Prüfsumme über die
// durch einen Zeiger übergebene Befehls- oder
// Antwortkette. Der Algorithmus zur 
// Prüfsummenberechnung findet sich im
// Datenblatt.

byte getCheckSum(byte *packet) {
  byte i;
  byte checksum = 0;
  for (i = 1; i < 8; i++) {
    checksum += packet[i];
  }
  checksum = 0xff - checksum;
  checksum += 1;
  return checksum;
}
