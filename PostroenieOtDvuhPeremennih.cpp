#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#define pi 3.14159265 
using namespace std;

double f(double X[])
{
	return pow(X[0], 2) + pow (X[1], 2);
}

int main ()
{
	int n = 3;
	double X[n-1];
	int const N = 1000;
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (X[0] = -10; X[0] < 10; X[0] = X[0] + 0.1) {
		for (X[1] = -10; X[1] < 10; X[1] = X[1] + 0.1) {
			datafile1 << X[0] << "\t" << X[1] << "\t" << f(X) << endl;
		}
	}
	datafile1.close();

	ofstream pl;
	pl.open ("plot.graph");
	pl << "set term qt" << endl;
	pl << "splot 'data1.txt' w l" << endl; 
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();
	system("gnuplot plot.graph");
}
