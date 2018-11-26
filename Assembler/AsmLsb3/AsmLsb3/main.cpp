#include <stdio.h>
#include <locale>
using namespace std;

extern "C" int __stdcall newton(float eps, float *x);

int main()
{
	setlocale(LC_CTYPE, "Russian");
	float eps;
	float x;
	int iter;
	printf_s("Введите точность решения: ");
	scanf_s("%f", &eps);
	iter = newton(eps, &x);
	printf_s("Количество итераций: %d\nx = %f\n", iter, x);
	system("PAUSE");
	return 0;
}
