#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>


class MyMatrix
{
public:
	std::vector<double> diag;
	std::vector<std::vector<double>> lower, upper; //3 matrix
	std::vector<std::vector<double>> mat;

	unsigned lowerWidth, upperWidth, diagSize;

	MyMatrix();//standard constructor

	MyMatrix(std::string * f_diag, std::string * f_lower, std::string * f_upper);
	bool buildInOne();
	//make matrix from files

	double getElem(int i, int j);
	double getLElem(int i, int j);
	double getUElem(int i, int j);
	void setL(int i, int j, double value);
	void setUElem(unsigned i, unsigned j, double value);

	~MyMatrix();


protected:

	unsigned get_width();
};

