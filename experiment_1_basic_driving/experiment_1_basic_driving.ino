/*
  Basic Drive Functions for the Rover
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-tribble/blob/master/LICENSE
*/

const int MOTOR_A_DIRECTION = 12;
const int MOTOR_A_BRAKE = 9;
const int MOTOR_A_SPEED = 3;
const int MOTOR_B_DIRECTION = 13;
const int MOTOR_B_BRAKE = 8;
const int MOTOR_B_SPEED = 11;

void setup() {
  //Set digital control pins as output
  pinMode (MOTOR_A_DIRECTION, OUTPUT);
  pinMode (MOTOR_A_BRAKE, OUTPUT);
  pinMode (MOTOR_B_DIRECTION, OUTPUT);
  pinMode (MOTOR_B_BRAKE, OUTPUT);
  //Ensure motors are stopped
  brake ("right");
  brake ("left");
  delay (4000); // Pause before starting sequence
}

void loop() {
  //forward for 2 seconds at full speed
  forward ("right", 255);
  forward ("left", 255);
  delay (2000);
  //reverse for 2 seconds at full speed
  reverse ("right", 255);
  reverse ("left", 255);
  delay (2000);
  //forward hard left turn at full speed
  forward ("right", 255);
  brake ("left");
  delay (2000);
  //reverse hard left turn at full speed
  reverse ("right", 255);
  brake ("left");
  delay (2000);
  //forward hard right turn at full speed
  forward ("left", 255);
  brake ("right");
  delay (2000);
  //reverse hard right turn at full speed
  reverse ("left", 255);
  brake ("right");
  delay (2000);
  //forward for 2 seconds at low speed
  forward ("right", 80);
  forward ("left", 80);
  delay (2000);
  //reverse for 2 seconds at low speed
  reverse ("right", 80);
  reverse ("left", 80);
  delay (2000);
  // stop
  brake ("right");
  brake ("left");
  delay (2000);
}

void forward (String motor, int speed) {
  if (motor == "right") {
    digitalWrite(MOTOR_A_DIRECTION, LOW); //Forward direction of Ch A
    digitalWrite(MOTOR_A_BRAKE, LOW); //Disengage the brake for Ch A
    analogWrite(MOTOR_A_SPEED, speed); //Drive motor on Ch A at set speed
  } else {
    digitalWrite(MOTOR_B_DIRECTION, LOW); //Forward direction of Ch B
    digitalWrite(MOTOR_B_BRAKE, LOW); //Disengage the brake for Ch B
    analogWrite(MOTOR_B_SPEED, speed); //Drive motor on Ch B at set speed
  }
}

void reverse (String motor, int speed) {
  if (motor == "right") {
    digitalWrite(MOTOR_A_DIRECTION, HIGH); //Reverse direction of Ch A
    digitalWrite(MOTOR_A_BRAKE, LOW); //Disengage the brake for Ch A
    analogWrite(MOTOR_A_SPEED, speed); //Drive motor on Ch A at set speed
  } else {
    digitalWrite(MOTOR_B_DIRECTION, HIGH); //Reverse direction of Ch B
    digitalWrite(MOTOR_B_BRAKE, LOW); //Disengage the brake for Ch B
    analogWrite(MOTOR_B_SPEED, speed); //Drive motor on Ch B at set speed
  }
}

void brake (String motor) {
  if (motor == "right") {
    digitalWrite(MOTOR_A_BRAKE, HIGH); //Engage the brake for Ch A
  } else {
    digitalWrite(MOTOR_B_BRAKE, HIGH); //Engage the brake for Ch B
  }
}
