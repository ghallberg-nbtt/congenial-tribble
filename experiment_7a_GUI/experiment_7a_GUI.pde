/*
 Rover control GUI
 Copyright 2020 Gary Hallberg
 Licensed under MIT https://github.com/ghallberg-nbtt/congenial-tribble/blob/master/LICENSE
 */

import controlP5.*; //Import ControlP5 library
import processing.serial.*; //Serial port communications

ControlP5 cp5; //Create ControlP5 object
PFont font; //Object for the font
Serial port; //Object of the serial port

void setup() {
  size(800, 500); 
  cp5 = new ControlP5(this);
  font = createFont("arial", 20);  //Use arial font for buttons 20pt
  cp5.addButton("forward")  //"forward" is the name of button
    .setPosition(440, 60) //x and y coordinates of upper left corner of button
    .setSize(120, 120) //(width, height)
    .setFont(font)
    ;   
  cp5.addButton("right")     
    .setPosition(580, 200)  
    .setSize(120, 120)      
    .setFont(font)
    ;   
  cp5.addButton("reverse")     
    .setPosition(440, 340) 
    .setSize(120, 120)     
    .setFont(font)
    ;  
  cp5.addButton("left")    
    .setPosition(300, 200)  
    .setSize(120, 120)     
    .setFont(font)
    ;
  cp5.addButton("stop")    
    .setPosition(440, 200)  
    .setSize(120, 120)     
    .setFont(font)
    ;
  cp5.addButton("high") //High speed   
    .setPosition(100, 140)  
    .setSize(120, 80)     
    .setFont(font)
    ;
  cp5.addButton("low") //Low speed
    .setPosition(100, 280)  
    .setSize(120, 80)     
    .setFont(font)
    ;

  background(77, 166, 255); // background color of window (r, g, b) or (0 to 255)

  //title for our window
  fill(0, 0, 0);  //text color (r, g, b)
  textFont(font);
  text("ROVER CONTROL", 325, 30);  // ("text", x coordinate, y coordinate)

  fill(80, 80, 80);  //text color (r, g, b)
  text("direction", 460, 490);  // ("text", x coordinate, y coordinate)
  text("speed", 133, 395);  // ("text", x coordinate, y coordinate)

  printArray(Serial.list());  //prints all available serial ports
  port = new Serial(this, "COM10", 9600); //com port of the Arduino
}

void draw() {  //same as loop in Arduino
  //No need for code here just yet
}

//Functions to act on button presses
//Called when matched to button name
void forward(){
  port.write('f'); //Send 'f' to serial port
}

void reverse(){
  port.write('b');
}

void right(){
  port.write('r');
}

void left(){
  port.write('l');
}

void stop(){
  port.write('s');
}

void high(){
  port.write('2');
}

void low(){
  port.write('1');
}
