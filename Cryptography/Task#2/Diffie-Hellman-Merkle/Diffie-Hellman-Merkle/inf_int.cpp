#include "inf_int.h"
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace::std;

//делать таки как у хохлушки, куча блоков размером int в количестве int штук, иначе смысла нет же

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

const inf_int & inf_int::operator*( inf_int & b)
{
		auto len = this->storage.size();
		inf_int res(2 * len);
		
		auto k = len / 2;
		inf_int Xr(k);
		std::copy(this->storage.begin(), this->storage.begin() + k,
			std::back_inserter(Xr.storage));
		inf_int Xl(k);
		std::copy(this->storage.begin() + k, this->storage.end(),
			std::back_inserter(Xl.storage));
		inf_int Yr(k);
		std::copy(b.storage.begin(), b.storage.begin() + k,
			std::back_inserter(Yr.storage));
		inf_int Yl(k);
		std::copy(b.storage.begin() + k, b.storage.end(),
			std::back_inserter(Yl.storage));
				
		inf_int P1 = Xl * Yl;
		inf_int P2 = Xr * Yr;

		inf_int Xlr(k);
		inf_int Ylr(k);

		for (int i = 0; i < k; ++i) {
			Xlr.storage[i] = Xl.storage[i] + Xr.storage[i];
			Ylr.storage[i] = Yl.storage[i] + Yr.storage[i];
		}

		inf_int P3 = Xlr * Ylr;

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
	
	// TODO: вставьте здесь оператор return
}

const inf_int & inf_int::operator/(const inf_int & i)
{
	return i;
	// TODO: вставьте здесь оператор return
}

const inf_int & inf_int::pow(inf_int & a, const inf_int & b)
{
	return a;
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
	storage.reserve(sizeof(char) * size);
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
