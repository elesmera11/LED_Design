/*
Linear regression code provided by John Brooks - Smarter Every Day
http://jwbrooks.blogspot.com/2014/02/arduino-linear-regression-function.html
Edited by Kate Chamberlin, Scott Davidsen, Fergus Duggan.
*/


#include "regression.h"


float simpLinReg(float* x, float* y, int n){
  // pass x and y arrays (pointers), lrCoef pointer, and n.  The lrCoef array is comprised of the slope=lrCoef[0] and intercept=lrCoef[1].  n is length of the x and y arrays.
  // http://en.wikipedia.org/wiki/Simple_linear_regression

  // initialize variables
	float lrCoef=0;
  float xbar=0;
  float ybar=0;
  float xybar=0;
  float xsqbar=0;
  
  // calculations required for linear regression
  for (int i=0; i<n; i++){
		if (y[i] != 0) {
			xbar=xbar+x[i];
			ybar=ybar+y[i];
			xybar=xybar+x[i]*y[i];
			xsqbar=xsqbar+x[i]*x[i];
		}
  }
  xbar=xbar/n;
  ybar=ybar/n;
  xybar=xybar/n;
  xsqbar=xsqbar/n;
  
  // simple linear regression algorithm
  lrCoef=(xybar-xbar*ybar)/(xsqbar-xbar*xbar);
	return lrCoef;
}
