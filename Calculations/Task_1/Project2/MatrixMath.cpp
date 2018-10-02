#include "MatrixMath.h"

MyMatrix LU_expansion(MyMatrix A)
{

	A.setL(0, 0, A.getElem(0, 0));
	double tmpSum = 0;
	for (unsigned i = 0; i < A.diagSize; ++i)
	{
		for (unsigned j = 0; j < (A.lowerWidth + A.upperWidth + 1); ++j)
		{
			if (j == 0)
			{
				A.setL(i, j, A.getElem(i, 0));
			}
			else
			{
				for (unsigned k = 0; k < j; ++k)
				{
					tmpSum += (A.lower[i][k]) * (A.upper[k][j]); //преобразовывать координаты?
				}
					A.lower[i][j] = (A.getElem(i, j) - tmpSum);
					tmpSum = 0;
					A.upper[i][j] = (A.lower[i][j]) / A.lower[i][i];
			}
		}
	}
		
	return MyMatrix();
}

MyMatrix multiplication(MyMatrix a, MyMatrix b) //преопределить оператор
{
	MyMatrix c;

	return c;
}