/*
  Analog Input and Digital Input

*/

int analogSensorPin = A0;    // select the pin for the analog sensor input
int digitalSensorPin = D2;   // select the pin for the digital sensor input
int analogSensorValue = 0;  // variable to store the value coming from the sensor
int digitalSensorValue = 0;  // variable to store the value coming from the sensor


void setup() {

  Serial.begin(9600);

  Serial.print("Analog Input and Digital Input \n");

  // declare the sensor pins as an INPUT:
  pinMode(analogSensorPin, INPUT);
  pinMode(digitalSensorPin, INPUT);
}

void loop() {
  // read the value from the sensor:
  analogSensorValue = analogRead(analogSensorPin);
  Serial.print("Analog Sensor Value: ");
  Serial.print(analogSensorValue);
  Serial.print("\n");
  delay(50);
  digitalSensorValue = digitalRead(digitalSensorPin);
  Serial.print("Digital Sensor Value: ");
  Serial.print(digitalSensorValue);
  Serial.print("\n");
  delay(500);
}
