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
	return sin(x * x);
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
	double p;
	p = ((*pfunc)(x0 + dx) - (*pfunc)(x0 - dx))/(2 * dx);
	return p;
}

int main () {
	setlocale (0,"");
	int i, a, x0;
	double p, l;
	int const N = 1000;  
	double const pi = 3.1416; 
	double const dx = 0.001;
	
	double x1 = -pi*3;   
	double x2 = pi*3;  
	
	double X[N];  
	double Y[N];  
	double P[N];
	
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
	for (int i = 0; i < N; i++) { // ������ ������ ����� ������� �������
		X[i] = x1 + (x2 - x1)/(N-1)*i;
	}
	for (int i = 0; i < N; i++) { // ������ ������ ����� ������� �������
		Y[i] = (*pfunc)(X[i]);
	}
	cout << "�� ����� �������� ��������� �����������?" << "\n";;
	cin >> x0;
	p = gradient(pfunc, x0, dx);
	cout << p;
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (int i = 0; i < N; i++) {
		datafile1 << X[i] << "\t" << Y[i] << endl;
	}
	datafile1.close();
	
	ofstream datafile2; // ���������� � ���� �����, ��� ��������� ����� � ������� ��������� �����������
	datafile2.open ("data2.txt");
	datafile2 << x0 << "\t" << Y[x0] << endl;
	datafile2.close();
	
	ofstream pl;
	pl.open ("plot.graph");
	pl << "set term qt" << endl;
	pl << "plot 'data1.txt' with lines, 'data2.txt' with points" << endl; // ������ ����� � ���������� �� ������� �����, � ������� ��������� �����������
	pl << "set pointsize 2" << endl;
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();

	system("gnuplot plot.graph");
  
	return 0;
}
