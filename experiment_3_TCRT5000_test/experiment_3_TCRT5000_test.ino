/*
  TCRT5000 Test
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-tribble/blob/master/LICENSE
*/

const int DO_PIN = 5;
const int AO_PIN = 2;

void setup() {
  pinMode (DO_PIN, INPUT); //Read DO from sensor
  Serial.begin (9600);
}

void loop() {
  int DO = digitalRead (DO_PIN);
  int A0 = analogRead (AO_PIN);
  if (DO == HIGH) {
    Serial.print ("DO HIGH - sensor not triggered. ");
  } else {
    Serial.print ("DO LOW - sensor triggered. ");
  }
  Serial.print ("Analog Output: ");
  Serial.println (A0);
  delay (250);
}
