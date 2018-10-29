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
	

	MyMatrix testMatrix(f_diag, f_lower, f_upper);
	//vector<real> testVec = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
	vector<real> testVec = { 1.0, 2.0, 3.0};
/*
	LU_dec(&testMatrix);
	forward_sol(testMatrix, testVec);
	std::vector<double> x = backward_sol(testMatrix, testVec);*/

	MyMatrix A = HilbertMat(3);

	MyMatrix B = HilbertMat(10);
	vector<double>f = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
	LU_dec(&B);
	forward_sol(B, f);
	std::vector<double> x2 = backward_sol(B, f);
	printVec(x2, f_out);
	// умножение чек
	// узнать доп.задание
	// сделать вывод
	// сделать testvec с помощью matOnVec как белый человек
	return 0;
}