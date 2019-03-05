#pragma once

#include "lexeme.h"

#include <iostream>
#include <fstream>
#include <set>

//realization of constant tables 
//since we can use both strings and characters - we will use template
template <typename Table_type> class const_table
{
public:
	
	const_table() {} //default constructor
	const_table(string f_name) //generation from file
	{
		generate_from_file(f_name);
	}
	~const_table()
	{
		my_table.clear();
	}
	//Generate table from file, true if file was opend, false otherwise
	bool generate_from_file(string f_name)
	{
		ifstream file_stream(f_name.c_str()); 

		if (file_stream.is_open())
		{
			Table_type read_el; //reading single element

			while (!file_stream.eof())
			{
				file_stream >> read_el;
				my_table.insert(read_el);
			};

			file_stream.close();
			return true;
		}
		else
			return false;
	}

	//addition of single element in table
	void add_element(Table_type add_elem)
	{
		my_table.insert(add_elem);
	}
	//Checking presence of element in table
	bool is_element_in_table(Table_type check_el)
	{
		set<Table_type>::iterator el_numb = my_table.find(check_el); //finding number of elem

		return el_numb != my_table.end() ? true : false; //there is no element in table if it's number is equal to end of structure, becouse STL
	}
	//finding number of elem, false if there is no such element
	bool get_elemen_number(Table_type check_el, int& num)
	{
		if (is_element_in_table(check_el))
		{
			num = distance(my_table.begin(), my_table.find(check_el));
			return true;
		}
		else
			return false;
	}
	//geting value by number of element
	bool get_elemen_value(int num, Table_type& gets_el)
	{
		if (num >= 0 && num < my_table.size())
		{
			set<Table_type>::iterator el_iter = my_table.begin();
			for (int i = 0; i < num; i++)
				el_iter++;
			gets_el = *el_iter;
			return true;
		}
		else
			return false;
	}

private:
	set<Table_type> my_table; //table
};
