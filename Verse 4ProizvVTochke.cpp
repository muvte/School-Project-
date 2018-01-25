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

int main () {
	setlocale (0,"");
	int i, a, j;
	double p, l;
	int const N = 1000;  
	double const pi = 3.1416; 
	double const dx = 0.001;
	
	double x1 = -pi*3;   
	double x2 = pi*3;  
	
	double X[N];  
	double Y[N];  
	double P[N];
	
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
	for (int i = 0; i < N; i++) { // Строим массив точек ординат функции
		Y[i] = (*pfunc)(X[i]);
	}
	cout << "На какой абсциссе посчитать производную?" << "\n";;
	cin >> j;
	p = ((*pfunc)(X[j] + dx) - (*pfunc)(X[j] - dx))/(2 * dx); // Находим производную
	cout << p;
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (int i = 0; i < N; i++) {
		datafile1 << X[i] << "\t" << Y[i] << endl;
	}
	datafile1.close();
	
	ofstream datafile2; // Записываем в файл точку, для выделения места в котором вычислили производную
	datafile2.open ("data2.txt");
	datafile2 << j << "\t" << Y[j] << endl;
	datafile2.close();
	
	ofstream pl;
	pl.open ("plot.graph");
	pl << "set term qt" << endl;
	pl << "plot 'data1.txt' with lines, 'data2.txt' 1:2 with points" << endl; // Строим грфик и отображаем на графике точку, в которой вычислили производную
	pl << "set pointsize 2" << endl;
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();

	system("gnuplot plot.graph");
  
	return 0;
}
