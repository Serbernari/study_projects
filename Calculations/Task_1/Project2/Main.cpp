#include <iostream>
#include <fstream>
#include <vector>
#include "MyMatrix.h"
#include "MatrixMath.h"
#include <string>

using namespace std;

int main()
{
	std::string *f_diag = new string, *f_lower = new string, *f_upper = new string;
	*f_diag = "D:/GitHub/study_projects/Calculations/Task1_files/f_diag.txt";
	*f_lower = "D:/GitHub/study_projects/Calculations/Task1_files/f_lower.txt";
	*f_upper = "D:/GitHub/study_projects/Calculations/Task1_files/f_upper.txt";
	
	MyMatrix testMatrix(f_diag,f_lower,f_upper);
	vector<double> testVec = {1,1,1,1,1,1};
	mult_MatOnVect(&testMatrix, &testVec);
	return 0;
}