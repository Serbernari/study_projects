#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
typedef double real;

class MyMatrix
{
public:
	std::vector<real> diag;
	std::vector<std::vector<real>> lower, upper; //2 matrix

	unsigned height, width;

	MyMatrix();//standard constructor

	MyMatrix(std::string * f_diag, std::string * f_lower, std::string * f_upper);

	~MyMatrix();
};

