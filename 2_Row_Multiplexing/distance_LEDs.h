#ifndef DISTANCE_LEDS_H_
#define DISTANCE_LEDS_H_

#include "circBufT.h"

#define MIN_DISTANCE 3
#define DIST_1 6
#define DIST_2 9
#define DIST_3 12
#define DIST_4 15
#define MAX_DISTANCE 18

void LEDControl(int x_distance, int y_distance);
#endif /*DISTANCE_LEDS_H_*/
