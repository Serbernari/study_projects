#include <iostream>
#include <fstream>
#include <vector>
#include "MyMatrix.h"
#include <string>

using namespace std;

MyMatrix multiplication(MyMatrix a, MyMatrix b) //преопределить оператор
{
	MyMatrix c;
	/*
	задаем размеры соотв. векторов
	*/
	return c;
}

int main()
{
	std::string *f_diag = new string, *f_lower = new string, *f_upper = new string;
	*f_diag = "D:/GitHub/Calculations/Task1_files/f_diag.txt";
	*f_lower = "D:/GitHub/Calculations/Task1_files/f_lower.txt";
	*f_upper = "D:/GitHub/Calculations/Task1_files/f_upper.txt";
	
	MyMatrix testMatrix(f_diag,f_lower,f_upper);

	return 0;
}