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
/*	if (F > *Konec) //���������� ����� ������� � ����� ��������� �������� ����� � �������� ������� ���������� ������� �� ��� �����
	*Konec = F; // ����� ������� ����������� ������� ���� ��������� � 2-�� ������� ������
	if (F < *Nachalo)
	*Nachalo = F;*/
	return tanh(F);
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
		x1 = random(-10, 10); //���� ��� �� ������, �� �� ����� �������� �����, � ��� � �������� ������� ����� �������� ����� �� ����� +- 0.02
		RandomHelp = random(-100, 100); 
		x2 = random(-10, 10);
		F = net(x1, x2, X0, &Nachalo, &Konec); //���������� ������������ ������� � ���������� F
		datafile2 << x1 << "\t" << x2 << "\t" << F << "\n"; // ���������� ����� � ����
	}
	datafile2.close();
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (X0[0] = -10; X0[0] < 10; X0[0] = X0[0] + 0.5) {
			for (X0[1] = -10; X0[1] < 10; X0[1] = X0[1] + 0.5) {
				datafile1 << X0[0] << "\t" << X0[1] << "\t" << tanh(X0[0] + X0[1]) << endl;
			}
			datafile1 << endl;
	}
	datafile1.close();
	
	ofstream pl;
	pl.open ("plot.graph");
	pl << "set samples 30; set isosamples 30" << endl;
	pl << "set hidden3d" << endl;
	pl << "set pm3d" << endl;
	pl << "set surface" << endl;
	pl << "set view 50,220" << endl;
	pl << "set xrange [-2:2]" << endl;
	pl << "set yrange [-2:2]" << endl;
    pl << "splot 'data1.txt' w l ls 1, 'data2.txt' with points lw 2 lt rgb 'red'" << endl; 
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();
	system("gnuplot plot.graph");
}
