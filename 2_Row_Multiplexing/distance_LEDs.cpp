/*
distance_LEDs.cpp

Module for controlling the LEDs on the device.
Authors: Kate Chamberlin, Scott Davidsen, Fergus Duggan.
Date: 03 Sep 2018
*/

#include "distance_LEDs.h"

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
