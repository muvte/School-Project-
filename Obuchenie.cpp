#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>
using namespace std;

double random(double min, double max) //Создаем функцию рандома от min до max
{
    return (double)(rand())/RAND_MAX*(max - min) + min;
}
double net (double x1, double x2, double X0[]) // Создаем указатель и работаем с ним, чтобы после функции return F; все изменения с этой переменной не стерлись
{
	setlocale(0,"");
	double F; //Аргумент будущей точки
	double w1 = X0[0]; //Присваиваем знаечения вектора старта весовым коэфициентам и смещению
	double w2 = X0[1];
	double b = X0[2];
	F = b + w1 * x1 + w2 * x2; //Подсчет аргумента точки
	return tanh(F);
}
double errors (double X0[]) {
	double s = 0;
	int i;
	for (i = 0; i < 2 * ns; i++) {
		s = s + pow(y[i] - net(sx1[i],sx2[i],X0),2);
	}
	return s;
}
f (double X0[])
{
	return errors(X0, sx1, sx2, y, ns);
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
	double x1, x2, epsilon, c = 0, R = 10; 
	epsilon = 5 * dx;

	double gr[n];
	double step[n]; 
	double y;
	
	for (int i = 0; i < n; i++) {
		Xout[i] = X0[i];
	}

	ofstream datafile2; 
	datafile2.open ("data2.txt");
        
	while (1) {
	    if (norm(Xout,n) < R) {
			for (int i = 0; i < n; i++) {
				datafile2 << Xout[i] << "\t";
			}
			datafile2 << f(Xout) << "\n";
			c++;
			gradient (Xout, gr, n, dx); 
			for (int i = 0; i < n; i++) {
				step[i] = - A * gr[i];
			}
			for (int i = 0; i < n; i++) {
				Xout[i] = Xout[i] + step[i];
			}
			if (norm(step,n) < epsilon) {
				*shagi = c; 
				break;
			}
	    } else {   
	    	cout << "Error Out of limits";
	    	break;
	    }
	}
	datafile2.close();
}
int main ()
{
	int ns = 5;
	double sx1[2*ns], sx2[2*ns], y[2*ns]; //Массивы координат двух групп точек 
	double r = 1, one1 = 1, one2 = 5, two1 = 5, two2 = 1;
	
	int i, N = 10000, n = 3, Ntochek = 10; // i- счетчик, N - кол-во точек функции, n - кол-во измерений, Ntochek - кол-во рандомных точек на графике.
	double X0[n];
	double x1, x2, RandomHelp, b, w1, w2, F;
	
	srand (time(0));
	RandomHelp = random(-100, 100); // Описание ниже. Строка 55
	X0[0] = random(-5, 5); //Рандомизируем 
	RandomHelp = random(-100, 100);
	X0[1] = random(-5, 5);
	RandomHelp = random(-100, 100);
	X0[2] = random(-5, 5);
	cout << "w1 - " << X0[0] << "\nw2 - " << X0[1] << "\nb - " << X0[2] << endl; 
	
// samples
// The first group
	for (i = 0; i < ns; i++) {
		RandomHelp = random(-100, 100);
		sx1[i] = one1 + random(-1, 1)  *r; //Задаем координаты точкам группы 1
		RandomHelp = random(-100, 100);
		sx2[i] = one2 + random(-1, 1)  *r;
		y[i] = 1;
	}
	
	// The second group
	for (i = ns; i < 2 * ns; i++) {
		RandomHelp = random(-100, 100);
		sx1[i] = two1 + random(-1, 1) * r; //Задаем координаты точкам группы 2
		RandomHelp = random(-100, 100);
		sx2[i] = two2 + random(-1, 1)  *r;
		y[i] = -1;
	}
	
	ofstream datafile2;
	datafile2.open ("data2.txt");
	for (i = 0; i < 2 * ns; i++) {
		datafile2 << sx1[i] << "\t" << sx2[i] << "\t" << y[i] << "\n"; // Записываем точки в файл
	}
	datafile2.close();
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (x1 = -10; x1 < 10; x1 = x1 + 0.5) {
			for (x2 = -10; x2 < 10; x2 = x2 + 0.5) {
				datafile1 << x1 << "\t" << x2 << "\t" << net(x1, x2, X0) << endl;
			}
			datafile1 << endl;
	}
	datafile1.close();
	
	ofstream pl;
	pl.open ("plot.graph");
    pl << "splot 'data1.txt' w l ls 1, 'data2.txt' with points lw 2 lt rgb 'red'" << endl; 
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();
	system("gnuplot plot.graph");
	
	cout << "Совершаем обучение нейронной сети";
	spusk (X0, Xout, n, dx, *shagi)
	cout << "Точка экстремума - ";
	for (i = 0; i < n; i++) {
		cout << Xout[i] << "\t";
	}
	cout << "\n" << "Найден за " << shagi << " количество шагов" << "\n"
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (x1 = -10; x1 < 10; x1 = x1 + 0.5) {
			for (x2 = -10; x2 < 10; x2 = x2 + 0.5) {
				datafile1 << x1 << "\t" << x2 << "\t" << net(x1, x2, Xout) << endl;
			}
			datafile1 << endl;
	}
	datafile1.close();
	
	ofstream pl1;
	pl.open ("plot.graph");
    pl << "splot 'data1.txt' w l ls 1, 'data2.txt' with points lw 2 lt rgb 'red'" << endl; 
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();
	system("gnuplot plot.graph");
}

