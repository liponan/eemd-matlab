// eemd.cpp : 定義 DLL 應用程式的匯出函式。
//

#include <math.h>
#include <mex.h>
#include <matrix.h>
#include "emd_core.cpp"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;
void randn(double *W, int sz) {
	srand(time(NULL));
	for (int i = 0; i < sz; i++) {
		double u = (rand() *1.0) / RAND_MAX;
		double v = (rand() *1.0) / RAND_MAX; 
		W[i] = sqrt( -2 * log(u) ) * cos(2*3.1415926*v);
	}
}

double Std(double *Y, int sz) {
	double mean = 0;
	for (int i = 0; i < sz; i++)
		mean = mean + Y[i];
	mean = mean / sz;
	double sigma = 0;
	for (int i = 0; i < sz; i++)
		sigma = sigma + pow( (Y[i] - mean) , 2);
	sigma = sqrt( sigma / (sz-1) );
	if (sigma < 0.0001)
		sigma = 1;
	return sigma;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	double *Y, *modes;
	double *Ens, *Goal, *Nstd;
	int my, ny;
	int m, i, c, k;

	/* parse input arguments */
	Y  = mxGetPr(prhs[0]);
	my = mxGetM(prhs[0]);
	ny = mxGetN(prhs[0]);

	Goal  = mxGetPr(prhs[1]);
	Ens  = mxGetPr(prhs[2]);
	Nstd  = mxGetPr(prhs[3]);

	int goal = (int)*Goal;
	int goal1 = goal + 1;
	int ens = (int)*Ens;
	double nstd = *Nstd;
	int sz = my * ny;


	/* create output arguments */
	plhs[0] = mxCreateDoubleMatrix(goal+1, sz, mxREAL);
	modes = mxGetPr(plhs[0]);


	/* Core function */
	double *m1  = new double[goal1*sz];
	double *m2  = new double[goal1*sz];
	double *tmp = new double[goal1*sz];
	double *wn = new double[sz];
	double *Y1 = new double[sz];
	double *Y2 = new double[sz];
	double sigma = Std(Y, sz);
    
    
    for (i = 0; i < sz*goal1; i++)
        tmp[i] = 0;
    
	for (k = 0; k < ens; k++) {

		randn(wn, sz);

		for (i = 0; i < sz; i++) {
			Y1[i] = Y[i]/sigma + wn[i] * nstd;
			Y2[i] = Y[i]/sigma - wn[i] * nstd;
		} // end of for-i

		emd_core(m1, Y1, sz, goal); 

		if (nstd > 0) {
			emd_core(m2, Y2, sz, goal);
			for (i = 0; i < sz*goal1; i++)
				tmp[i] = tmp[i] + m1[i] + m2[i];
		} 
		else {
			for (i = 0; i < sz*goal1; i++)
				tmp[i] = tmp[i] + m1[i];
		}// end of if-else	
	} // end of for-k

	if (nstd > 0) {
		for (i = 0; i < sz*goal1; i++)
			modes[i] = tmp[i]*sigma  / (ens * 2);
	} else {
		for (i = 0; i < sz*goal1; i++)
			modes[i] = tmp[i]*sigma  / ens;
	} // end of if-else

	delete[] Y1;
	delete[] Y2;
	delete[] m1;
	delete[] m2;
	delete[] tmp;
	delete[] wn;

	}
	
