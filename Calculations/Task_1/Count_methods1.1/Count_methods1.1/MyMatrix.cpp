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
			height = diag.size();
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
			width = tmp_vector.size() / height;
			std::vector<double> tmp_vec2;

			for (int line = 0; line < height; ++line)
			{
				for (int i = 0; i < width; ++i)
				{
					tmp_vec2.push_back(tmp_vector[width*line + i]);
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
			//width = tmp_vector.size() / height;
			std::vector<double> tmp_vec2;

			for (int line = 0; line < height; ++line)
			{
				for (int i = 0; i < width; ++i)
				{
					tmp_vec2.push_back(tmp_vector[width*line + i]);
				}
				upper.push_back(tmp_vec2);
				tmp_vec2.clear();
			}
			break;
		}
	}
	input3.close();
}

MyMatrix::~MyMatrix()
{
}

