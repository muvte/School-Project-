// basic file operations
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int const N = 1000;  /// всего точек
float const pi = 3.1416;  // констанка ѕи

float x1 = -pi*3;   // начальна€ точка оси X
float x2 = pi*3;   // конечна€ точка оси X

float X[N];   // массив оси X
float Y[N];   //массив оси Y

int main () {
	// точки оси X
	for (int i = 0; i < N; i++) {
		X[i] = x1 + (x2 - x1)/(N-1)*i;
	}
	
	// ¬ычисление синуса во всех точках
	for (int i = 0; i < N; i++) {
		Y[i] = sin(X[i]);
	}
	
	// вывод данных в файл
  ofstream datafile;
  datafile.open ("data.txt");
  for (int i = 0; i < N; i++) {
    datafile << X[i] << '\t' << Y[i] << endl;
  }
  datafile.close();
  
  // скрипт дл€ gnuplot
  ofstream pl;
  pl.open ("plot.graph");
  pl << "set term qt" << endl;     // установка терминала
  pl << "plot 'data.txt' w l " << endl;   // выбор файла, в котором наход€тс€ данные
  pl << "pause mouse button1,keypress"<< endl;  // сказать gnuplot-у, чтобы он ждал, пока не будет нажата кнопка мыши
  pl.close();
  
  // запуск внешней программы gnuplot
  system("gnuplot plot.graph");
  
  return 0;
}
