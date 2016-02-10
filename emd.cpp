#include <mex.h>
#include <matrix.h>
#include "emd_core.cpp"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	double *modes;
	double *X, *Y;
	double *G;
	
	int m1, n1;
	int m2, n2;
	int goal = 0;

	/* parse input arguments */
	X  = mxGetPr(prhs[0]);
	m1 = mxGetM(prhs[0]);
	n1 = mxGetN(prhs[0]);
	int l1 = m1 * n1;

	G  = mxGetPr(prhs[1]);
	m2 = mxGetM(prhs[1]);
	n2 = mxGetN(prhs[1]);
	int l2 = m2 * n2;

	goal = (int)G[0];

	int l3 = l1*(goal+1);

	/* initialize arrays */
	modes = new double[ l3 ]; // output buffer
	
	/* create output arguments */
	plhs[0] = mxCreateDoubleMatrix(goal+1, l1, mxREAL);
	Y = mxGetPr(plhs[0]);

	/* call core function */
	emd_core(modes, 
		X, l1, goal);

	for(int i = 0; i < l1; i++) {
		for(int j=0; j <= goal; j++) {
			Y[j + i*(goal+1)] = modes[i + j*l1];	
		}
	}
}