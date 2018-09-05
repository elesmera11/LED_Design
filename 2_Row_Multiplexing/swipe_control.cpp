#include "swipe_control.h"

//Determines the state by looking at BUffer in quadrants
State determine_state(circBuf_t* x_buff, circBuf_t* y_buff) {
	//local variables
	float x_temp[BUFF_SIZE] = {0};
	float y_temp[BUFF_SIZE] = {0};
	float t_temp[BUFF_SIZE] = {0};	
	State state = Waiting;
	int size = 0;
	int x_time = 1;
	int y_time = 1;
	
	//populate x buffer and x_time buffer with datapoints, ignoring zeros.
	while (x_time <= BUFF_SIZE) {
		int temp = readCircBuf(x_buff);
		if (temp != 0) {
			x_temp[size] = temp;
			t_temp[size] = x_time;
			size++;
		}
		x_time++;
	}
	float x[size];
	float x_t[size];
	for (int i = 0; i < size; i++) {
		x[i] = x_temp[i];
		x_t[i] = t_temp[i];
	}
	
	//populate y buffer and y_time buffer with datapoints, ignoring zeros.
	size = 0;
	while (y_time <= BUFF_SIZE) {
		int temp = readCircBuf(y_buff);
		if (temp != 0) {
			y_temp[size] = temp;
			t_temp[size] = y_time;
			size++;
		}
		y_time++;
	}
	
	float y[size];
	float y_t[size];
	memset(t_temp, 0, BUFF_SIZE); //reset time buffer to zero
	for (int i = 0; i < size; i++) {
		y[i] = y_temp[i];
		y_t[i] = t_temp[i];
	}
	
	/* //read the circ buff into a local buffer
	for (int i = 0; i < BUFF_SIZE; i++) {
		x[i] = readCircBuf(x_buff);
		y[i] = readCircBuf(y_buff);
	} */
	
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
	float x_grad = simpLinReg(x_t, x, sizeof(x_t)/sizeof(float));
	float y_grad = simpLinReg(y_t, y, sizeof(y_t)/sizeof(float));
	Serial.print("X: ");
	Serial.println(x_grad, 4);
	Serial.print("Y: ");
	Serial.println(y_grad, 4);
	
	
	if (x_grad > y_grad) {
		if (x_grad > 0) {
			state = R_Swipe;
		} else {
			state = L_Swipe;
		}
	} else if (y_grad > x_grad) {
		if (y_grad > 0) {
			state = U_Swipe;
		} else {
			state = D_Swipe;
		}
	}
		
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