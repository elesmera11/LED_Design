/*
2_Row_Multiplexing.ino

The main code for the gesture-controlled LED matrix
Authors: Kate Chamberlin, Scott Davidsen, Fergus Duggan.
Date: 27 Aug 2018
*/

#include "pins.h"
#include "distance_LEDs.h"
#include "circBufT.h"
#include "swipe_control.h"

// Constants
#define ECHO_TIMEOUT 50000 //50ms


static circBuf_t x_circ_buff;
static circBuf_t y_circ_buff;
uint8_t counter = 0; //global to trigger determination of state when buffs full.

//Initialise al pins, buffers and serial output.
void setup() {  
  pinMode(TRIG_PIN_1, OUTPUT); // Sets the TRIG_PIN_ as an Output
  pinMode(ECHO_PIN_1, INPUT); // Sets the ECHO_PIN_ as an Input
  pinMode(TRIG_PIN_2, OUTPUT); // Sets the TRIG_PIN_ as an Output
  pinMode(ECHO_PIN_2, INPUT); // Sets the ECHO_PIN_ as an Input
  Serial.begin(115200); // Starts the serial communication
  
  pinMode(DIG_PIN_0, OUTPUT);
  pinMode(DIG_PIN_1, OUTPUT);
  pinMode(DIG_PIN_2, OUTPUT);
  pinMode(DIG_PIN_3, OUTPUT);
  pinMode(DIG_PIN_4, OUTPUT);
  
  pinMode(ANA_PIN_0, OUTPUT);
  pinMode(ANA_PIN_1, OUTPUT);
  pinMode(ANA_PIN_2, OUTPUT);
  pinMode(ANA_PIN_3, OUTPUT);
  pinMode(ANA_PIN_4, OUTPUT);
  
  initCircBuf(&x_circ_buff, BUFF_SIZE);
  initCircBuf(&y_circ_buff, BUFF_SIZE);
}

// Read the distance from the ultrasonic sensors
int readDistance(int trig_pin, int echo_pin) {
  // Clears the trigPin
  digitalWrite(trig_pin, LOW);
  delay(10);
  
  // Sets the trigPin on HIGH state for 50 milli seconds
  digitalWrite(trig_pin, HIGH);
  delay(20);
  digitalWrite(trig_pin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  unsigned long duration = pulseIn(echo_pin, HIGH, ECHO_TIMEOUT);
  
  // Calculating the distance in cm using speed of sound
  float distance = duration*0.034/2;
  // If out of bounds, reset
  if (distance > MAX_DISTANCE) { 
    distance = 0;
  }
  return distance;
}

void loop() {
  counter++;
  int x_distance = readDistance(TRIG_PIN_1, ECHO_PIN_1);
  int y_distance = readDistance(TRIG_PIN_2, ECHO_PIN_2);
  writeCircBuf(&x_circ_buff, x_distance);
  writeCircBuf(&y_circ_buff, y_distance);
  LEDControl(x_distance, y_distance); // Turn on the LEDs
  State state = Waiting;
  if (counter == BUFF_SIZE-1) {
    state = determine_state(&x_circ_buff, &y_circ_buff);
    switch(state) {
      case 0: Serial.print("WAITING\n"); break;
      case 1: Serial.print("LEFT\n"); break;
      case 2: Serial.print("RIGHT\n"); break;
      case 3: Serial.print("UP\n"); break;
      case 4: Serial.print("DOWN\n"); break;
    }
    counter = 0; //reset counter
  }
}
