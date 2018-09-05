#include "swipe_control.h"

//Determines the state by looking at BUffer in quadrants
State determine_state(circBuf_t* x_buff, circBuf_t* y_buff) {
	//local variables
	float x[BUFF_SIZE];
	float y[BUFF_SIZE];
  float t[BUFF_SIZE];	
	State state = Waiting;
	
	//populate time vector with consecutive values.
	for (int i = 0; i < BUFF_SIZE; i++) {
		t[i] = (float)(i+1);
	}
	
	//read the circ buff into a local buffer
	for (int i = 0; i < BUFF_SIZE; i++) {
		x[i] = readCircBuf(x_buff);
		y[i] = readCircBuf(y_buff);
	}
	
	/* //go through each quadrant and average
	for (int i = Q_Zero; i <= Q_Three; i++) {
		for (int j = i * QUAD_SIZE; j < (i+1) * BUFF_SIZE; j++) {
			x_average[i] += readCircBuf(x_buff);
			y_average[i] += readCircBuf(y_buff);
		}
		//note these will be truncated as not float buffer
		x_average[i] = x_average[i] / QUAD_SIZE;
		//Serial.println(x_average[i]);
		y_average[i] = y_average[i] / QUAD_SIZE;
		//Serial.println(y_average[i]);

	} */
	/* //iteratively move through the buffer until a swipe has been determined.
	//if no swipe is selected, will default to waiting.
	//TODO currently there is a priority on x swipes which is not ideal.
	for (int i = Q_Zero; i <= Q_Three; i++) {
		
		//wraparound
		int next = i + 1;
		if (next == Q_Three + 1) {
			next = Q_Zero;
		}
		int next2 = i + 2;
		if (next2 == Q_Three + 1) {
			next2 = Q_Zero;
		} else if (next2 == Q_Three + 2) {
			next2 = Q_One;
		}
	} */
	
	//use linear regression to determine gradient of swipe
	float x_grad = simpLinReg(t, x, BUFF_SIZE);
	float y_grad = simpLinReg(t, y, BUFF_SIZE);
	Serial.print("X: ");
	Serial.println(x_grad, 4);
	Serial.print("Y: ");
	Serial.println(y_grad, 4);
	
	
		
		/* //if x distance decreases over time (by one section per quadrant)
		if (x_average[i] != 0) {
			Serial.println(x_average[i]);
			if (x_average[i] > x_average[next] + MIN_DISTANCE 
							 && x_average[next] > x_average[next2] + MIN_DISTANCE) {
				state = L_Swipe;
				break;
			}
			//if x distance increases over time		
			else if (x_average[i] + MIN_DISTANCE < x_average[next] 
							 && x_average[next] + MIN_DISTANCE < x_average[next2]) {
				state = R_Swipe;
				break;
			}
		} else if (y_average[i] != 0) {
			//if y distance decreases over time		
			if (y_average[i] > y_average[next] + MIN_DISTANCE 
							 && y_average[next] > y_average[next2] + MIN_DISTANCE) {
				state = D_Swipe;
				break;
			}
			//if y distance increases over time		
			else if (y_average[i] + MIN_DISTANCE < y_average[next] 
							 && y_average[next] + MIN_DISTANCE < y_average[next2]) {
				state = U_Swipe;
				break;
			}
		} */
	return state;
}			