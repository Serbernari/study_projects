#include "MatrixMath.h"

void mult_MatOnVect(MyMatrix * A, std::vector<double>* V)
{
	std::vector<double> tmp;
	for (unsigned i = 0; i < A->height; ++i)
	{
		tmp.push_back(0);

		for (unsigned j = 0; j < A->width; ++j) //lower triangle 
		{
			tmp[i] += (A->lower[i][j]) * (*V)[i];
		}

		{
			tmp[i] += A->diag[i] * (*V)[i]; //diagonal
		}

		for (unsigned j = 0; j < A->width; ++j) //upper triangle 
		{
			if (i + 1 + j < A->height)
			{
				tmp[i] += (A->upper[i + 1 + j][A->width - 1 - j]) * (*V)[i]; //переделать всю верхнюю матрицу ради этого?
			}
		}
	}
	*V = tmp; //колхоз, переделать
}

void mult_MatOnMat(MyMatrix * A, MyMatrix * B)
{
	/*smh vertical vector*/
}

void LU_expansion(MyMatrix * A)
{ //разложение LU
	for (int i = 0; i < A->height; i++)
	{
		double sum_d = 0;
		int j = i - A->width;

		for (int jL = 0; jL < A->width; jL++, j++)
		{
			if (j < 0) continue;
			double sum_l = 0;
			double sum_u = 0;
			int kU = i - j;

			for (int kL = 0; kL < jL; kL++, kU++)
			{
				//if ()
				sum_l += A->lower[i][kL] * A->upper[j][kU];
				sum_u += A->upper[i][kL] * A->lower[j][kU];
			}

			A->lower[i][jL] -= -sum_l;
			A->upper[i][jL] -= sum_u;
			A->upper[i][jL] / A->diag[j];
			sum_d += A->lower[i][jL] * A->upper[i][jL];
		}
		A->diag[i] = A->diag[i] - sum_d;
	}
}
