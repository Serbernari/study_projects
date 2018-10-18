#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>


class MyMatrix
{
public:
	std::vector<double> diag;
	std::vector<std::vector<double>> lower, upper; //2 matrix

	unsigned height, width;

	MyMatrix();//standard constructor

	MyMatrix(std::string * f_diag, std::string * f_lower, std::string * f_upper);

	~MyMatrix();
};

