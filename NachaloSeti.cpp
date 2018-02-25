#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#define pi 3.14159265 
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
	return ((*pfunc)(x0 + dx) - (*pfunc)(x0 - dx))/(2 * dx); //Геометрический смысл производной tg a 
}

double spusk (double(*pfunc)(double), double x0, double dx, double A, int x1, int x2, int naprav, int OPRED, int shagi)
{
	double h, epsilon; // h - шаг, epsilon - допустимая погрешность поиска экстремумма
	ofstream datafile2; // Записываем в файл точки, по которым спускались
	datafile2.open ("data2.txt");
	h = 1; //Вводим любой шаг, чтобы в нем не лежал мусор
	epsilon = 5 * dx;
	shagi = 0;
	while (x0 > x1 && x0 < x2) {
		shagi++;
		datafile2 << x0 << "\t" << (*pfunc)(x0) << "\n"; //Записываем в файл точки движения
		if (naprav == 1) {
			h = - (gradient (*pfunc, x0, dx)) * A; 
		} else {
			h = (gradient (*pfunc, x0, dx)) * A;
		}
		x0 = x0 + h;
		if (h < epsilon && h > -epsilon && gradient (*pfunc, x0 - 1, dx) * gradient (*pfunc, x0 + 1, dx) < 0) { //Если шаг из промежутка (-epsilon,epsilon), то мы находимся в погрешности от точки экстремумма
			cout << "Количесто шагов при нахождении экстрэмума = " << shagi << "\n";
			return x0; // Отступаем влево и вправо от экстрэмума и ищем там производные. Если они разных знаков, то при умножении друг на друга результат будет < 0
		}
		if (x0 <= x1) {
			OPRED = 0;
			datafile2 << x1 << "\t" << (*pfunc)(x1) << "\n"; //Записываем в файл точку края ф-ции
			cout << "Количесто шагов при нахождении экстрэмума = " << shagi << "\n";
			return x1;
		}
		if (x0 >= x2) {
			OPRED = 0;
			datafile2 << x2 << "\t" << (*pfunc)(x2) << "\n"; //Записываем в файл точку края ф-ции
			cout << "Количесто шагов при нахождении экстрэмума = " << shagi << "\n";
			return x2;
		}
	}
	datafile2.close();
}

int main () {
	setlocale (0,"");
	int i, a, b, naprav, OPRED, alt4, shagi; // i - счетчик, a - выбор функции, b - коэф продолжения работы, naprav - что будем искать min/max, alt4 - экстрэмум параболы, shagi - кол-во шагов градиента
	double x0, xGrad, A, l, alt; // x0 - точка старта, xGrad - точка минимума максимума, A - коэфициент спуска, alt - альтернативный экстрэмум
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
		cout << "Введите абсциссу точки, с которой будет начинаться движение" << "\n";
		cin >> x0;
		cout << "Выберите спуск (1) или подъем (2)" << "\n";
		cin >> naprav;
		double(*pfunc)(double); // Объявляем указатель
		if (a == 1) { // Смотрим к какой фукции подходит а
			pfunc = f1;
			OPRED = 1;
			l = - pi / 2 + pi * -50; //Тк меньше -50 я думаю мы вводить не будем
			while (!(x0 >= l && x0 <= l + pi)) { // Ищем промежуток от pi / 2 * n до pi / 2 * n + pi
				l = l + pi;
			}
			if (naprav == 1) { //Если спуск, то выбираем нижнюю точку промежутка
				alt = l + pi;
			} else {
				alt = l; //Если подъем, то выбираем верхнюю точку промежутка
			}			
		}
		if (a == 2) {
			pfunc = f2;
			OPRED = 1;
			l = - pi / 4 + pi / 2 * -50; //Тк меньше -50 я думаю мы вводить не будем
			while (!(x0 >= l && x0 <= l + pi)) { // Ищем промежуток от pi / 2 * n до pi / 2 * n + pi
				l = l + pi / 2;
			}
			if (naprav == 1) { //Если спуск, то выбираем нижнюю точку промежутка
				alt = l + pi / 2;
			} else {
				alt = l; //Если подъем, то выбираем верхнюю точку промежутка
			}
		}
		if (a == 3) {
			pfunc = f3;
		}
		if (a == 4) {
			pfunc = f4;
			OPRED = 1;
		}
		if (a == 5) {
			pfunc = f5;
		}
		for (i = 0; i < N; i++) { // Строим массив точек абсцисс функции
			X[i] = x1 + (x2 - x1)/(N-1)*i;
		}
		for (i = 0; i < N; i++) { // Строим массив точек ординат функции
			Y[i] = (*pfunc)(X[i]);
		}

		cout << "Введите коэфициент спуска А, то есть чем А больше, тем больше шаг" << "\n" << "Для функций y=x^3 и y=x*cos(x) совесуется выбирать A < 0.1" << "\n";
		cin >> A;
		xGrad = spusk(*pfunc, x0, dx, A, x1, x2, naprav, OPRED, shagi); //Пишем в xGrad абсциссу точки экстремумма
		cout << "Абцисса экстрэмума = " << xGrad << "\n";
		alt4 = xGrad; // alt4 определен типом int так что при параболе (a = 4) альтернативный экстрэмум будет вычислыться точно
		if (a == 4) {
			alt = alt4;
		}
		if (OPRED == 1) {
			cout << "Погрешность = " << abs(abs(alt) - abs(xGrad)) << "\n"; //Берем модуль от погрешности, так как она всегда положительная
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
		pl << "plot 'data1.txt' w l, 'data2.txt' using 1:2 with points lw 2 lt rgb 'red'" << endl; // РЎС‚СЂРѕРёРј РіСЂС„РёРє Рё РѕС‚РѕР±СЂР°Р¶Р°РµРј РЅР° РіСЂР°С„РёРєРµ С‚РѕС‡РєСѓ, РІ РєРѕС‚РѕСЂРѕР№ РІС‹С‡РёСЃР»РёР»Рё РїСЂРѕРёР·РІРѕРґРЅСѓСЋ
		pl << "pause mouse button1,keypress"<< endl; 
		pl.close();
		cout << "Закройте Gnuplot после просмотра графика для возвращения к работе." << "\n";
		system("gnuplot plot.graph");
		
		cout << "0 - Выход, 1 - Продолжить работу." << "\n";
		cin >> b; // при b = 0 работа завершается

	}
	return 0;
}
