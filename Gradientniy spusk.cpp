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
	return cos(x) * x
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
	return ((*pfunc)(x0 + dx) - (*pfunc)(x0 - dx))/(2 * dx); //Геометрический смыслпроизводной tg a 
}

double spusk (double(*pfunc)(double), double x0, double dx, double A)
{
	double h, epsilon; // h - шаг, epsilon - допустимая погрешность поиска экстремумма
	int naprav; // naprav - Что будем искать min/max
	ofstream datafile2; // Записываем в файл точки, по которым спускались
	datafile2.open ("data2.txt");
	h = 1; //Вводим любой шаг, чтобы в нем не лежал мусор
	epsilon = 5 * dx;
	cout << "Выберите спуск (1) или подъем (2)" << "\n";
	cin >> naprav;
	while (1) {
		datafile2 << x0 << "\t" << (*pfunc)(x0) << "\n"; //Записываем в файл точки движения
		if (naprav == 1) {
			h = - (gradient (*pfunc, x0, dx)) * A; 
		} else {
			h = (gradient (*pfunc, x0, dx)) * A;
		}
		x0 = x0 + h;
		if (h < epsilon && h > -epsilon) { //Если шаг из промежутка (-epsilon,epsilon), то мы находимся в погрешности от точки экстремумма
			return x0;
		}
	}
	datafile2.close();
}

int main () {
	setlocale (0,"");
	int i, a, b; // i - счетчик, a - выбор функции, b - коэф продолжения работы
	double x0, xGrad, A; // x0 - точка старта, xGrad - точка минимума максимума, A - коэфициент спуска
	int const N = 1000; // кол-во точек функции
	double const dx = 0.001; //шаг
	b = 1; // Вводим конкретное значение для зацикливания программы
	while (b == 1) {
		double x1;   
		double x2; 
		cout << "Поставьте границы функции x1 и x2" << "\n" << "x1 = ";
		cin >> x1;
		cout << "x2 = ";
		cin >> x2;
		
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
			
		for (i = 0; i < N; i++) { // Строим массив точек абсцисс функции
			X[i] = x1 + (x2 - x1)/(N-1)*i;
		}
		for (i = 0; i < N; i++) { // Строим массив точек ординат функции
			Y[i] = (*pfunc)(X[i]);
		}
		cout << "Введите коэфициент спуска А, то есть чем А больше, тем больше шаг" << "\n";
		cin >> A;
		cout << "Введите абсциссу точки, с которой будет начинаться движение" << "\n";
		cin >> x0;
		xGrad = spusk(*pfunc, x0, dx, A); //Пишем в xGrad абсциссу точки экстремумма
		cout << "Абцисса минимумма = " << xGrad << "\n";
		
		ofstream datafile1;
		datafile1.open ("data1.txt");
		for (i = 0; i < N; i++) {
			datafile1 << X[i] << "\t" << Y[i] << endl;
		}
		datafile1.close();
		
		ofstream pl;
		pl.open ("plot.graph");
		pl << "set term qt" << endl;
		pl << "plot 'data1.txt' w l, 'data2.txt' using 1:2 with points lw 2 lt rgb 'red'" << endl; // Строим грфик и отображаем на графике точку, в которой вычислили производную
		pl << "pause mouse button1,keypress"<< endl; 
		pl.close();
		cout << "Закройте Gnuplot после просмотра графика для возвращения к работе." << "\n";
		system("gnuplot plot.graph");
		
		cout << "0 - Выход, 1 - Продолжить работу." << "\n";
		cin >> b; // при b = 0 работа завершается
	}
	return 0;
}
