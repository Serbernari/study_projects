#include "MatrixMath.h"

void mult_MatOnVect(MyMatrix * A, std::vector<real>* V)
{
	std::vector<real> tmp;
	for (unsigned i = 0; i < A->height; ++i)
	{   tmp.push_back(0);
		for (unsigned j = 0; j < A->width; ++j) //lower triangle 
		{
			tmp[i] += (A->lower[i][j]) * (*V)[i];
		}
		tmp[i] += A->diag[i] * (*V)[i]; //diagonal
		
		for (unsigned j = 0; j < A->width; ++j) //upper triangle 
		{   if (i + 1 + j < A->height)
			    tmp[i] += (A->upper[i + 1 + j][A->width - 1 - j]) * (*V)[i]; 
		}
	}
	*V = tmp; 
}

void mult_MatOnMat(MyMatrix * A, MyMatrix * B)
{
	/*smh vertical vector*/
}

void LU_dec(MyMatrix * A)
{ //разложение LU
	for (unsigned i = 0; i < A->height; i++)
	{	real sum_d = 0;
		int j = i - A->width;
		for (unsigned jL = 0; jL < A->width; jL++, j++)
		{	if (j < 0) continue;
			real sum_l = 0;
			real sum_u = 0;
			int kU = i - j;

			for (int kL = 0; kL < jL; kL++, kU++)
			{	sum_l += A->lower[i][kL] * A->upper[j][kU];
				sum_u += A->upper[i][kL] * A->lower[j][kU];
			}
			A->lower[i][jL] -= -sum_l;
			A->upper[i][jL] -= sum_u;
			A->upper[i][jL] = A->upper[i][jL] / A->diag[j];
			sum_d += A->lower[i][jL] * A->upper[i][jL];
		}
		A->diag[i] = A->diag[i] - sum_d;
	}
}

void forward_sol(MyMatrix* A, std::vector<real>* F) // 
{
	real tmp_sum = 0;
	for (unsigned i = 0; i < A->height; ++i)
	{
		for (unsigned k = 0; k < A->width; ++k)
		{
			tmp_sum += A->lower[i][k] * F->at(k);
		}
		F->at(i) -= tmp_sum; //same []
		tmp_sum = 0;
	}
}
void backward_sol(MyMatrix* A, std::vector<real>* F)
{
	real tmp_sum = 0;
	for (unsigned i = A->height - 1; i > 0; --i)
	{
		for (unsigned k = 0; k < A->width; ++k)
		{
			tmp_sum += A->upper[i][k] * F->at(k);
		}
		F->at(i) -= tmp_sum;
		F->at(i) = F->at(i) / A->diag[i];
	}
}
/*
void LU_sol(MyMatrix* A, std::vector<real> F)
{
	forward_sol(A, F);
	backward_sol(A, F);
}*/

MyMatrix HilbertMat(const unsigned size) //all stored in
{
	MyMatrix A;

	std::vector<real> tmp;
	for (unsigned j = 0; j < size; ++j)
	{
		tmp.push_back(0);
	}

	for (unsigned i = 0; i < size; ++i)
	{
		A.diag.push_back(0);
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
				A.lower[i][j] = (1.0 / (real)(i + j + 1));
			}
			else if (i < j)
			{
				A.upper[j][i] = (1.0 / (real)(i + j + 1)); // ij or ji?
			}
		}
	}
	return A;
}

