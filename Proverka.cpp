#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
using namespace std;

double f1 (double x)
{
	return sin(x);
}

double f2 (double x)
{
	return sin(2 * x);
}

double f3 (double x)
{
	return cos(x) * x;
}

double f4 (double x)
{
	return x * x;
}

double f5 (double x)
{
	return x * x * x;
}

double gradient (double(*pfunc)(double), double x0, double dx)
{
	return ((*pfunc)(x0 + dx) - (*pfunc)(x0 - dx))/(2 * dx);
}

int main () {
	setlocale (0,"");
	int i, a, x0;
	double p, l;
	int const N = 1000;
	double const pi = 3.1416; 
	double const dx = 0.001;
	
	double x1;   
	double x2; 
	cout << "��������� ������� ������� x1 � x2" << "\n" << "x1 = ";
	cin >> x1;
	x1 = 0;
	cout << "x2 = ";
	cin >> x2;
	x2 = pi;
	
	double X[N];
	double Y[N];
	double P[N];
	cout << "1.y=sin(x) 2.y=sin(2x) 3.y=x*cos(x) 4.y=x^2 5.y=x^3" << "\n";
	cout << "�������� �������." << "\n";
	cin >> a;
	double(*pfunc)(double); // ��������� ���������
	if (a == 1)  // ������� � ����� ������ �������� �
		pfunc = f1;
	if (a == 2) 
		pfunc = f2;
	if (a == 3)
		pfunc = f3;
	if (a == 4) 
		pfunc = f4;
	if (a == 5)
		pfunc = f5;
	for (i = 0; i < N; i++) { // ������ ������ ����� ������� �������
		X[i] = x1 + (x2 - x1)/(N-1)*i;
	}
	cout << (*pfunc)(X[1]);
	cout << ((*pfunc)(X[1] + dx) - (*pfunc)(X[1] - dx))/(2 * dx);
	
	for (i = 0; i < N; i++) { // ������ ������ ����� ������� ������� � ������� �����������
		Y[i] = (*pfunc)(X[i]);
		P[i] = ((*pfunc)(X[i] + dx) - (*pfunc)(X[i] - dx))/(2 * dx);
	}
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (i = 0; i < N; i++) {
		datafile1 << X[i] << "\t" << Y[i] << endl;
	}
	datafile1.close();
	
	ofstream datafile2; // ���������� � ���� �����, ��� ��������� ����� � ������� ��������� �����������
	datafile2.open ("data2.txt");
	for (i = 0; i < N; i++) {
		datafile2 << X[i] << "\t" << P[i] << "\n";
	}
	datafile2.close();
	
	ofstream pl;
	pl.open ("plot.graph");
	pl << "set term qt" << endl;
	pl << "plot 'data1.txt' w l, 'data2.txt' w l" << endl; // ������ ����� � ���������� �� ������� �����, � ������� ��������� �����������
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();

	system("gnuplot plot.graph");
  
	return 0;
}
