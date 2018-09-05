/*
distance_LEDs.cpp

Module for controlling the LEDs on the device.
Authors: Kate Chamberlin, Scott Davidsen, Fergus Duggan.
Date: 03 Sep 2018
*/

#include "distance_LEDs.h"

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

// Turning on and off the LED's as a function of distance from the distance sensor
// Analogue - active low. Digital - active high.
void LEDControl(int x_distance, int y_distance) {
	//TODO adjust for y distance too.
	if (y_distance >= MIN_DISTANCE && y_distance < DIST_1) {
	  analogWrite(ANA_PIN_0, ANA_HIGH);
  	analogWrite(ANA_PIN_1, ANA_HIGH);
  	analogWrite(ANA_PIN_2, ANA_HIGH);
  	analogWrite(ANA_PIN_3, ANA_HIGH);
  	analogWrite(ANA_PIN_4, LOW);
	}
  else if (y_distance >= DIST_1 && y_distance < DIST_2) {
    analogWrite(ANA_PIN_0, ANA_HIGH);
    analogWrite(ANA_PIN_1, ANA_HIGH);
    analogWrite(ANA_PIN_2, ANA_HIGH);
    analogWrite(ANA_PIN_3, LOW);
    analogWrite(ANA_PIN_4, LOW);
  }
  else if (y_distance >= DIST_2 && y_distance < DIST_3) {
    analogWrite(ANA_PIN_0, ANA_HIGH);
    analogWrite(ANA_PIN_1, ANA_HIGH);
    analogWrite(ANA_PIN_2, LOW);
    analogWrite(ANA_PIN_3, LOW);
    analogWrite(ANA_PIN_4, LOW);
  }
  else if (y_distance >= DIST_3 && y_distance < DIST_4) {
    analogWrite(ANA_PIN_0, ANA_HIGH);
    analogWrite(ANA_PIN_1, LOW);
    analogWrite(ANA_PIN_2, LOW);
    analogWrite(ANA_PIN_3, LOW);
    analogWrite(ANA_PIN_4, LOW);
  }
  else if (y_distance >= DIST_4 && y_distance < MAX_DISTANCE) {
    analogWrite(ANA_PIN_0, LOW);
    analogWrite(ANA_PIN_1, LOW);
    analogWrite(ANA_PIN_2, LOW);
    analogWrite(ANA_PIN_3, LOW);
    analogWrite(ANA_PIN_4, LOW);
  }
  else {
    analogWrite(ANA_PIN_0, LOW);
    analogWrite(ANA_PIN_1, LOW);
    analogWrite(ANA_PIN_2, LOW);
    analogWrite(ANA_PIN_3, LOW);
    analogWrite(ANA_PIN_4, LOW);
  }
    
	if (x_distance >= MIN_DISTANCE && x_distance < DIST_1) {
		digitalWrite(DIG_PIN_0, LOW);
		digitalWrite(DIG_PIN_1, LOW);
		digitalWrite(DIG_PIN_2, LOW);
		digitalWrite(DIG_PIN_3, LOW);
	  digitalWrite(DIG_PIN_4, HIGH);
  }
  else if (x_distance >= DIST_1 && x_distance < DIST_2) {
    digitalWrite(DIG_PIN_0, LOW);
		digitalWrite(DIG_PIN_1, LOW);
		digitalWrite(DIG_PIN_2, LOW);
		digitalWrite(DIG_PIN_3, HIGH);
	  digitalWrite(DIG_PIN_4, HIGH); 
  }
  else if (x_distance >= DIST_2 && x_distance < DIST_3) {
    digitalWrite(DIG_PIN_0, LOW);
		digitalWrite(DIG_PIN_1, LOW);
		digitalWrite(DIG_PIN_2, HIGH);
		digitalWrite(DIG_PIN_3, HIGH);
	  digitalWrite(DIG_PIN_4, HIGH);
  }
  else if (x_distance >= DIST_3 && x_distance < DIST_4) {
    digitalWrite(DIG_PIN_0, LOW);
		digitalWrite(DIG_PIN_1, HIGH);
		digitalWrite(DIG_PIN_2, HIGH);
		digitalWrite(DIG_PIN_3, HIGH);
	  digitalWrite(DIG_PIN_4, HIGH);
  }
  else if (x_distance >= DIST_4 && x_distance <= MAX_DISTANCE) {
    digitalWrite(DIG_PIN_0, HIGH);
		digitalWrite(DIG_PIN_1, HIGH);
		digitalWrite(DIG_PIN_2, HIGH);
		digitalWrite(DIG_PIN_3, HIGH);
	  digitalWrite(DIG_PIN_4, HIGH);
  }
	else {
		digitalWrite(DIG_PIN_0, HIGH);
		digitalWrite(DIG_PIN_1, HIGH);
		digitalWrite(DIG_PIN_2, HIGH);
		digitalWrite(DIG_PIN_3, HIGH);
	  digitalWrite(DIG_PIN_4, HIGH);
	}
}
