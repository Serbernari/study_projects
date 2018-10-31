#include "DenseMatrix.h"

using namespace std;
//input from file
DenseMatrix::DenseMatrix(string path, int n) 
{
	size = n;
	A = new real*[size];
	for (int i = 0; i < size; ++i) A[i] = new real[size];
	  ifstream f; f.open(path);
	for (int i = 0; i < size; ++i) 
	{
		for (int j = 0; j < size; ++j) 
			f >> A[i][j];
	}

}

void DenseMatrix::gaussMethod(real* b) 
{
	//solution will be there
	real* x = new real[size];
	real* f = b;

	int pos = -1;
	//i-element of massive shows what line should be next in Gauss-method
	int* line_sequence = new int[size];
	//counter for line_sequence
	int countElem = 0;
	real del;
	real coeff;
	bool lineWasUsed = 0;

	//reduction to upper triangular view
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (pos == -1) {
				if (A[j][i] != 0.0) {
					for (int l = 0; l < countElem && !lineWasUsed; ++l) {
						if (line_sequence[l] == j) lineWasUsed = 1;
					}
					if (!lineWasUsed) {
						pos = j;
						del = A[j][i];
						line_sequence[countElem] = j;
						++countElem;
					}
					lineWasUsed = 0;
				}
			}
			else {
				if (A[j][i] != 0) {
					coeff = A[j][i] / del;
					for (int k = i; k < size; k++) {
						A[j][k] = A[j][k] - (A[pos][k] * coeff);
					}
					f[j] = f[j] - f[pos] * coeff;
				}
			}
		}
		pos = -1;
	}


	//reduction to lead elementd
	for (int i = 0; i < size; ++i) {
		del = A[i][i];
		f[i] = f[i] / A[i][i];
		for (int j = i; j < size; ++j) {
			A[i][j] = A[i][j] / del;
		}
	}

	//resolve equations
	int countX = 0;
	for (int step = 9; step >= 0; --step) { 
		int j = line_sequence[step];
		real sum = 0;
		for (int i = size - 1; i >= step; --i) {
			if (i == step) {
				x[i] = (f[i] - sum) / A[j][i];
			}
			else {
				sum += x[i] * A[j][i];
			}
		}
	}

	for (int i = 0; i < size; ++i) {
		printf("%.16f\n", x[i]);
	}

}

