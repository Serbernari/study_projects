#pragma once

#include <string>

using namespace std;

//programm representation of token
struct lexeme
{
	string name; //name of indentifier
	int type;
	//type of indentifier
	//0 - not defined
	//1 - int

	bool value; //initialization of indentifier 

		lexeme() {}
	lexeme(string ind_name)
	{
		name = ind_name;
		type = 0;
		value = false;
	}

	//set
	bool operator < (const lexeme& b) const
	{
		return name < b.name;
	}

	bool operator == (lexeme b)
	{
		return name == b.name;
	}
};

