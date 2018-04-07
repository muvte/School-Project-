#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>
using namespace std;
double random(double min, double max) //������� ������� ������� �� min �� max
{
    return (double)(rand())/RAND_MAX*(max - min) + min;
}
double net (double x1, double x2, double X0[], double* Nachalo, double* Konec) // ������� ��������� � �������� � ���, ����� ����� ������� return F; ��� ��������� � ���� ���������� �� ��������
{
	setlocale(0,"");
	double F; //�������� ������� �����
	double w1 = X0[0]; //����������� ��������� ������� ������ ������� ������������ � ��������
	double w2 = X0[1];
	double b = X0[2];
	F = b + w1 * x1 + w2 * x2; //������� ��������� �����
	if (F > *Konec) //���������� ����� ������� � ����� ��������� �������� ����� � �������� ������� �����\������ ������� �� ��� �����
	*Konec = F; // ����� ������� ����������� ������� ���� ��������� � 2-�� ������� ������
	if (F < *Nachalo)
	*Nachalo = F;
	return F;
}
int main ()
{	
	int i, N = 1000, n = 3, Ntochek = 100; // i- �������, N - ���-�� ����� �������, n - ���-�� ���������, Ntochek - ���-�� ��������� ����� �� �������.
	double X[N];
	double Y[N];
	double X0[n];
	double x1, x2, RandomHelp, b, w1, w2, Nachalo, Konec, F;
	Nachalo = -2;
	Konec = 2;
	
	srand (time(0));
	RandomHelp = random(-100, 100); // �������� ����. ������ 55
	X0[0] = random(-5, 5); //������������� 
	RandomHelp = random(-100, 100);
	X0[1] = random(-5, 5);
	RandomHelp = random(-100, 100);
	X0[2] = random(-5, 5);
	cout << "w1 - " << X0[0] << "\nw2 - " << X0[1] << "\nb - " << X0[2] << endl; 
	
	ofstream datafile2;
	datafile2.open ("data2.txt");
	for (i = 0; i < Ntochek; i++) {
		RandomHelp = random(-100, 100); //������������� �������� ��� ���������� (RandomHelp), ����� srand time ���-�� ���������� � ��� ������������� ������
		x1 = random(-50, 51); //���� ��� �� ������, �� �� ����� �������� �����, � ��� � �������� ������� ����� �������� ����� �� ����� +- 0.02
		RandomHelp = random(-100, 100); 
		x2 = random(-50, 51);
		F = net(x1, x2, X0, &Nachalo, &Konec); //���������� ������������ ������� � ���������� F
		datafile2 << F << "\t" << tanh(F) << "\n"; // ���������� ����� � ����
	}
	datafile2.close();
	
	for (i = 0; i < N; i++) { // ������ ������ ����� ������� �������
		X[i] = Nachalo + (Konec - Nachalo)/(N-1)*i;
	}
	
	for (i = 0; i < N; i++) { // ������ ������ ����� ������� �������
		Y[i] = tanh (X[i]);		
	}
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (i = 0; i < N; i++) {
		datafile1 << X[i] << "\t" << Y[i] << endl;
	}
	datafile1.close();
	
	ofstream pl;
	pl.open ("plot.graph");
	pl << "set term qt" << endl;
	pl << "set linestyle 1 lt 1 lw 3" << endl; //������ ����� ��� ��������. �����������- ������� ����� lw3;
    pl << "plot 'data1.txt' w l ls 1, 'data2.txt' with points lw 2 lt rgb 'red'" << endl; 
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();
	system("gnuplot plot.graph");
}
