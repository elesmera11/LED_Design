#include "Arduino.h"
#include "pins.h"
#include "circBufT.h"
#include "swipe_control.h"

#define QUAD 4
#define QUAD_SIZE (BUFF_SIZE / QUAD)

enum Quadrant{Q_Zero, Q_One, Q_Two, Q_Three}; // Quadrants of the buffers.
enum State{Waiting, L_Swipe, R_Swipe, U_Swipe, D_Swipe, Unsure}; //swipe states

//Determines the state by looking at BUffer in quadrants
State determine_state(circBuf_t* x_buff, circBuf_t* y_buff) {
	uint8_t average[QUAD];
	enum State state;
	//go through each quadrant
	for (int i = Q_Zero; i <= Q_Three; i++) {
		for (int j = i * QUAD_SIZE; j < (i+1) * BUFF_SIZE; j++) {
			average[i] += x_buff->data[j];
		}
		average[i] = average[i] / QUAD_SIZE;