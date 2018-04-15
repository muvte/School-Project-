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
/*	if (F > *Konec) //Определяем самый большой и самый маленький аргумент точки и сдвигаем границу построения графика на эту точку
	*Konec = F; // чтобы облость определения графика была заключена в 2-ух крайних точках
	if (F < *Nachalo)
	*Nachalo = F;*/
	return tanh(F);
}
int main ()
{	
	int i, N = 1000, n = 3, Ntochek = 1000; // i- счетчик, N - кол-во точек функции, n - кол-во измерений, Ntochek - кол-во рандомных точек на графике.
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
		RandomHelp = random(-100, 100); //Рандомизируем ненужную нам переменную (RandomHelp), чтобы srand time как-то попортился и был действительно рандом
		x1 = random(-10, 10); //Если так не делать, то он будет выдавать числа, а при с слежующм запросе будет быдавать такое же число +- 0.02
		RandomHelp = random(-100, 100); 
		x2 = random(-10, 10);
	//	F = net(x1, x2, X0); //Записываем получившийся аргуент в переменную F
		datafile2 << x1 << "\t" << x2 << "\t" << net(x1,x2,X0) << "\n"; // Записываем точки в файл
	}
	datafile2.close();
	
	ofstream datafile1;
	datafile1.open ("data1.txt");
	for (x1 = -10; x1 < 10; x1 = x1 + 0.5) {
			for (x2 = -10; x2 < 10; x2 = x2 + 0.5) {
				datafile1 << x1 << "\t" << x2 << "\t" << net(x1,x2,X0) << endl;
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
//	pl << "set xrange [-2:2]" << endl;
//	pl << "set yrange [-2:2]" << endl;
    pl << "splot 'data2.txt' with points lw 5 , 'data1.txt' w l ls 1" << endl; 
	//pl << "pause mouse button1,keypress"<< endl;  // Будем вызывать gnulot самостоятельно, чтобы можно было крутить график
	pl.close();
	system("gnuplot plot.graph");
}
