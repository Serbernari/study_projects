#include "inf_int.h"

int main()
{
	std::string way = "D:/GitHub/study_projects/Cryptography/Task#2/Diffie-Hellman-Merkle/first_number.txt";
	inf_int a(&way);
	inf_int b;
	b = (a * a); //2
	b = b * a; //3

	inf_int c;
	c = inf_int::pow(a, 100);

	return 0;
}