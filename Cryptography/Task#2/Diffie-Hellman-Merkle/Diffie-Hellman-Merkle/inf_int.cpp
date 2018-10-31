#include "inf_int.h"
#include <fstream>
#include <iterator>
using namespace::std;

const inf_int & inf_int::operator+(inf_int & i)
{
	i.storage[0] = 7;
	return i;
	// TODO: вставьте здесь оператор return
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
