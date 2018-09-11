/*
distance_LEDs.h

Functions for controlling the LEDs, max/min distances, 
and spacial sectioning.
Authors: Kate Chamberlin, Scott Davidsen, Fergus Duggan.
Date: 03 Sep 2018
*/
#ifndef DISTANCE_LEDS_H_
#define DISTANCE_LEDS_H_

#include "pins.h"
#include "arrows.h"
#include "Arduino.h"

// Constants
#define MATRIX_SIZE 5
#define ECHO_TIMEOUT 50000 //50ms
#define MIN_DISTANCE 3
#define DIST_1 6
#define DIST_2 9
#define DIST_3 12
#define DIST_4 15
#define MAX_DISTANCE 18

//void swap(bool *x, bool *y);

//void rotate_CW(bool* data[MATRIX_SIZE][MATRIX_SIZE]);

int readDistance(int trig_pin, int echo_pin);

//void update_row(int row, bool LED_mask[MATRIX_SIZE]);

void LEDControl(int x_distance, int y_distance);
#endif /*DISTANCE_LEDS_H_*/
