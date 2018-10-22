#pragma once
#include <fstream>
#include "MatrixMath.h"
#include "MyMatrix.h"
typedef double real;

using namespace std;
class DenseMatrix
{
private:
	real **A;
	int size;
public:
	DenseMatrix(string path, int n);
	void gaussMethod(real* b);

};

