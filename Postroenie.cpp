#include <iostream>
#include <cstring>
#include <cmath>
#define PI 3.14159265  
using namespace std;
int trig () 
{
	int i;
	char A [3];
	cout << "Назовите тригонометрическую функцию";
	for (i = 0; i < 3; i++) {
		cin >> A[i];
	}
	if (A[1] == 's' && A[2] == 'i' && A[3] == 'n') {
		return 1;
	}
	if (A[1] == 'c' && A[2] == 'o' && A[3] == 's') {
		return 2;
	}
}
double sin(double x)
{
	double y;
	y = sin (x + PI / 180);
	return y;
}
double cos(double x)
{
	double y;
	y = cos (x + PI / 180);
	return y;
}
double other (double x) {
	setlocale (0,"");
	double ;
	cout << "Введите уравнение";
	cin >> m >> n >> k;
	;
}
int main ()
{
	setlocale (0,"");
	int a, b, c, d, i, N, m, n, k;
	cout << "Введите границы построение графика";
	cin >> a >> b;
	cout << "Если вы хотите построить тригонометрическую функцию, то введите '1', а если другую, то '2'";
	cin >> c;
	if (c == 1) {
		d = trig();
	}
	if (c == 2) {
		d = 3;	
	}
	N = 1000;
	int x[N];
	int y[N];
	if (d == 1) {
		for (i = 0; i < N; i++) {
			x[i] = a + (i *( (b - a) / N - 1) );
			y[i] = sin(x[i]);
		}
	}
	if (d == 2) {
		for (i = 0; i < N; i++) {
			x[i] = a + (i *( (b - a) / N - 1) );
			y[i] = cos(x[i]);
		}
	}

	if (d == 3) {
		for (i = 0; i < N; i++) {
			x[i] = a + (i *( (b - a) / N - 1) );
			y[i] = kvadr(x[i]);
		}
	}
	plot (x,y) // Я пока не нашел нормальной библиотеки
}
