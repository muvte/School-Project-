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
double net (double x1, double x2, double X0[], double* Nachalo, double* Konec) // Создаем указатель и работаем с ним, чтобы после функции return F; все изменения с этой переменной не стерлись
{
	setlocale(0,"");
	double F; //Аргумент будущей точки
	double w1 = X0[0]; //Присваиваем знаечения вектора старта весовым коэфициентам и смещению
	double w2 = X0[1];
	double b = X0[2];
	F = b + w1 * x1 + w2 * x2; //Подсчет аргумента точки
	if (F > *Konec) //Определяем самый большой и самый маленький аргумент точки и сдвигаем границу посто\роения графика на эту точку
	*Konec = F; // чтобы облость определения графика была заключена в 2-ух крайних точках
	if (F < *Nachalo)
	*Nachalo = F;
	return F;
}
int main ()
{	
	int i, N = 1000, n = 3, Ntochek = 100; // i- счетчик, N - кол-во точек функции, n - кол-во измерений, Ntochek - кол-во рандомных точек на графике.
	double X[N];
	double Y[N];
	double X0[n];
	double x1, x2, RandomHelp, b, w1, w2, Nachalo, Konec, F;
	Nachalo = -2;
	Konec = 2;
	
	srand (time(0));
	RandomHelp = random(-100, 100); // Описание ниже. Строка 55
	X0[0] = random(-5, 5); //Рандомизируем 
	RandomHelp = random(-100, 100);
	X0[1] = random(-5, 5);
	RandomHelp = random(-100, 100);
	X0[2] = random(-5, 5);
	cout << "w1 - " << X0[0] << "\nw2 - " << X0[1] << "\nb - " << X0[2] << endl; 
	
	ofstream datafile2;
	datafile2.open ("data2.txt");
	for (i = 0; i < Ntochek; i++) {
		RandomHelp = random(-100, 100); //Рандомизируем ненужные нам переменную (RandomHelp), чтобы srand time как-то попортился и был действительно рандом
		x1 = random(-50, 51); //Если так не делать, то он будет выдавать числа, а при с слежующм запросе будет быдавать такое же число +- 0.02
		RandomHelp = random(-100, 100); 
		x2 = random(-50, 51);
		F = net(x1, x2, X0, &Nachalo, &Konec); //Записываем получившийся аргуент в переменную F
		datafile2 << F << "\t" << tanh(F) << "\n"; // Записываем точки в файл
	}
	datafile2.close();
	
	for (i = 0; i < N; i++) { // Строим массив точек абсцисс функции
		X[i] = Nachalo + (Konec - Nachalo)/(N-1)*i;
	}
	
	for (i = 0; i < N; i++) { // Строим массив точек ординат функции
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
	pl << "set linestyle 1 lt 1 lw 3" << endl; //Содаем стиль для гнуплота. Особенность- толщина линий lw3;
    pl << "plot 'data1.txt' w l ls 1, 'data2.txt' with points lw 2 lt rgb 'red'" << endl; 
	pl << "pause mouse button1,keypress"<< endl; 
	pl.close();
	system("gnuplot plot.graph");
}
