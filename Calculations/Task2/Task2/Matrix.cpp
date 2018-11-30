#include "Matrix.h"

Matrix::Matrix(ifstream &size, ifstream &matrix, ifstream &vector)
{
	size >> n >> m >> maxiter >> eps;
	di.resize(n);
	l1.resize(n - 1);
	u1.resize(n - 1);
	l2.resize(n - m - 2);
	u2.resize(n - m - 2);
	sX.resize(n);
	F.resize(n);
	for (int i = 0; i < n - m - 2; i++)
		matrix >> l2[i];
	for (int i = 0; i < n - 1; i++)
		matrix >> l1[i];
	for (int i = 0; i < n; i++)
	{
		matrix >> di[i];
		vector >> F[i];
	}
	for (int i = 0; i < n - 1; i++)
		matrix >> u1[i];
	for (int i = 0; i < n - m - 2; i++)
		matrix >> u2[i];
	for (int i = 0; i < n; i++)
		vector >> sX[i];
	normF = norm(F);
}

Matrix::~Matrix() {
}

real Matrix::norm(vector <real> x)
{
	real norma = 0;
	for (int i = 0; i < n; i++)
		norma += pow(x[i], 2);
	norma = sqrt(norma);
	return norma;
}

real Matrix::mult(int flag, int i, vector <real> x)
{
	real res = 0;
	if (flag == 1 || flag == 3) // нижний треугольник
	{
		if (i > 0)
		{
			res += x[i - 1] * l1[i - 1];
			if (i > m + 1)
				res += x[i - m - 2] * l2[i - m - 2];
		}
	}
	if (flag == 2 || flag == 3) // верхний треугольник
	{
		res += x[i] * di[i];
		if (i < n - 1)
		{
			res += x[i + 1] * u1[i];
			if (i < n - m - 2)
				res += x[i + m + 2] * u2[i];
		}
	}
	return res;
}

void Matrix::jacobi(real w, vector <real> &xi, real &pogr)
{
	real buf = 0;
	pogr = 0;
	for (int i = 0; i < n; i++)
	{
		buf = F[i] - mult(3, i, sX);
		xi[i] = sX[i] + w * buf / di[i];
		pogr += pow(buf, 2);
	}
	pogr = sqrt(pogr) / normF;
}

void Matrix::gaus_z(real w, vector <real> &xi, real&pogr)
{
	real buf = 0;
	pogr = 0;
	for (int i = 0; i < n; i++)
	{
		buf = F[i] - mult(1, i, xi) - mult(2, i, sX);
		xi[i] = sX[i] + w * buf / di[i];
		pogr += pow(buf, 2);
	}
	pogr = sqrt(pogr) / normF;
}

void Matrix::iteration(ofstream &result, int flag)
{
	vector <real> xi(n);
	vector <real> x(n);
	real condN;
	x = sX;
	real pogr;
	real w = 0.5;
	int exit = 0;
	result.precision(15);
	for (int i = 0; i < maxiter&&exit != 1; i++) {
		if (flag == 1)
		{
			jacobi(w, xi, pogr);
			sX = xi;
		}
		if (flag == 2)
		{
			gaus_z(w, xi, pogr);
			sX = xi;
		}
		cout << "step = " << i + 1 << " " << "discrepancy = " << pogr << endl;
		if (pogr < eps)
		{
			exit = 1;
			cout << "EXIT" << endl;
		}

	}
	if (exit != 1)
		cout << "Аварийное завершение (шаг больше максимального числа итераций)" << endl;
	for (int i = 0; i < n; i++)
		result << xi[i] << " ";
	result << endl;
	condN = cond(xi, pogr);
	result << condN;
}

real Matrix::cond(vector <real> x, real pogr)
{
	real res;
	for (int i = 0; i < n; i++)
	{
		x[i] -= i + 1;
	}
	res = norm(x);
	res = res / norm(sX);
	res = res / pogr;
	return res;
}
