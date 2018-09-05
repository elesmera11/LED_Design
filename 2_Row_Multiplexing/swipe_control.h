/*
swipe_control.h

Module for determining the gesture state of the device.
Enum of state included.
Authors: Kate Chamberlin, Scott Davidsen, Fergus Duggan.
Date: 03 Sep 2018
*/

#ifndef SWIPE_CONTROL_H_
#define SWIPE_CONTROL_H_

#include "Arduino.h"
#include "pins.h"
#include "circBufT.h"
#include "regression.h"


enum State{Waiting, L_Swipe, R_Swipe, U_Swipe, D_Swipe}; //swipe states

//Determines the state dependent on distance gradients.
State determine_state(float x_grad, float y_grad);

//Process the buffers so that the gesture state can be determined.
State process_buffs(circBuf_t* x_buff, circBuf_t* y_buff);

#endif /*SWIPE_CONTROL_H_*/