/**
 * CO2-Messung mit Sensor Typ MHZ19B
 * Messwerterfassung durch PWM-Signal
 */

// Der Sensor hängt an Pin 16

const int pwmpin = D0;

// Der eingestellte Messbereich (0-2000ppm)

const int range = 2000;

// Die setup()-Funktion

void setup() {

  // PWM-Pin auf Eingang setzen

  pinMode(pwmpin, INPUT);

  // Serielle Übertragung über USB initialisieren

  Serial.begin(9600);

}

// Die loop()-Funktion

void loop() {

  // Messung der PWM-Länge mittels einer eigenen Funktion

  int ppm_pwm = readCO2PWM();

  // Ausgabe der Werte über die serielle USB-Verbindung

  Serial.print("PPM PWM: ");
  Serial.println(ppm_pwm);

  // Messungen alle 3 Sekundn

  delay(3000);

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
