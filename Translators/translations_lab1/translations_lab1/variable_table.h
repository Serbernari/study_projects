#pragma once

#include "const_table.h"
#include <vector>

//Storage variable tables as hash-tables
//Realization by using hash-tables with chains, Hashing is preforming on first character of identifier
const int hash_N = 26 * 2 + 10; //max hash value
class variable_table
{
public:
	variable_table()
	{
		my_table = new vector<lexeme>[hash_N];
	}

	~variable_table()
	{
		for (int i = 0; i < hash_N; i++)
			my_table[i].clear();
		delete[] my_table;
	}

	bool add_ind(string ind_name); //Adiing identifier
	bool set_ind_type(string ind_name, int type); //Adding value to type of identifier
	bool set_ind_val(string ind_name, bool val); //changing type of indentifire's initialization
	bool check_ind_in_table(string ind_name); //checking presence of identifire in table
	bool ind_adrress(string ind_name, int& hash, int& numb); //get full adress of identifier
	bool get_lexeme(string ind_name, lexeme& gets_lexeme); //get token by identifier
	bool get_lexeme(int hash, int numb, lexeme& gets_lexeme); //get token by it's full adress
	bool set_type_address(int hash, int numb, int type); //Set type by full adress
	bool set_value_address(int hash, int numb, bool val); //Set value by full adressУ
	
	//сделать отдельный класс для констант только поиск и добавление, не лексемы а цепочек (цепочка содержит строки)

private:

	vector<lexeme> *my_table; 

	int calc_hash(string ind_name);	//Hash calculation. first - numbers, then - lower case letters, then - upper case
	int find_in_vector(int hash, string ind_name);
};