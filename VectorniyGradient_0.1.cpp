#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#define pi 3.14159265 
using namespace std;

// Тестовая функция

double f1(double X[] )
{
	// Эта функция должна выдавать в любоей точке градиент (3,2,1)
	return 3*X[0] + 2*X[1] + X[2] ;
}

double f2(double X[]) {
	// Эта функция выдает градиент такой(3*x1^2, 2*x2, 5)
	return pow(X[0],3)+pow(X[1],2)+5*X[2];
}

void gradient (double(*pfunc)(double[]), double X0 [], double Xout[], int n, double dx)
{	
	int i, j;
	double X1[n-1];
	double X2[n-1];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			X1[j] = X0[j];   //Здесь вместо i нужно поставить j, потому что мы инициируем весь вектор
			X2[j] = X0[j];
		}
		X1[i] = X0[i] + dx;
		X2[i] = X0[i] - dx;
		Xout[i] = (pfunc(X1) - pfunc(X2)) / (2 * dx);   // Аргументом функции является весь вектор, а не последнее значения, как было у тебя pfunc(x1[n-1])
	}
}
int main ()
{
	int i, n; //n - кол-во измерений
	double const dx = 0.001; //шаг
	/* double(*pfunc)(double); // Объявляем указатель
	Используем конкретную функцию
	*/
	n = 3;
	double X0[n-1];
	double Xout[n-1];
	cout << "Enter 3 coorinates of the vector \n";
	for (i = 0; i < n; i++) {
		cin >> X0[i];
	}
	cout << " Gradient of the function 1 is (";
	// вычисляем градиент от функции f1
	gradient (f1, X0, Xout, n, dx);
	for (i = 0; i < n; i++) {
		cout << Xout[i] << ",";
	}
	cout << "\b) \n";
	
	cout << " Gradient of the function 2 is (";
		// вычисляем градиент от функции f2
	gradient (f2, X0, Xout, n, dx);
	for (i = 0; i < n; i++) {
		cout << Xout[i] << ",";
	}
	cout << "\b) \n";
}


