#pragma once
//infinite length int
#include <iostream>
#include <vector>

class inf_int
{
public:

const inf_int& operator+(const inf_int& i); //разобраться с перегрузкой и ссылками
const inf_int& operator-(const inf_int& i);
const inf_int& operator*(const inf_int& i);
const inf_int& operator/(const inf_int& i);
const inf_int& pow (inf_int& a, const inf_int& b);

    inf_int();
	inf_int(std::string* f_diag);
	~inf_int();

private:
	std::vector<char> storage; //as long as one symbol {0,1...9} is 8 bit we should use char. Or shouldn't we?...
};

