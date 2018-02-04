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
	cout << "1.y=sin(x) 2.y=sin(2x) 3.y=x*cos(x) 4.y=x^2 5.y=x^3" << "\n";
	cout << "Выберите функцию." << "\n";
	cin >> a;
	double(*pfunc)(double); // Объявляем указатель
	if (a == 1)  // Смотрим к какой фукции подходит а
		pfunc = f1;
	if (a == 2) 
		pfunc = f2;
	if (a == 3)
		pfunc = f3;
	if (a == 4) 
		pfunc = f4;
	if (a == 5)
		pfunc = f5;
	for (int i = 0; i < N; i++) { // Строим массив точек абсцисс функции
		X[i] = x1 + (x2 - x1)/(N-1)*i;
	}
	for (int i = 0; i < N; i++) { // Строим массив точек ординат функции и ординат производной
		Y[i] = (*pfunc)(X[i]);
<<<<<<< HEAD
		P[i] = gradient(pfunc, x0, dx);
=======
		P[i] = 
		
>>>>>>> 919a551ba5f3eb725372286be12c11b9691b0268
	}
	
	cout << "На какой абсциссе посчитать производную?" << "\n";;
	cin >> x0;
	p = gradient(pfunc, x0, dx);
	cout << p;
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (i = 0; i < N; i++) {
		datafile1 << X[i] << "\t" << Y[i] << endl;
	}
	datafile1.close();
	
	ofstream datafile2; // Записываем в файл точку, для выделения места в котором вычислили производную
	datafile2.open ("data2.txt");
	for (i = 0; i < N; i++) {
		datafile2 << X[i] << "\t" << Y[i] << "\n";
	}
	datafile2.close();
	
	ofstream pl;
	pl.open ("plot.graph");
	pl << "set term qt" << endl;
	pl << "plot 'data1.txt' w l, 'data2.txt' w l" << endl; // Строим грфик и отображаем на графике точку, в которой вычислили производную
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();

	system("gnuplot plot.graph");
  
	return 0;
}
