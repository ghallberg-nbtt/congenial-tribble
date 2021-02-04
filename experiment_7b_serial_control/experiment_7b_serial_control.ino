/*
  Object Avoidance
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-tribble/blob/master/LICENSE
*/

#include <Servo.h>

const int MOTOR_A_DIRECTION = 12;
const int MOTOR_A_BRAKE = 9;
const int MOTOR_A_SPEED = 3;
const int MOTOR_B_DIRECTION = 13;
const int MOTOR_B_BRAKE = 8;
const int MOTOR_B_SPEED = 11;
const int SWITCH = 2;
const int LED = 4;
const int RIGHT_SENSOR = 5;
const int LEFT_SENSOR = 6;
const int SERVO = 7;
const int ECHO = 10;
const int TRIGGER = A2;
const int speed = 120;
const int range = 30;
// variables will change:
boolean previousButton = HIGH; // Previous button state
boolean currentButton = HIGH; // Current button state
int function = 1; //Holds the selected function
boolean printOnce = false; //We only want to print to serial monitor on button press
float duration; //time of HC-SR04 pulse
float distance; // calculated distance
int speedBluetooth = 120;
//objects
Servo myServo; //Create an object if the Servo class

void setup() {
  //Set digital control pins as output
  pinMode (MOTOR_A_DIRECTION, OUTPUT);
  pinMode (MOTOR_A_BRAKE, OUTPUT);
  pinMode (MOTOR_B_DIRECTION, OUTPUT);
  pinMode (MOTOR_B_BRAKE, OUTPUT);
  pinMode (SWITCH, INPUT_PULLUP);
  pinMode (LED, OUTPUT);
  pinMode (RIGHT_SENSOR, INPUT);
  pinMode (LEFT_SENSOR, INPUT);
  pinMode (TRIGGER, OUTPUT);
  pinMode (ECHO, INPUT);
  //Ensure motors are stopped
  brake ("right");
  brake ("left");
  digitalWrite (LED, LOW); //Turn off LED
  delay (2000); // Pause before starting
  Serial.begin (9600);
  //Create the Servo Object and pass pin number
  myServo.attach(SERVO);
  myServo.write(90); //look ahead
  delay (500);

}

void loop() {
  //read switch and debounce
  currentButton = digitalRead(SWITCH); // Read the switch state
  if (previousButton != currentButton)  // If switch pressed
  {
    delay(5);  // Wait 5ms
    currentButton = digitalRead(SWITCH);  // Read switch again
  }

  if (previousButton == HIGH && currentButton == LOW)  // Detect a button press
  {
    printOnce = false;
    //Increment function selection
    function++; // increment function by 1
    if (function == 5) {
      function = 1; //allow the function to cycle 1 thru 4
    }
    //Flash LED
    switch (function) {
      case 1:
        //Standby
        //1 LED flash
        flashLED (function);
        break;
      case 2:
        //Line follower
        //2 LED flashes
        flashLED (function);
        break;
      case 3:
        //Object avoidance
        //3 LED flashes
        flashLED (function);
        break;
      case 4:
        //Bluetooth control
        //4 LED flashes
        flashLED (function);
        break;
    }
  }
  previousButton = currentButton;  // Reset button value
  //Act on function selection
  switch (function) {
    case 1:
      //Standby
      brake ("right");
      brake ("left");
      if (!printOnce) {
        Serial.println ("Function 1 - Standby");
      }
      printOnce = true;
      break;
    case 2:
      //Line follower
      if (!printOnce) {
        Serial.println ("Function 2 - Line Follower");
      }
      printOnce = true;
      followLine();
      break;
    case 3:
      //Object avoidance
      if (!printOnce) {
        Serial.println ("Function 3 - Object Avoidance");
      }
      printOnce = true;
      avoidObject ();
      break;
    case 4:
      //Bluetooth control
      if (!printOnce) {
        Serial.println ("Function 4 - Bluetooth Control");
        brake ("right");
        brake ("left");
      }
      printOnce = true;
      remoteControl();
      break;
  }
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

void flashLED (int numberOfFlashes) {
  for (int i = 0; i < numberOfFlashes; i++) {
    digitalWrite (LED, HIGH);
    delay (250);
    digitalWrite (LED, LOW);
    delay (250);
  }
}

void followLine() {
  //read state of sensors
  boolean lineDetectedRight = digitalRead (RIGHT_SENSOR);
  boolean lineDetectedLeft = digitalRead (LEFT_SENSOR);
  if (!lineDetectedRight && !lineDetectedLeft) {
    //Drive forward
    forward ("right", 60);
    forward ("left", 60);
  } else if (lineDetectedRight && !lineDetectedLeft) {
    //Turn right
    brake ("right");
    forward ("left", 60);
  } else if (!lineDetectedRight && lineDetectedLeft) {
    //Turn left
    forward ("right", 60);
    brake ("left");
  } else {
    //Both sensors trigger - stop!
    brake ("right");
    brake ("left");
  }
}

void avoidObject() {
  //Take a reading to detect object
  distance = measureDistance();
  if (distance < range) {
    brake ("left");
    brake ("right");
    delay (250); //stop for 1/4 second
    int direction = random(2); //0 = right and 1 = left
    if (direction == 0) {
      myServo.write (30);
    } else {
      myServo.write (150);
    }
    delay (500);
    //Take another object reading
    distance = measureDistance();
    myServo.write(90); //look ahead
    delay (500);
    if (distance < range) {
      //look in opposite direction
      if (direction == 0) {
        myServo.write (150);
      } else {
        myServo.write (30);
      }
      delay (500);
      //Take distance reading in opposite direction
      distance = measureDistance();
      myServo.write(90); //look ahead
      delay (500);
      if (distance < range) {
        //Reverse
        reverse ("right", speed);
        reverse ("left", speed);
        delay (2000);
        if (direction == 0) {
          brake ("right");
          forward ("left", speed);
        } else {
          forward ("right", speed);
          brake ("left");
        }
        delay (500);
      } else {
        //turn in that direction
        if (direction == 0) {
          //reverse a little
          reverse ("right", speed);
          reverse ("left", speed);
          delay (500);
          //Turn right
          brake ("right");
          forward ("left", speed);
          delay (500);
        } else {
          //reverse a little
          reverse ("right", speed);
          reverse ("left", speed);
          delay (500);
          //Turn left
          forward ("right", speed);
          brake ("left");
          delay (500);
        }
      }
    } else {
      //Turn in that direction
      if (direction == 0) {
        //reverse a little
        reverse ("right", speed);
        reverse ("left", speed);
        delay (500);
        //Turn right
        brake ("right");
        forward ("left", speed);
        delay (500);
      } else {
        //reverse a little
        reverse ("right", speed);
        reverse ("left", speed);
        delay (500);
        //Turn left
        forward ("right", speed);
        brake ("left");
        delay (500);
      }
    }
  } else {
    forward ("right", speed);
    forward ("left", speed);
  }
}

float measureDistance () {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  float functionDistance = (duration / 58);
  return functionDistance;
}

void remoteControl() {
  if (Serial.available()) { //if data is available to read
    char val = Serial.read();
    if (val == 'f') { //if f received
      forward ("right", speedBluetooth);
      forward ("left", speedBluetooth);
    }
    if (val == 'b') { //if b received
      reverse ("right", speedBluetooth);
      reverse ("left", speedBluetooth);
    }
    if (val == 'r') { //if r received
      brake ("right");
      forward ("left", speedBluetooth);
    }
    if (val == 'l') { //if l received
      forward ("right", speedBluetooth);
      brake ("left");
    }
    if (val == 's') { //if s received
      brake ("right");
      brake ("left");
    }
    if (val == '1') { //if 1 received
      speedBluetooth = 120;
    }
    if (val == '2') { //if 2 received
      speedBluetooth = 220;
    }
  }
}
