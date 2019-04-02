#include <iostream>
#include <math.h>
#include <vector>
#include <conio.h>
using namespace std;
double lambda = 1, eps = 1E-7
;
static int f_calc;
double func_rozenbrock(vector <double>point)
{
	double y = point[1], x = point[0];
	return 100 * (y - x * x)*(y - x * x) + (1 - x)*(1 - x);
}
double func(vector <double>point)
{
	double y = point[1], x = point[0];
	f_calc++;
	//return 100 * (y - x)*(y - x) + (1 - x)*(1 - x);
	return 100 * (y - x * x)*(y - x * x) + (1 - x)*(1 - x);
}
double diff_x_func_rozenbrock(vector <double>point)
{
	double y = point[1], x = point[0];
	return 2 * (200 * pow(x, 3) - 200 * x*y + x - 1);
}
double diff_y_func_rozenbrock(vector <double>point)
{
	double y = point[1], x = point[0];
	return 200 * (y - x * x);
}
double diff_x_func(vector <double>point)
{
	double y = point[1], x = point[0];
	//return 202 * x - 200 * y - 2;
	return 2 * (200 * pow(x, 3) - 200 * x*y + x - 1);
}
double diff_y_func(vector <double>point)
{
	double y = point[1], x = point[0];
	//return 200 * (y - x);
	return 200 * (y - x * x);
}
vector <double> operator-(vector<double> & l, vector <double> & r)
{
	if (l.size() != r.size())
		throw("operator-: incompatible dimensions.");
	vector <double> ret(l.size());
	for (size_t i = 0; i < l.size(); i++)
		ret[i] = l[i] - r[i];
	return ret;
};
vector <double> operator+(vector<double> & l, vector <double> & r)
{
	if (l.size() != r.size())
		throw("operator+: incompatible dimensions.");
	vector <double> ret(l.size());
	for (size_t i = 0; i < l.size(); i++)
		ret[i] = l[i] + r[i];
	return ret;
};
vector <double> operator*(vector<double> & l, double r)
{
	vector <double> ret(l.size());
	for (size_t i = 0; i < l.size(); i++)
		ret[i] = l[i] * r;
	return ret;
};
vector <double> operator/(vector<double> & l, double r)
{
	vector <double> ret(l.size());
	for (size_t i = 0; i < l.size(); i++)
		ret[i] = l[i] / r;
	return ret;
};
double norm(vector <double> x)
{
	return sqrt(x[0] * x[0] + x[1] * x[1]);
}
double lambd_func(vector <double> x, vector <double> grad, double lambd)
{
	double  grad_norm = 1 / norm(grad);
	vector <double> grad_normalized(2);
	grad_normalized = grad * grad_norm;
	grad_normalized = grad_normalized * lambd;
	return func(x - grad_normalized); //return func(x - grad_normalized); for gradient decent
}
void interval(vector <double> x0, vector <double> grad, double& a, double& b)
{
	double f0 = lambd_func(x0, grad, lambda);
	double delta = 1e-5, h = delta;
	double lambda_new1 = lambda + delta;
	double f1 = lambd_func(x0, grad, lambda_new1);

	if (f0 < f1) {
		lambda_new1 = lambda - delta;
		h *= -1;
	}

	bool end_cycle = false;

	while (!end_cycle) {
		h *= 2;
		lambda = lambda_new1 + h;
		f0 = lambd_func(x0, grad, lambda);

		if (f1 > f0) {
			lambda_new1 = lambda;
			f1 = f0;
		}
		else {
			end_cycle = true;
			lambda_new1 = lambda;
			lambda -= h + h / 2;
		}

	}
	a = lambda_new1; b = lambda;
	if (a > b) swap(a, b);
}

double fibonacci(vector <double> x, vector <double> grad)
{
	int n = 1;
	double lambda_new1, lambda_new2, f1, f2, a, b = 10;
	double fib1 = 1, fib2 = 1, fib3 = 2;
	interval(x, grad, a, b);
	while (fabs(b - a) / eps >= fib3)
	{
		fib1 = fib2;
		fib2 = fib3;
		fib3 = fib2 + fib1;
		n++;
	}
	lambda_new1 = a + (fib1 / fib3)*(b - a);
	lambda_new2 = a + (fib2 / fib3)*(b - a);
	f1 = lambd_func(x, grad, lambda_new1);
	f2 = lambd_func(x, grad, lambda_new2);
	for (int k = 1; k < n + 1; k++)
	{
		double fib1_buf = fib2 - fib1;
		fib3 = fib2;
		fib2 = fib1;
		fib1 = fib1_buf;
		if (f1 > f2)
		{
			a = lambda_new1;
			lambda_new1 = lambda_new2;
			f1 = f2;
			lambda_new2 = a + (fib2 / fib3)*(b - a);
			f2 = lambd_func(x, grad, lambda_new2);
		}
		else
		{
			b = lambda_new2;
			lambda_new2 = lambda_new1;
			f2 = f1;
			lambda_new1 = a + (fib1 / fib3)*(b - a);
			f1 = lambd_func(x, grad, lambda_new1);
		}
		//out.precision(15);
		//out << k << str << a << str << b << str << b - a << str << x1 << str << x2 << str << f1 << str << f2 << endl;
	}
	//lambda_new2 = lambda_new1 + eps;
	//f2 = lambd_func(x, grad, lambda_new2);
	//if (f1 <= f2)
	//	b = lambda_new1;
	//else
	//	a = lambda_new1;
	return (a + b) / 2.0;
}

double mult(vector <double> x, vector < double> y)
{
	return x[0] * y[0] + x[1] * y[1];
}

void rozenbrock(vector <double> point)
{
	vector <double> x(2), b(2);
	vector <vector<double>> s, a;
	double lambda1, lambda2;
	int iter = 0;
	f_calc = 0;
	s.resize(2); a.resize(2);
	for (int i = 0; i < 2; i++)
	{
		s[i].resize(2);
		a[i].resize(2);
	}
	x[0] = point[0];
	x[1] = point[0];
	// Начальные ортогональные направления
	s[0][0] = s[1][1] = 1.0;
	s[0][1] = s[1][0] = 0.0;
	// Сам метод (стандартный)
	while (fabs(func(x) - func(point)) > eps)
	{
		point = x;
		lambda1 = fibonacci(x, s[0]);
		x = x + s[0] * lambda1;
		lambda2 = fibonacci(x, s[1]);
		x = x + s[1] * lambda2;
		// Построение новых ортогональных направлений
		a[0] = s[0] * lambda1 + s[1] * lambda2;
		// Сортировка лямбд по убыванию
		if (fabs(lambda1 >= lambda2))
			a[1] = s[1] * lambda2;
		else
			a[1] = s[0] * lambda1;
		// Ортогонализация Грамма-Шмидта
		s[0] = a[0] / norm(a[0]);
		b = a[1] - s[1] * mult(a[1], s[1]);
		if (norm(b) > eps)
			s[1] = b / norm(b);
		iter++;
		//printf("%d %.7lf %.7lf %.7lf %.7lf %.7lf %.7lf %.7lf %.7lf %.7lf %.7lf %.7lf %.7lf\n", iter, x[0], x[1], func(x), 
			//s[0][0], s[0][1], s[1][0], s[1][1], lambda1, lambda2, fabs(x[0] - point[0]), fabs(x[1] - point[1]), fabs(func(x) - func(point)));
		//cout << f_calc << '\t' << iter << '\t' << "[ " << x[0] << ", " << x[1] << " ]" << '\t' << func(x) << endl;
	}
	//cout << f_calc << '\t' << iter << '\t' << "[ " << x[0] << ", " << x[1] << " ]" << '\t' << func(x) << endl;
	printf("%.7lf %d %d %.7lf %.7lf	%.7lf", eps, iter, f_calc, x[0], x[1], func(x));
}

vector <double> gradient_descent(vector <double> point)
{
	int k = 1; f_calc = 0;
	vector <double> res(2), grad(2), x(2), nabla_f(2);
	grad[0] = diff_x_func(point);
	grad[1] = diff_y_func(point);
	double grad_norm = lambda / norm(grad);
	x = point - grad * grad_norm;
	while (fabs(func(x) - func(point)) > eps )
	{
		point = x;
		grad[0] = diff_x_func(point);
		grad[1] = diff_y_func(point);
		lambda = fibonacci(point, grad);
		double grad_norm = lambda / norm(grad);
		x = point - grad * grad_norm;
		k++;
		printf("%.7lf %d %d %.7lf %.7lf	%.7lf \n", eps, k, f_calc, x[0], x[1], func(x));
	}
	return x;
}

void main()
{
	vector <double> point(2), res(2);
	point[0] = 3; point[1] = 2;
	eps = 1E-3;
	gradient_descent(point);
	//while (eps >= 1E-7)
	{
	//rozenbrock(point);
	eps /= 10;
	}
	_getch();
}