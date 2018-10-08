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
	//переход к столбцам Al[i][j] = L[i][width - (i-j) + 1]
					  // Au[i][j] = U[j][width - (j-i) + 1]
	

	for (unsigned i = 0; i < A->height; ++i)
	{
		double tmpsum = 0;
		
		for (unsigned j = 0; j < A->width; ++j)
		{ 
			//надо попеременно расчитывать
			for (int k = 0; k <= j; ++k)
			{
				tmpsum += A->lower[i][A->width - (i-k)] * A->upper[j][A->width - (j-k)];
			}
			if ((j > i) && (A->width >= j - i))
			{
				A->upper[j][A->width - (j - i) ] -= tmpsum;
				A->upper[j][A->width - (j - i) ] / A->diag[i];
			}
			else if ((i > j) && (A->width >= i - j))
			{
				A->lower[i][A->width - (i - j) ] -= tmpsum;
				//A->lower[i][A->width - (i - j) + 1] 
			}
			else 
			{

			}
		}
	}
	



	/*//double tmpSum = 0;
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
	}*/
}
