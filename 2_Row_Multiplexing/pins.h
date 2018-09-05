/*
pins.h

Definitions for all relevant pins and global constants.
Can be adjusted to suit new microcontroller (pin defs and 
analogue high voltage) or speed of response (Buff_size).
Authors: Kate Chamberlin, Scott Davidsen, Fergus Duggan.
Date: 03 Sep 2018
*/
#ifndef PINS_H_
#define PINS_H_

//digital pins
#define DIG_PIN_0 2
#define DIG_PIN_1 3
#define DIG_PIN_2 4
#define DIG_PIN_3 5
#define DIG_PIN_4 6

//analogue pins
#define ANA_PIN_0 A0
#define ANA_PIN_1 A1
#define ANA_PIN_2 A2
#define ANA_PIN_3 A3
#define ANA_PIN_4 A4

//sensor pins
#define TRIG_PIN_1 8
#define ECHO_PIN_1 9
#define TRIG_PIN_2 10
#define ECHO_PIN_2 11

//global constants
#define ANA_HIGH 255
#define BUFF_SIZE 20

#endif /*PINS_H_*/
