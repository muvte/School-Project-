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
		y = sin(x * PI / 180);                 // ��������� �������� x
		Y = sin((x + delta) * PI / 180);	   // ��������� �������� x + delta
		if (Y > y) {
			x = x + delta; 					   // ���� ������ �������� ������ ������, �� �������� x �� x + delta
		} else {
			if (Y == y) {
				res = (x + x + delta) / 2;	   // ���� delta �����, ��� ��� �������� �����, ����� �������� ���������� �� ������-�������������� x � x + delta
				break;
			}
			delta = - delta / 2;			   // E��� �� ������ �������� ������ ������, ����� �� ������ ��������.
											   // ���� ������������ � ��������� ���, ����� �� ��� �� ������ �� ������ ��� ��� ���
		}
		if (delta < 0.001) {				   // ������� ���� ��� ���������, ����� � ������������ �� ����� ����� ������� ���������
			res = x;
			break;
		} else {
			cout << x << endl;
		}
	}
	cout << res;
}
