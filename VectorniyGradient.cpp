#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#define pi 3.14159265 
using namespace std;
void gradient (double(*pfunc)(double), double X0 [], double Xout[], int n, double dx)
{	
	int i;
	for (i = 0; i < n; i++) {
		Xout[i] = (pfunc(X0[i] + dx) - pfunc(X0[i] - dx)) / 2 * dx;
	}
}
int main ()
{
	int i, n; //n - кол-во измерений
	double const dx = 0.001; //шаг
	double(*pfunc)(double); // ќбъ€вл€ем указатель
	n = 3;
	double X0[n-1];
	double Xout[n-1];
	for (i = 0; i < n; i++) {
		cin >> X0[i];
	}
	gradient (pfunc, X0, Xout, n, dx);
	for (i = 0; i < n; i++) {
		cout << Xout[i] << "\n";
	}
}


