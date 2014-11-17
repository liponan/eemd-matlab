// spline.cpp : 定義 DLL 應用程式的匯出函式。
//

#include "spline.hpp"


void spline(double *YY, 
		int *X, double *Y, int m1, int m2) {

	// m1: length of discrete extremas
	// m2: length of original data points

	/* Core function */
	using namespace magnet::math;

	Spline spline;
	double m;
	
	if (m1 > 2 ) {

		for (int i = 0; i < m1; i++) {
			spline.addPoint(X[i],Y[i]);
		} // end of for-i

		for (int j = 0; j < m2; j++) {
			YY[j] = spline(j);
		} // end of for-j

	} // end of if

	else {

		m = (Y[1] - Y[0]) / (m2 - 1);

		for (int j = 0; j < m2; j++) {
			YY[j] = Y[0] + m * j;		
		} // end of for-j
		
	} //end of else

}
