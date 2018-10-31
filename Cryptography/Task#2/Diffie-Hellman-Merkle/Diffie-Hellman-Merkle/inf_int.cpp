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

const inf_int & inf_int::operator*(const inf_int & i)
{
	return i;
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
