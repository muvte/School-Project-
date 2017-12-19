#include <iostream>                                   
#include <cmath> 
#define PI 3.14159265                                   
using namespace std;                              
int main()
{
	int y1;
	double x, delta, Y, res;
	double y;
	cin >> x;
/*	double param;
	cin >> param;
	cout << " sin " << param << " = " << sin(param * PI / 180) << endl;
	return 0;*/
	delta = 1;
	res = 404;
	while (1) {
		y = sin(x * PI / 180);                 // Вычисляет ординату x
		Y = sin((x + delta) * PI / 180);	   // Вычисляет ординату x + delta
		if (Y > y) {
			x = x + delta; 					   // Если вторая ордината больше первой, то заменяем x на x + delta
		} else {
			if (Y == y) {
				res = (x + x + delta) / 2;	   // Если delta такая, что две ординаты равны, тогда абсцисса экстремума на средне-арифметическом x и x + delta
				break;
			}
			delta = - delta / 2;			   // Eсли же вторая ордината меньше первой, тогда мы прошли эксремум.
											   // Надо развернуться и уменьшить шаг, чтобы по тем же точкам не пройти его еще раз
		}
		if (delta < 0.001) {				   // Наконец если шаг минимален, тогда с погрешностью мы можем взять абциссу эксремума
			res = x;
			break;
		} else {
			cout << x << endl;
		}
	}
	cout << res;
}
