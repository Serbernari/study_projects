#pragma once
//infinite length int
#include <iostream>
#include <vector>

class inf_int
{
public:

const inf_int& operator+(inf_int& i); //разобраться с перегрузкой и ссылками
const inf_int& operator-(const inf_int& i);
const inf_int operator*(inf_int& i);
const inf_int& operator/(const inf_int& i);
const inf_int& pow (inf_int& a, const inf_int& b);

static inf_int pow(inf_int a, const int b);

inf_int karatsuba_mul(const inf_int & A, const inf_int & B);

    inf_int();
	inf_int(unsigned long long size);
	inf_int(std::string* f_diag);
	~inf_int();


	inf_int naitive_mul(inf_int* A, inf_int* B);
	std::vector<short unsigned int> storage; //as long as one symbol {0,1...9} is 8 bit we should use char. Or shouldn't we?...
};

