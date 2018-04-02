#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#define pi 3.14159265 
using namespace std;

double f(double X[])
{
//	return cos(X[0]) * sin( X[1] / (pow(X[1],2) + pow(X[0],2)));
return X[0]*X[0] + pow(X[1]-3,2);
}

double norm(double X[], int n) {
	double s = 0;
	for (int i = 0; i < n; i++) {
		s = s + X[i] * X[i];
	}
	return sqrt(s);
}

void gradient (double X0 [], double Xout[], int n, double dx)
{	
	int i, j;
	double X1[n];
	double X2[n];
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
void spusk (double X0 [], double Xout[], int n, double dx, double A, int* shagi)
{
	setlocale (0,"");
	double x1, x2, epsilon, c = 0, R = 10; //x1, x2 - ���������� ������, epsilon - ���������� ����������� ����������, � - ���� ������, c - �������, R - ?????? ?????? ???????????
	epsilon = 5 * dx;

	double gr[n]; // ������� ������ ������
	double step[n]; // ��� 
	double y;
	
	for (int i = 0; i < n; i++) {
		Xout[i] = X0[i];
	}

	ofstream datafile2; // ���������� � ���� �����, �� ������� ����������
	datafile2.open ("data2.txt");
        
	while (1) {
                if (norm(Xout,n) < R) {
		        for (int i = 0; i < n; i++) {
		        	datafile2 << Xout[i] << "\t";
				}
				datafile2 << "\n";
		        c++;
		        gradient (Xout, gr, n, dx); //���� ��������
		        for (int i = 0; i < n; i++) {
		        	step[i] = - A * gr[i];
				}
		        
		        for (int i = 0; i < n; i++) {
		        	Xout[i] = Xout[i] + step[i];
				}
		        
		        if (norm(step,n) < epsilon) {
			        *shagi = c; //�������� � ��������� �� �������� ���������� ���-�� �����
			        break;
		        }
                } else {
                	// ����� �� �������
                	cout << "Error Out of limits";
                        break;
                }
	}
	datafile2.close();
}
int main ()
{
	setlocale (0,"");
	int i, n = 2, b = 1, shagi = 0;
	double const dx = 0.001;
	double A = 0.1;
	double X0[n];
	X0[0] = 2;
	X0[1] = 4;
	double Xout[n];
	
		spusk (X0, Xout, n, dx, A, &shagi);
		
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
		system("gnuplot plot.graph");
		cin >> b; // ��� b = 0 ������ �����������
}
