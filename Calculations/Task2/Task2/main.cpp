#include "Matrix.h"

int main() {
	setlocale(LC_CTYPE, "Russian");
	ifstream size("size.txt");
	ifstream matrix("matrix.txt");
	ifstream vector("vector.txt");
	ofstream result("result.txt");
	Matrix M(size, matrix, vector);
	int flag = 1;
	M.iteration(result, flag);
	system("pause");
	return 0;
}
