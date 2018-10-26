#include <iostream>
#include <fstream>
#include <string>
#include "MyMatrix.h"
#include "MatrixMath.h"

using namespace std;
typedef double real;

int main()
{
	std::string *f_diag = new string, *f_lower = new string, *f_upper = new string;
	*f_diag = "D:/GitHub/study_projects/Calculations/Task1_files/f_diag.txt";
	*f_lower = "D:/GitHub/study_projects/Calculations/Task1_files/f_lower.txt";
	*f_upper = "D:/GitHub/study_projects/Calculations/Task1_files/f_upper.txt";

	MyMatrix testMatrix(f_diag, f_lower, f_upper);
	vector<real> testVec = { 0.0, 0.0, 0.0, 0.0, 0.0};
	//mult_MatOnVect(&testMatrix, &testVec);
	/*LU_dec(&testMatrix);
	forward_sol(&testMatrix, &testVec);
	backward_sol(&testMatrix, &testVec);*/

	MyMatrix B = HilbertMat(3);
	vector<double>f = { 1.0, 1.0, 1.0};
	//mult_MatOnVect(&B, &f);
	//LU_dec(&B);
	LU_dec(&B);
	forward_sol(&B, &f);
	backward_sol(&B, &f);
	   
	return 0;
}