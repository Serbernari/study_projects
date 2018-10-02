#include "MyMatrix.h"


MyMatrix::MyMatrix() //default constructor
{
}

MyMatrix::MyMatrix(std::string* f_diag, std::string* f_lower, std::string* f_upper)
{
	double tmp_double;
	std::ifstream input1(*f_diag); 
	while (true)
	{
		input1 >> tmp_double;
		diag.push_back(tmp_double);
		if (input1.eof()) {
			diagSize = diag.size();
			break;
		}
	}
	input1.close();

	std::ifstream input2(*f_lower); 
	std::vector<double> tmp_vector;
	while (true)
	{
		input2 >> tmp_double;
		tmp_vector.push_back(tmp_double);
		if (input2.eof())
		{
			lowerWidth = tmp_vector.size() / diagSize;
			std::vector<double> tmp_vec2;

			for (int line = 0; line < diagSize; ++line)
			{
				for (int i = 0; i < lowerWidth; ++i)
				{
					tmp_vec2.push_back(tmp_vector[lowerWidth*line + i]);
				}
				lower.push_back(tmp_vec2);
				tmp_vec2.clear();
			}
			break;
		}
	}
	input2.close();

	std::ifstream input3(*f_upper); 
	tmp_vector.clear();
	while (true)
	{
		input3 >> tmp_double;
		tmp_vector.push_back(tmp_double);
		if (input3.eof())
		{
			upperWidth = tmp_vector.size() / diagSize;
			std::vector<double> tmp_vec2;

			for (int line = 0; line < diagSize; ++line)
			{
				for (int i = 0; i < upperWidth; ++i)
				{
					tmp_vec2.push_back(tmp_vector[upperWidth*line + i]);
				}
				upper.push_back(tmp_vec2);
				tmp_vec2.clear();
			}
			break;
		}
	}
	input3.close();
}

bool MyMatrix::buildInOne()
{
	mat = lower;
	for (int i = 0; i < diag.size(); ++i)
	{
		mat[i].push_back(diag[i]);
		mat[i].insert(mat[i].end(), upper[i].begin(), upper[i].end());
	}
	return 0;
}

double MyMatrix::getElem(int i, int j)
{
	if (((i < j) && ((j - i) <= lowerWidth)) || ((i > j) && (i - j) <= upperWidth)) //если лежит в пределах записанного
	{
		return(mat[i][j - i + lowerWidth + 1]);
	}
	else return 0.0; //сделать ограничение по вылезанию за массив if ((i > diag.size()) || (j > diag.size()) exception
}

MyMatrix::~MyMatrix()
{
}

unsigned MyMatrix::get_width()
{
	return 0;
}
