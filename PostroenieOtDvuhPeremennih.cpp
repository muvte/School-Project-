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
<<<<<<< HEAD
	double x1, x2, epsilon, A, c = 0; //x1, x2 - координаты старта, epsilon - окресность обнаружения экстрэмума, А - коэф спуска, c - счетчик
=======
	double x1, x2, epsilon, A; //x1, x2 - ГЄГ®Г®Г°Г¤ГЁГ­Г ГІГ» Г±ГІГ Г°ГІГ , epsilon - Г®ГЄГ°ГҐГ±Г­Г®Г±ГІГј Г®ГЎГ­Г Г°ГіГ¦ГҐГ­ГЁГї ГЅГЄГ±ГІГ°ГЅГ¬ГіГ¬Г , ГЂ - ГЄГ®ГЅГґ Г±ГЇГіГ±ГЄГ 
>>>>>>> 039c8aed7543e9a7f042b6e752244b402acf51b4
	epsilon = 5 * dx;
	cout << "Г‚ГўГҐГ¤ГЁГІГҐ ГЄГ®Г®Г°Г¤ГЁГ­Г ГІГ» x1 ГЁ x2 Г± ГЄГ®ГІГ®Г°Г»Гµ ГЎГіГ¤ГҐГІ Г­Г Г·ГЁГ­Г ГІГјГ±Гї Г±ГЇГіГ±ГЄ \n";
	cin >> x1 >> x2;
	double X1[n-1]; // Г‘Г®Г§Г¤Г ГҐГ¬ ГўГҐГЄГІГ®Г° Г±ГІГ Г°ГІГ 
	X1[0] = x1; //Г‡Г ГЇГ®Г«Г­ГїГҐГ¬ ГҐГЈГ®
	X1[1] = x2;
	X1[2] = f(X1);
	gradient (X1, Xout, n, dx); //Г€Г№ГҐГ¬ ГЈГ°Г Г¤ГЁГҐГ­ГІ
	cout << "Г‚ГўГҐГ¤ГЁГІГҐ ГЄГ®ГЅГґГЁГ¶ГЁГҐГ­ГІ Г±ГЇГіГ±ГЄГ  ГЂ, ГІГ® ГҐГ±ГІГј Г·ГҐГ¬ ГЂ ГЎГ®Г«ГјГёГҐ, ГІГҐГ¬ ГЎГ®Г«ГјГёГҐ ГёГ ГЈ \n";
	cin >> A;
	ofstream datafile2; // Г‡Г ГЇГЁГ±Г»ГўГ ГҐГ¬ Гў ГґГ Г©Г« ГІГ®Г·ГЄГЁ, ГЇГ® ГЄГ®ГІГ®Г°Г»Г¬ Г±ГЇГіГ±ГЄГ Г«ГЁГ±Гј
	datafile2.open ("data2.txt");
	while (1) {
<<<<<<< HEAD
		datafile2 << x1 << "\t" << x2 << "\t" << f(X1) << "\n"; //Записываем в файл точки движения
		c++;
		x1 = x1 - A * Xout[0]; //Шагаем
=======
		datafile2 << x1 << "\t" << x2 << "\t" << f(X1) << "\n"; //Г‡Г ГЇГЁГ±Г»ГўГ ГҐГ¬ Гў ГґГ Г©Г« ГІГ®Г·ГЄГЁ Г¤ГўГЁГ¦ГҐГ­ГЁГї
		x1 = x1 - A * Xout[0]; //ГГ ГЈГ ГҐГ¬
>>>>>>> 039c8aed7543e9a7f042b6e752244b402acf51b4
		x2 = x2 - A * Xout[1];
		X1[0] = x1; // Г‡Г ГЇГ®Г«Г­ГїГҐГ¬ ГўГҐГЄГІГ®Г° *Г±ГІГ Г°ГІГ * ГіГ¦ГҐ Г­Г®ГўГ»Г¬ГЁ Г§Г­Г Г·ГҐГ­ГЁГїГ¬ГЁ
		X1[1] = x2;
		X1[2] = f(X1);
		gradient (X1, Xout, n, dx);
		if (Xout[0] < epsilon && Xout[1] < epsilon && Xout[0] > -epsilon && Xout[1] > -epsilon) {
			Xout[0] = x1; // Г‡Г ГЇГ®Г«Г­ГїГҐГ¬ ГўГҐГЄГІГ®Г° *Г±ГІГ Г°ГІГ * ГіГ¦ГҐ Г­Г®ГўГ»Г¬ГЁ Г§Г­Г Г·ГҐГ­ГЁГїГ¬ГЁ
			Xout[1] = x2;
			Xout[2] = f(Xout);
			*shagi = c; //Передаем в указатель на итоговую переменную кол-ва шагов
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
		
		cout << "Координаты экстрэмумма - ";
		for (i = 0; i < n; i++) {
			cout << Xout[i] << "\t";
		}
		cout << endl << "Количество шагов - " << shagi << endl;
		ofstream datafile1;
		datafile1.open ("data1.txt");
		for (X0[0] = -10; X0[0] < 10; X0[0] = X0[0] + 0.1) {
			for (X0[1] = -10; X0[1] < 10; X0[1] = X0[1] + 0.1) {
				datafile1 << X0[0] << "\t" << X0[1] << "\t" << f(X0) << endl;
			}
			datafile1 << endl;
		}
<<<<<<< HEAD
		datafile1.close();
	
		ofstream pl;
		pl.open ("plot.graph");
		pl << "set term qt" << endl;
		pl << "splot 'data1.txt' w l, 'data2.txt' with points lw 2 lt rgb 'red'" << endl; 
		pl << "pause mouse button1,keypress"<< endl; 
		pl.close();
		cout << "Закройте Gnuplot после просмотра графика для возвращения к работе." << "\n";
		system("gnuplot plot.graph");
		cout << "0 - Выход, 1 - Продолжить работу." << "\n";
		cin >> b; // при b = 0 работа завершается
=======
   cout << endl;
>>>>>>> 039c8aed7543e9a7f042b6e752244b402acf51b4
	}
}
