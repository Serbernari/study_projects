#include <iostream>
#include <fstream>
#include <string>
#include "MyMatrix.h"
#include "MatrixMath.h"

using namespace std;
typedef double real;

void printVec(vector<real> V, std::string* f_out)
{
	std::ofstream outFile(*f_out);
	for (const auto &e : V) outFile << e << "\n";
}

int main()
{
	std::string *f_diag = new string, *f_lower = new string, *f_upper = new string, *f_out = new string;
	*f_diag = "D:/GitHub/study_projects/Calculations/Task1_files/f_diag.txt";
	*f_lower = "D:/GitHub/study_projects/Calculations/Task1_files/f_lower.txt";
	*f_upper = "D:/GitHub/study_projects/Calculations/Task1_files/f_upper.txt";
	*f_out = "D:/GitHub/study_projects/Calculations/Task1_files/f_out.txt";
	
/*
	MyMatrix testMatrix(f_diag, f_lower, f_upper);
	makeDetNotZero(&testMatrix, 10);
	vector<real> testVec = { -4.0, 1.0, -2.0, -3.0, 4.0};
	//vector<real> testVec = { 1.0, 2.0, 3.0};

	LU_dec(&testMatrix);
	forward_sol(testMatrix, testVec);
	std::vector<double> x = backward_sol(testMatrix, testVec);
	printVec(x, f_out);
	*/
	MyMatrix A = HilbertMat(4);

	vector<double>f = { 4.0, 2.716667, 2.1, 1.721429};
	LU_dec(&A);
	f = forward_sol(A, f);
	std::vector<double> x2 = backward_sol(A, f);
	printVec(x2, f_out);

	return 0;
}