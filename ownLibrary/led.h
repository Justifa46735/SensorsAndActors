void setupLED(int ledPin)
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void turnLedOn(int ledPin)
{
  digitalWrite(ledPin, HIGH);
}

void turnLedOff(int ledPin)
{
  digitalWrite(ledPin, LOW);
}

void turnLedOnForMs(int ledPin,long ms)
{
 digitalWrite(ledPin, HIGH);
 delay(ms);
 digitalWrite(ledPin, LOW);
}
