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
void gradient (double X0 [], double Xout[], int n, double dx)
{	
	int i, j;
	double X1[n-1];
	double X2[n-1];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			X1[j] = X0[j];
			X2[j] = X0[j];
		}
		X1[i] = X0[i] + dx;
		X2[i] = X0[i] - dx;
		Xout[i] = (f(X1) - f(X2)) / (2 * dx); 
	}
}
void spusk (double X0 [], double Xout[], int n, double dx, int* shagi)
{
	setlocale (0,"");
	double x1, x2, epsilon, A, c = 0; //x1, x2 - ���������� ������, epsilon - ���������� ����������� ����������, � - ���� ������, c - �������
	epsilon = 5 * dx;
	cout << "������� ���������� x1 � x2 � ������� ����� ���������� ����� \n";
	cin >> x1 >> x2;
	double X1[n-1]; // ������� ������ ������
	X1[0] = x1; //��������� ���
	X1[1] = x2;
	X1[2] = f(X1);
	gradient (X1, Xout, n, dx); //���� ��������
	cout << "������� ���������� ������ �, �� ���� ��� � ������, ��� ������ ��� \n";
	cin >> A;
	ofstream datafile2; // ���������� � ���� �����, �� ������� ����������
	datafile2.open ("data2.txt");
	while (1) {
		datafile2 << x1 << "\t" << x2 << "\t" << f(X1) << "\n"; //���������� � ���� ����� ��������
		c++;
		x1 = x1 - A * Xout[0]; //������
		x2 = x2 - A * Xout[1];
		X1[0] = x1; // ��������� ������ *������* ��� ������ ����������
		X1[1] = x2;
		X1[2] = f(X1);
		gradient (X1, Xout, n, dx);
		if (Xout[0] < epsilon && Xout[1] < epsilon && Xout[0] > -epsilon && Xout[1] > -epsilon) {
			Xout[0] = x1; // ��������� ������ *������* ��� ������ ����������
			Xout[1] = x2;
			Xout[2] = f(Xout);
			*shagi = c; //�������� � ��������� �� �������� ���������� ���-�� �����
			break;
		}
	}
	datafile2.close();
}
int main ()
{
	setlocale (0,"");
	int i, n = 3, b = 1, shagi = 0;
	double const dx = 0.001;
	double X0[n-1];
	double Xout[n-1];
	
	while (b == 1) {
		spusk (X0, Xout, n, dx, &shagi);
		
		cout << "���������� ����������� - ";
		for (i = 0; i < n; i++) {
			cout << Xout[i] << "\t";
		}
		cout << endl << "���������� ����� - " << shagi << endl;
		ofstream datafile1;
		datafile1.open ("data1.txt");
		for (X0[0] = -10; X0[0] < 10; X0[0] = X0[0] + 0.1) {
			for (X0[1] = -10; X0[1] < 10; X0[1] = X0[1] + 0.1) {
				datafile1 << X0[0] << "\t" << X0[1] << "\t" << f(X0) << endl;
			}
			datafile1 << endl;
		}
		datafile1.close();
	
		ofstream pl;
		pl.open ("plot.graph");
		pl << "set term qt" << endl;
		pl << "splot 'data1.txt' w l, 'data2.txt' with points lw 2 lt rgb 'red'" << endl; 
		pl << "pause mouse button1,keypress"<< endl; 
		pl.close();
		cout << "�������� Gnuplot ����� ��������� ������� ��� ����������� � ������." << "\n";
		system("gnuplot plot.graph");
		cout << "0 - �����, 1 - ���������� ������." << "\n";
		cin >> b; // ��� b = 0 ������ �����������
	}
}
