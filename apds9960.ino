/****************************************************************
ER BROS LAB 

GESTURE control light

APDS-9960 library :- 
https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor



Hardware Connections:

IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt

Resources:
Include Wire.h and SparkFun_APDS-9960.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with SparkFun Arduino Pro Mini 3.3V

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.
****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin
#define a 3
#define b 4
#define c 5
#define d 6

// Constants
bool i = 0;
bool j = 0;
bool k = 0;
bool x = 0;

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

void setup() {

  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));
  
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
}

void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
  if (i == 1) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
  }
  if (j == 1) {
    digitalWrite(b, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
  }
  if (k == 1) {
    digitalWrite(c, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(d, LOW);
  }
  if (x == 1) {
    digitalWrite(d, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  }
  else {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        i = 1;
        j = 0;
        k = 0;
        x = 0;
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        i = 0;
        j = 1;
        k = 0;
        x = 0;
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        i = 0;
        j = 0;
        k = 1;
        x = 0;
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        i = 0;
        j = 0;
        k = 0;
        x = 1;
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        i = 1;
        j = 1;
        k = 1;
        x = 1;
        break;
      case DIR_FAR:
        Serial.println("FAR");
        i = 0;
        j = 0;
        k = 0;
        x = 0;
        break;

      default:
        Serial.println("NONE");
    }
  }
}
