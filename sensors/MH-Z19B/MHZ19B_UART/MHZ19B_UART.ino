/**
 * CO2-Messung mit Sensor Typ MHZ19B
 * Messdatenerfassung über UART (serielle Schnittstelle)
 */

// Da die Hardware-UART des Arduino vom USB-Kabel belegt
// und über die Funktionen der Serial-Klasse schon
// verwendet werden, braucht es die SoftwareSerial-Klasse
// (gehört zu den Arduino-Standardklassen,
//  wenn du diese Programm mit dem esp8266 nutzen willst
//  musst du diese gegen ESPSoftwareSerial tauschen)
// mit deren Hilfe
// beliebige Pins als RX/TX-Verbindungen verwendet werden
// können (mit Ausname von Pin 0 und Pin 1)

#include <SoftwareSerial.h>

// Hier wird eine Instanz der Klasse mit den Pins 2 (RX) und 3 (TX)
// initialisiert ESP8266 D2 und D1

SoftwareSerial co2Serial(5, 4); // define MH-Z19 RX TX

// In der setup()-Funktion werden sowohl die Hardware-
// als auch die Software UART initialisiert

void setup() {

  Serial.begin(9600);

  co2Serial.begin(9600);

}

// Die loop() Funktion liest mit Hilfe der eigenen
// Funktion readSensor() die
// Sensorwerte aus und schreibt sie über die serielle
// USB-Verbindung auf den angeschlossenen Computer.

void loop() {

  int ppm, temperature = 0;

  readSensor(&ppm, &temperature);

  Serial.print("PPM: ");
  Serial.print(ppm);
  Serial.print(" Temperature: ");
  Serial.println(temperature);

  delay(5000);
}

// Die Funktion liest die CO2-Werte über die UART des
// Sensors ein und schreibt die ermittelten Werte mit
// Hilfe der übergebenen Pointer in die Variablen ppm
// und temperature.

void readSensor(int *ppm, int *temperature){

  // Die Befehlskette zum Einlesen des PPM-Wertes laut Datenblatt

  byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};

  // Speicherplatzreservierung von 9 Byte für die Antwort des Sensors.
  // Alles Befehle und Antworten des Sensors haben eine Länge von
  // 9 Byte, wobei das letzte Byte eine Prüfsumme zur Kontrolle
  // der Übermittlung darstellt.

  byte response[9];

  // Befehl zum Auslesen schreiben

  co2Serial.write(cmd, 9);

  // Zuerst den Eingangsbuffer löschen (mit 0 füllen) und
  // danach in einer while-Schleife darauf warten, bis
  // die Funktion co2Serial.available() einen Wert ungleich 0
  // zurückgibt.

  memset(response, 0, 9);
  while (co2Serial.available() == 0) {
    delay(1000);
  }

  // Die Antwort wird in den Speicher eingelesen.

  co2Serial.readBytes(response, 9);

  // Die Prüfsumme mit Hilfe einer eigenen Funk-
  // tion errechnen, um zu klären, ob die
  // Übertragung fehlerfrei abgelaufen ist.

  byte check = getCheckSum(response);

  if (response[8] != check) {
    Serial.println("Fehler in der Übertragung!");
    return;
  }

  // PPM-Wert errechnen, sie finden sind
  // im 3. und 4. Byte der Antwort im Format
  // HIGH-Byte und LOW-Byte und müssen über die
  // folgende Formel zu einem Word (int) verkettet
  // werden.

  *ppm = 256 * (int)response[2] + response[3];

  // Temperaturwert wird als 5. Byte der Response
  // übermittelt (im Datenblatt nicht angegeben).
  // Damit auch negative Temperaturen übertragen
  // werden können, wurde der Wert 40 dazuaddiert,
  // der jetzt wieder entfernt werden muss.

  *temperature = response[4] - 40;

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
