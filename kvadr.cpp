#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int const N = 1000;  
float const pi = 3.1416; 

float x1 = -pi*3;   
float x2 = pi*3;  

float X[N];  
float Y[N];  

int main () {

	for (int i = 0; i < N; i++) {
		X[i] = x1 + (x2 - x1)/(N-1)*i;
	}

	for (int i = 0; i < N; i++) {
		Y[i] = 1/(1 + X[i] * X[i]);
	}

  ofstream datafile;
  datafile.open ("data.txt");
  for (int i = 0; i < N; i++) {
    datafile << X[i] << '\t' << Y[i] << endl;
  }
  datafile.close();

  ofstream pl;
  pl.open ("plot.graph");
  pl << "set term qt" << endl;
  pl << "plot 'data.txt' w l " << endl; 
  pl << "pause mouse button1,keypress"<< endl; 
  pl.close();

  system("gnuplot plot.graph");
  
  return 0;
}
