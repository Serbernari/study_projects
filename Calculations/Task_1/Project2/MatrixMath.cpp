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
			tmp[i] += (A->upper[i][j]) * (*V)[i];
		}
	}
	*V = tmp; //колхоз, переделать
}
