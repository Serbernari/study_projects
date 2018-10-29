#include "MatrixMath.h"

//сравнивать с LLT

void LU_dec(MyMatrix * A)
{ //разложение LU
	for (unsigned i = 0; i < A->height; i++)
	{	real sum_d = 0;
		int j = i - A->width;
		for (unsigned jL = 0; jL < A->width; jL++, j++)
		{	
			if (j < 0) continue;
			real sum_l = 0;
			real sum_u = 0;
			int kU = i - j;

			for (int kL = 0; kL < jL; kL++, kU++)
			{	
				sum_l += A->lower[i][kL] * A->upper[j][kU];
				sum_u += A->upper[i][kL] * A->lower[j][kU];
			}
			A->lower[i][jL] = A->lower[i][jL] - sum_l;
			A->upper[i][jL] = (A->upper[i][jL] - sum_u) / A->diag[j];
			sum_d += A->lower[i][jL] * A->upper[i][jL];
		}
		A->diag[i] = A->diag[i] - sum_d;
	}
}

void forward_sol(MyMatrix A, std::vector<real> F) //правь
{	
	std::vector<double> Y(F.size());
	real sum;
	for (int i = 0; i < A.height; i++)
	{
		int j = i - A.width;
		sum = 0;
		for (int jL = 0; jL < A.width; jL++, j++)
		{	
			if (j < 0) continue;
			sum += A.lower[i][jL] * F[j];
		}
		F[i] -= sum;
	}
}

std::vector<double> backward_sol(MyMatrix A, std::vector<real>  F) //правь
{	
	std::vector<double> tmp(F.size());
	for (int i = A.height - 1; i >= 0; i--)
	{
		int j = i - A.width;
		real Xi = F[i] / A.diag[i];
		for (int jL = 0; jL < A.width; jL++, j++)
		{
			if (j < 0) continue;
			F[j]-= A.upper[i][jL] * Xi;

		}
		tmp[i] = Xi;
	}
	return tmp;
}

void LU_sol(MyMatrix* A, std::vector<real> F)
{
	forward_sol(*A, F);
	backward_sol(*A, F);
}

MyMatrix HilbertMat(const unsigned size) //all stored in
{
	MyMatrix A;
	A.height = size;
	A.width = size - 1 ; //ACHTUNG
	std::vector<real> tmp;
	for (unsigned j = 0; j < size - 1; ++j)
		tmp.push_back(0);
	for (unsigned i = 0; i < size; ++i)
	{	A.diag.push_back(0);
		A.lower.push_back(tmp);
		A.upper.push_back(tmp);
	}
	
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			if (i == j)
			{
				A.diag[i] = (1.0 / (real)(i + j + 1));
			}
			else if (i > j)
			{
				if (i < A.width)
				{ 
					A.lower[i][A.width - i + j] = (1.0 / (real)(i + j + 1));
				}
				else
				{
					A.lower[i][j] = (1.0 / (real)(i + j + 1));
				}								
			}			
		}
	}

	A.upper = A.lower; //becouse Hilbert matrix is symertical

	return A;
}

void makeDetNotZero(MyMatrix * A, int k)
{
	A->diag[0] += pow(10, -k);
}

