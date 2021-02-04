/*
  Servo
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/cautious-spoon/blob/master/LICENSE
*/

#include <Servo.h>

const int SERVO = 7; //Servo on Pin 7
const int SWITCH = 2;
Servo myServo; //Create an object if the Servo class

void setup()
{
  pinMode (SWITCH, INPUT_PULLUP);
  //Create the Servo Object and pass pin number
  myServo.attach(SERVO);
}

void loop()
{
  myServo.write(90); //moves the servo to 90 deg
  while (digitalRead (SWITCH) == HIGH) {
  }
  myServo.write(30); //moves the servo to right
  delay (500);
  myServo.write(150); //moves the servo to left
  delay (500);
}
