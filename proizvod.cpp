#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int x (float X[], float x1, float x2, int N)
{
	int i;
	for (int i = 0; i < N; i++) {
		X[i] = x1 + (x2 - x1)/(N-1)*i;
	}
}

int y (float Y[], int N, float X[])
{
	int i;
	for (int i = 0; i < N; i++) {
		Y[i] = sin(X[i]);
	}
}

int p (float P[], int N, float dx, float X[])
{
	int i;
	for (int i = 0; i < N; i++) {	
		P[i] = (sin(X[i] + dx) - sin(X[i] - dx))/(2 * dx);
	}
}

int main () {
	int i;
	int const N = 1000;  
	float const pi = 3.1416; 
	float const dx = 0.001;
	
	float x1 = -pi*3;   
	float x2 = pi*3;  
	
	float X[N];  
	float Y[N];  
	float P[N];
	
	x(X, x1, x2, N);
	y(Y, N, X);
	p(P, N, dx, X);

	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (int i = 0; i < N; i++) {
	datafile1 << X[i] << '\t' << Y[i] << endl;
	}
	datafile1.close();
	
	ofstream datafile2;
	datafile2.open ("data2.txt");
	for (int i = 0; i < N; i++) {
    datafile2 << X[i] << '\t' << P[i] << endl;
	}
	datafile2.close();

  ofstream pl;
  pl.open ("plot.graph");
  pl << "set term qt" << endl;
  pl << "plot 'data1.txt' w l, 'data2.txt' w l" << endl; 
  pl << "pause mouse button1,keypress"<< endl; 
  pl.close();

  system("gnuplot plot.graph");
  
  return 0;
}
