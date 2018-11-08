#include "inf_int.h"

int main()
{
	std::string way = "D:/GitHub/study_projects/Cryptography/Task#2/Diffie-Hellman-Merkle/first_number.txt";
	inf_int a(&way);
	inf_int b;
	b.storage.push_back(2);
	inf_int c;
	inf_int d;

	c = inf_int::pow(a, 1000);

	return 0;
}