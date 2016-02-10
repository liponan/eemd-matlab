// requires GNU Scientific Lib
// v0.3 @ 2014/11/12

#include <gsl/gsl_spline.h>

void spline(double *YY, 
		int *X, double *Y, int m1, int m2) {

	// m1: length of discrete extremas
	// m2: length of original data points

	gsl_interp_accel *acc = gsl_interp_accel_alloc ();
  	//const gsl_interp_type *t = gsl_interp_cspline; 
  	gsl_spline *spline = NULL;

	/* Core function */
  	double *xd = new double[m1];
  	for (int j = 0; j < m1; j++)
  		xd[j] = (int)X[j];


	double m; // slope for linear interpolation
	
	if (m1 > 2 ) { // use spline
		spline = gsl_spline_alloc (gsl_interp_cspline, m1);
		gsl_spline_init (spline, xd, Y, m1);
		for (int j = 0; j < m2; j++) {
			YY[j] = gsl_spline_eval (spline, j, acc);
		} // end of for-j
	} // end of if
	else {
		m = (Y[1] - Y[0]) / (m2 - 1);
		for (int j = 0; j < m2; j++) {
			YY[j] = Y[0] + m * j;
		} // end of for-j		
	} //end of else

	delete[] xd;
	gsl_spline_free (spline);
	gsl_interp_accel_free (acc);
}
