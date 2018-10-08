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
{
	double tmpsum = 0;
	for (unsigned i = 0; i < A->height; ++i)
	{
			for (int k = 1; k < A->width + 1; ++k) //переход к столбцам Al[i][j] = L[i][width - (i-j) + 1]
			{	
			A->upper[k][A->width - k];
			}
		}
		for (unsigned j = 0; j < A->width; ++j)
		{
			for (int k = 0; k <= j - 1; ++k)
			{
				tmpsum += A->lower[i][k] * A->upper[k][j];
			}
			A->upper[i][j] -= tmpsum;
		}
	}

	
	A->upper[i][j] -= tmpsum;














	double tmpSum = 0;
	for (unsigned i = 0; i < A->height; ++i)
	{
		for (unsigned j = 0; j < A->height; ++j)
			for (unsigned j = 0; j < (A->width + 1); ++j)
			{
				if (j = 0)
					if (j == 0)
					{
						A.lower[i][j] = A.getElem(i, 0);
						A.setL(i, j, A.getElem(i, 0));
					}
					else
					{
						for (int k = 0; k <= j; ++k)
							for (unsigned k = 0; k < j; ++k)
							{
								tmpSum += (A.lower[i][k]) * (A.upper[k][j]); //aaaaaaaaaaa
								tmpSum += (A.lower[i][k]) * (A.upper[k][j]); //��������������� ����������?
							}
						A.lower[i][j] = (A.getElem(i, j) - tmpSum);
						tmpSum = 0;
						A.upper[i][j] = (A.lower[i][j]) / A.lower[i][i];
					}
			}
	}
}
