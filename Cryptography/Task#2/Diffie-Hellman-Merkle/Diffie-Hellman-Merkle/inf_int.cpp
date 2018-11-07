#include "inf_int.h"
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace::std;

const inf_int & inf_int::operator+(inf_int & b)
{
	// определяем длину массива суммы
	if (this->storage.size() > b.storage.size())
	{
		const long long difference = this->storage.size() - b.storage.size();
		for (int i = 0; i <= difference; ++i)
		{
			this->storage[i] += b.storage[i]; // суммируем последние разряды чисел
			if (i != difference)
				this->storage[i + 1] += (this->storage[i] / 10);  // если есть разряд для переноса, переносим его в следующий разряд
			else
				this->storage.push_back(this->storage[i] / 10);
			this->storage[i] %= 10; // если есть разряд для переноса он отсекается
		}
	}
	else
	{ 
		const long long difference = b.storage.size() - this->storage.size();
		for (int i = 0; i <= difference; ++i)
		{
			this->storage[i] += b.storage[i]; // суммируем последние разряды чисел
			if (i != difference)
				this->storage[i + 1] += (this->storage[i] / 10);  // если есть разряд для переноса, переносим его в следующий разряд
			else
				this->storage.push_back(this->storage[i] / 10);
			this->storage[i] %= 10; // если есть разряд для переноса он отсекается
		}
	}
	return *this;
}

const inf_int & inf_int::operator-(const inf_int & i)
{
	return i;
	// TODO: вставьте здесь оператор return
}

inf_int naive_mul(const inf_int& x, const inf_int& y) 
{
	int len = x.storage.size();
	inf_int res(2 * len + 1);
	/*
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			res.storage[i + j] += x.storage[i] * y.storage[j];				
		}
	}*/
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			res.storage[i + j] += x.storage[i] * y.storage[j];
		}
	}
	return res;
}

void extend_storage(inf_int & A, size_t len)
{
	if (len % 2 == 0)
	{
		A.storage.resize(len);
	}
	else
	{
		A.storage.resize(len + 1);
	}
}

void finalize(inf_int& res) 
{
	for (auto i = 0; i < res.storage.size() - 1; ++i) 
	{
		res.storage[i + 1] += res.storage[i] / 10;
		res.storage[i] %= 10;
	}

	while ( res.storage.back() == 0)
		res.storage.pop_back();
}

const inf_int inf_int::operator*(inf_int & b)
{
	inf_int tmp = karatsuba_mul(*this, b);
	finalize(tmp);
	return tmp;
}

inf_int inf_int::karatsuba_mul(const inf_int & A, const inf_int & B) 
{
	inf_int a = A;
	inf_int b = B;

	auto len_change = max(a.storage.size(), b.storage.size());
	extend_storage(a, len_change);
	extend_storage(b, len_change);

	auto len = a.storage.size();
	inf_int res(2 * len);

	if (len <= 2) //magic const
	{
		res = naive_mul(a, b);
		return res;
	}

	auto k = len / 2;

	inf_int Xr;
	Xr.storage = { a.storage.begin(), a.storage.begin() + k };
	inf_int Xl;
	Xl.storage = { a.storage.begin() + k, a.storage.end() };
	inf_int Yr;
	Yr.storage = { b.storage.begin(), b.storage.begin() + k };
	inf_int Yl;
	Yl.storage = { b.storage.begin() + k, b.storage.end() };

	inf_int P1(len);
	P1 = karatsuba_mul( Xl, Yl); // i dunno wtf orerator* wasnt working.
	inf_int P2(len);
	P2 = karatsuba_mul (Xr, Yr);

	inf_int Xlr(k);
	inf_int Ylr(k);

	for (int i = 0; i < k; ++i) {
		Xlr.storage[i] = Xl.storage[i] + Xr.storage[i];
		Ylr.storage[i] = Yl.storage[i] + Yr.storage[i];
	}

	inf_int P3(len);
	P3 = karatsuba_mul(Xlr , Ylr);
	 
	for (auto i = 0; i < len; ++i) {
		P3.storage[i] -= P2.storage[i] + P1.storage[i];
	}

	for (auto i = 0; i < len; ++i) {
		res.storage[i] = P2.storage[i];
	}

	for (auto i = len; i < 2 * len; ++i) {
		res.storage[i] = P1.storage[i - len];
	}

	for (auto i = k; i < len + k; ++i) {
		res.storage[i] += P3.storage[i - k];
	}

	return res;
}

const inf_int & inf_int::operator/(const inf_int & i)
{
	return i;
	// TODO: вставьте здесь оператор return
}

const inf_int & inf_int::pow(inf_int & a, const inf_int & b)
{
	//while i'll do this later
	return a;
}

inf_int  inf_int::pow(inf_int a, int b)
{
	/*inf_int res; //�����-����� �����
	res.storage.push_back(1);
		for (int i = b; i > 0; --i)
		{
			res = res * a;
		}
	return res;*/
	
	inf_int res;
	res.storage.push_back(1);//
	extend_storage(res, a.storage.size() *  b);
	while (b)
	{
		if (b % 2 == 0)
		{
			b /= 2;
			a = a * a;
	    }		
		else
		{
			--b;
			res = res * a;
		}
	}
	return res;
}

/*
inf_int::inf_int()//reading number fron external file
{

}*/


inf_int::inf_int()
{
}

inf_int::inf_int(unsigned long long size)
{
	while (size != 0)
	{
		storage.push_back(0);
		--size;
    }
}

inf_int::inf_int(std::string* f_input)
{
	std::ifstream input(*f_input); // i dont watr to read char by char :( I want it all in one!
	try 
	{
		if (input.is_open() == 0)
		{
			throw 404;
		}
		char tmp;
		while (input >> tmp)
		{
			storage.push_back(tmp);
			storage.back() -= '0';
		}
		input.close();
		reverse(std::begin(storage), std::end(storage));
		/*std::copy(std::istream_iterator<char>(input),
	    		  std::istream_iterator<char>(),
				  std::back_inserter(storage));
		input.close();*/

	}
	catch (int err)
	{
		cout << "Can not open file" << endl;
	}
	
 
}

inf_int::~inf_int()
{
}
