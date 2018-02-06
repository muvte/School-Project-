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
	return ((*pfunc)(x0 + dx) - (*pfunc)(x0 - dx))/(2 * dx); //�������������� ���������������� tg a 
}

double spusk (double(*pfunc)(double), double x0, double dx, double A)
{
	double h, epsilon; // h - ���, epsilon - ���������� ����������� ������ �����������
	int naprav; // naprav - ��� ����� ������ min/max
	ofstream datafile2; // ���������� � ���� �����, �� ������� ����������
	datafile2.open ("data2.txt");
	h = 1; //������ ����� ���, ����� � ��� �� ����� �����
	epsilon = 5 * dx;
	cout << "�������� ����� (1) ��� ������ (2)" << "\n";
	cin >> naprav;
	while (1) {
		datafile2 << x0 << "\t" << (*pfunc)(x0) << "\n"; //���������� � ���� ����� ��������
		if (naprav == 1) {
			h = - (gradient (*pfunc, x0, dx)) * A; 
		} else {
			h = (gradient (*pfunc, x0, dx)) * A;
		}
		x0 = x0 + h;
		if (h < epsilon && h > -epsilon) { //���� ��� �� ���������� (-epsilon,epsilon), �� �� ��������� � ����������� �� ����� �����������
			return x0;
		}
	}
	datafile2.close();
}

int main () {
	setlocale (0,"");
	int i, a, b; // i - �������, a - ����� �������, b - ���� ����������� ������
	double x0, xGrad, A; // x0 - ����� ������, xGrad - ����� �������� ���������, A - ���������� ������
	int const N = 1000; // ���-�� ����� �������
	double const dx = 0.001; //���
	b = 1; // ������ ���������� �������� ��� ������������ ���������
	while (b == 1) {
		double x1;   
		double x2; 
		cout << "��������� ������� ������� x1 � x2" << "\n" << "x1 = ";
		cin >> x1;
		cout << "x2 = ";
		cin >> x2;
		
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
		for (i = 0; i < N; i++) { // ������ ������ ����� ������� �������
			Y[i] = (*pfunc)(X[i]);
		}
		cout << "������� ���������� ������ �, �� ���� ��� � ������, ��� ������ ���" << "\n";
		cin >> A;
		cout << "������� �������� �����, � ������� ����� ���������� ��������" << "\n";
		cin >> x0;
		xGrad = spusk(*pfunc, x0, dx, A); //����� � xGrad �������� ����� �����������
		cout << "������� ��������� = " << xGrad << "\n";
		
		ofstream datafile1;
		datafile1.open ("data1.txt");
		for (i = 0; i < N; i++) {
			datafile1 << X[i] << "\t" << Y[i] << endl;
		}
		datafile1.close();
		
		ofstream pl;
		pl.open ("plot.graph");
		pl << "set term qt" << endl;
		pl << "plot 'data1.txt' w l, 'data2.txt' using 1:2 with points lw 2 lt rgb 'red'" << endl; // ������ ����� � ���������� �� ������� �����, � ������� ��������� �����������
		pl << "pause mouse button1,keypress"<< endl; 
		pl.close();
		cout << "�������� Gnuplot ����� ��������� ������� ��� ����������� � ������." << "\n";
		system("gnuplot plot.graph");
		
		cout << "0 - �����, 1 - ���������� ������." << "\n";
		cin >> b; // ��� b = 0 ������ �����������
	}
	return 0;
}
