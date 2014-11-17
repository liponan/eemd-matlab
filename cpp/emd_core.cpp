// emd_core.cpp : 定義 DLL 應用程式的匯出函式。
//

#include <math.h>
#include <mex.h>
#include <matrix.h>
#include "find_extrema.cpp"
#include "spline.cpp"

void mean(double *mean, double *y1, double *y2, int sz) {
	for (int i = 0; i < sz; i++)
		mean[i] = (y1[i] + y2[i]) / 2;
}

void emd_core(double *modes, 
		double *Y, int sz, int goal) {
	int my, ny;
	int m, i, c;
	int MAX = sz;

	int goal1 = goal + 1;

	/* Core function */

	// variables for find_extrema
	double *vmax = new double[MAX];
	double *vmin = new double[MAX];
	int *pmax = new int[MAX];
	int *pmin = new int[MAX];
	int lmax = 0, lmin = 0;
	// variables for spline
	double *upper = new double[MAX];
	double *lower = new double[MAX];
	double *emean = new double[MAX];
	int itr = (int)ceil(pow(sz, 0.5));
	double *h = new double[MAX];
	double *r = new double[MAX];
	// r = Y
	for(i = 0; i < sz; i++)
		r[i] = Y[i];

	// for each mode
	for (m = 0; m < goal; m++) {

			for (i = 0; i < sz; i++) {
				h[i] = r[i];
			}

			// solving mode
			for (c = 0; c < itr; c++) {
				find_extrema(pmax, vmax, pmin, vmin, &lmax, &lmin, h, sz);
				spline(upper, pmax, vmax, lmax, sz);
				spline(lower, pmin, vmin, lmin, sz);
				mean(emean, upper, lower, sz);

				// h = h - mean
				for (i = 0; i < sz; i++)
					h[i] = h[i] - emean[i];
			} // end of for-c

			// r = r -h
			for (i = 0; i < sz; i++) {
				r[i] = r[i] - h[i];
				modes[goal1*i + m] = h[i];
			} // end of for-i
	} // end of for-m

	// save trend
	for (i = 0; i < sz; i++) {
		modes[goal1*i + goal] = r[i];
	} // end of for-i

	delete[] pmax;
	delete[] vmax;
	delete[] pmin;
	delete[] vmin;
	delete[] upper;
	delete[] lower;
	delete[] emean;
	delete[] h;
	delete[] r;
}
	
