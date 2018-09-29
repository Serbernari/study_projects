#include <iostream>
#include <fstream>
#include "strip_matrix.h"

void readMatrix(ifstream &input, vector<vector<double> >* myMatrix, int matSize)
{
	for (int i = 0; i < matSize; ++i)
	{		vector<double> tmp;
		for (int j = 0; j < matSize; ++j)
		{
			float n;
			input >> n;
			tmp.push_back(n);
		}
		myMatrix->push_back(tmp);
	}
}


int main()
{
	const unsigned matSize = 5;
	vector<vector<double> > myMatrix;
	/*myMatrix.resize(matSize);
	for (int i = 0, size = myMatrix.size(); i < size; ++i)
		myMatrix[i].resize(matSize);*/

	ifstream input;
	input.open("d:\\matrixInput.txt");
	readMatrix( input, &myMatrix, matSize);
	input.close();
	
	return 0;
}
