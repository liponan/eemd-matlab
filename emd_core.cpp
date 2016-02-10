// emd_core.cpp : 定義 DLL 應用程式的匯出函式。
//
/*


*/

#include <iostream>
#include <fstream>
#include <math.h>
#include "find_extrema.cpp"
//#include "spline_alglib.cpp"
#include "spline_gsl.cpp"

	using namespace std;

void mean(double *mean, double *y1, double *y2, int sz) {
	for (int i = 0; i < sz; i++)
		mean[i] = (y1[i] + y2[i]) / 2;
}

void emd_core(double *modes, 
		double *Y, int sz, int goal) {
	int m, i, c;
	int MAX = sz;

	int goal1 = goal + 1;

	//fstream fout("spline_log.txt", ios::out | ios::app);

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


	for (i = 0; i < sz; i++)
		emean[i] = 0;

	// r = Y
	for(i = 0; i < sz; i++)
		r[i] = Y[i];
	// for each mode
	for (m = 0; m < goal; m++) {
			// h = r
			//fout << " @ mode " << m+1 <<"  h = [";
			for (i = 0; i < sz; i++) {
				h[i] = r[i];
				//fout << h[i] << " ";
			}
			//fout << "];" << endl;
			// solving mode
			for (c = 0; c < itr; c++) {
				//fout << "@itr #" << c+1 << endl;
				//cout << "finding extrema..." << endl;
				find_extrema(pmax, vmax, pmin, vmin, &lmax, &lmin, h, sz);
				//cout << "finding upper envelope..." << endl;
				spline(upper, pmax, vmax, lmax, sz);
				//cout << "finding lower envelope..." << endl;
				spline(lower, pmin, vmin, lmin, sz);
				//cout << "finding mean..." << endl;
				mean(emean, upper, lower, sz);
				for (i = 0; i < sz; i++) {
					if (emean[i] > 1000 || emean[i] < -1000)
						cout<< "Warning! Abnormal EMEAN value " << emean[i] 
							<< " at position " << i << " after " << c << " iterations..." << endl;
				}
				// h = h - meana
				for (i = 0; i < sz; i++)
					h[i] = h[i] - emean[i];
				for (i = 0; i < sz; i++) {
					if (h[i] > 1000 || h[i] < -1000)
						cout<< "Warning! Abnormal H value " << emean[i] 
							<< " at position " << i << " after " << c << " iterations..." << endl;
				}
			} // end of for-c
			// r = r -h
			for (i = 0; i < sz; i++) {
				r[i] = r[i] - h[i];
				modes[i + m*sz] = h[i];
			} // end of for-i

	} // end of for-m
	for (i = 0; i < sz; i++) // save trend
		modes[i + goal*sz] = r[i];
    
	delete [] vmax;
	delete [] pmax;
	delete [] vmin;
	delete [] pmin;
	delete [] upper;
	delete [] lower;
	delete [] emean;
	delete [] h;
	delete [] r;

	}
	
