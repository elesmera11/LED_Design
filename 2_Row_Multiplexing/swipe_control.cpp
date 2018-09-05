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
	memset(t_temp, 0, BUFF_SIZE); //reset temp time buffer to zero
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
	for (int i = 0; i < size; i++) {
		y[i] = y_temp[i];
		y_t[i] = t_temp[i];
	}
	
	//use linear regression to determine gradient of swipe
	float x_grad = simpLinReg(x_t, x, sizeof(x_t)/sizeof(float));
	float y_grad = simpLinReg(y_t, y, sizeof(y_t)/sizeof(float));
	Serial.print("X: ");
	Serial.println(x_grad, 4);
	Serial.print("Y: ");
	Serial.println(y_grad, 4);
	
	//determine state
	if (x_grad) {//if x has gradient change
		if (abs(x_grad) < abs(y_grad) && y_grad) {//if y also does, choose lowest grad
			if (y_grad > 0) {
				state = U_Swipe;
			} else {
				state = D_Swipe;
			}
		} else {
			if (x_grad > 0) {
				state = R_Swipe;
			} else {
				state = L_Swipe;
			}
		}
	} else if (y_grad) {
		if (abs(y_grad) < abs(x_grad) && x_grad) {
			if (x_grad > 0) {
				state = R_Swipe;
			} else {
				state = L_Swipe;
			}
		} else {
			if (y_grad > 0) {
				state = U_Swipe;
			} else {
				state = D_Swipe;
			}
		}
	}
	
	return state;
}			