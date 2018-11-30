#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
typedef double real;

class Matrix
{
public:
	Matrix(ifstream &size, ifstream &matrix, ifstream &vector);
	~Matrix();
	real norm(vector <real> x);
	real mult(int flag, int i, vector <real> x);
	void jacobi(real w, vector <real> &xi, real &pogr);
	void gaus_z(real w, vector <real> &xi, real &pogr);
	void iteration(ofstream &result, int flag);
	real cond(vector <real> x, real pogr);
private:
	real eps; // точность решения
	int n, m, maxiter;
	vector <real> di;
	vector <real> l1, l2, u1, u2;
	vector <real> F;
	vector <real> sX;
	real normF;
};

