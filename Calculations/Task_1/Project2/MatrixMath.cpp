#include "MatrixMath.h"

MyMatrix LU_expansion(MyMatrix A)
{
	A.lower[0][0] = A.getElem(0, 0);
	double tmpSum = 0;
	for (unsigned i = 0; i < A.diagSize; ++i)
	{
		for (unsigned j = 0; j < A.diagSize; ++j)
		{
			if (j = 0)
			{
				A.lower[i][j] = A.getElem(i, 0);
			}
			else
			{
				for (int k = 0; k <= j; ++k)
				{
					tmpSum += (A.lower[i][k]) * (A.upper[k][j]); //aaaaaaaaaaa
				}
					A.lower[i][j] = (A.getElem(i, j) - tmpSum);
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