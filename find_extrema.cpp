
#include <iostream>
#include <fstream>

	using namespace std;

void find_extrema(int *Pmax, double *Vmax, int *Pmin, double *Vmin, int *Lmax, int *Lmin,
				double *Y, int sz) {
	//double *Pmax, *Pmin;
	//double *Y, *Vmax, *Vmin;
	//int m, n, *Lmax, *Lmin;
	//fstream fout("spline_log.txt", ios::out | ios::app);
	/* parse input arguments */
	//Y  = mxGetPr(prhs[0]);
	//m = mxGetM(prhs[0]);
	//n = mxGetN(prhs[0]);
	//int *Lmax = *Lmax;
	//int *Lmin = *Lmin;
	//int sz = m * n;

	/* Core function */

	// Find maximas
	//int *Pmax[sz0] = {0};
	//double *Vmax[sz0] = {0};
	Pmax[0] = 0;
	Vmax[0] = Y[0];
	*Lmax = 1;
	for (int i=1; i < sz-1; i++) {
		if ( (Y[i] > Y[i-1]) && (Y[i] > Y[i+1]) ) {
			Pmax[*Lmax] = i;
			Vmax[(*Lmax)++] = Y[i];
		}
	}
	Pmax[*Lmax] = sz-1;
	Vmax[(*Lmax)++] = Y[sz-1];

	//Additional check
	if (*Lmax > 3) {
		double m1 = (Vmax[2] - Vmax[1]) / (Pmax[2] - Pmax[1]);
		double test = Vmax[1] - m1 * (Pmax[1] - Pmax[0]);
		if (test > Vmax[0])
			Vmax[0] = test;
		double m2 = (Vmax[*Lmax-2] - Vmax[*Lmax-3]) / (Pmax[*Lmax-2] - Pmax[*Lmax-3]);
		test = Vmax[*Lmax-2] + m2 * (Pmax[*Lmax-1] - Pmax[*Lmax-2]);
		if (test > Vmax[*Lmax-1])
			Vmax[*Lmax-1] = test;
	}
	//fout << "pmax = [";
	//for (int i=0; i < *Lmax; i++)
	//	fout << Pmax[i] << " ";
	//fout << "]" << endl;
	//fout << "vmax = [";
	//for (int i=0; i < *Lmax; i++)
	//	fout << Vmax[i] << " ";
	//fout << "]" << endl;
	// Find minimas
	//int *Pmin[sz0] = {0};
	//double *Vmin[sz0] = {0};
	Pmin[0] = 0;
	Vmin[0] = Y[0];
	*Lmin = 1;
	for (int i=1; i < sz-1; i++) {
		if ( (Y[i] < Y[i-1]) && (Y[i] < Y[i+1]) ) {
			Pmin[*Lmin] = i;
			Vmin[(*Lmin)++] = Y[i];
		}
	}
	Pmin[*Lmin] = sz-1;
	Vmin[(*Lmin)++] = Y[sz-1];

	// Additional check
	if (*Lmin > 3) {
		double m1 = (Vmin[2] - Vmin[1]) / (Pmin[2] - Pmin[1]);
		double test = Vmin[1] - m1 * (Pmin[1] - Pmin[0]);
		if (test < Vmin[0])
			Vmin[0] = test;
		double m2 = (Vmin[*Lmin-2] - Vmin[*Lmin-3]) / (Pmin[*Lmin-2] - Pmin[*Lmin-3]);
		test = Vmin[*Lmin-2] + m2 * (Pmin[*Lmin-1] - Pmin[*Lmin-2]);
		if (test < Vmin[*Lmin-1])
			Vmin[*Lmin-1] = test;
	}
	//fout << "pmin = [";
	//for (int i=0; i < *Lmin; i++)
	//	fout << Pmin[i] << " ";
	//fout << "]" << endl;
	//fout << "vmin = [";
	//for (int i=0; i < *Lmin; i++)
	//	fout << Vmin[i] << " ";
	//fout << "]" << endl;

}