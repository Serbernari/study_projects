#include "strip_matrix.h"

strip_matrix::strip_matrix()
{
	std::vector<float> diag; //main diagonal
	std::vector<float> l_diag; //lower diagonal 
	std::vector<float> u_diag; //upper diagonal
}
/*
void readMatrixFromFile(ifstream input)
{
	ifstream input;
	input.open("d:\\MatrixInput.txt");

	char tmp; //что бы замечать \n
	while (true)
	{		
		input >> tmp;
		if (input.eof()) break;

		if (tmp != '0')
		{

		}
		myMatrix.push_back(n);
	}
}
*/

strip_matrix::~strip_matrix()
{
}
