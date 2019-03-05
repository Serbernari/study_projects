#include "variable_table.h"

int main()
{
	const_table<string> string_t("table2.txt");

	bool check1 = string_t.is_element_in_table("int");// проверка наличия типа int в постоянной таблице, true, ok

	int n0;
	string_t.get_elemen_number("int", n0);
	string get_s;
	string_t.get_elemen_value(n0, get_s);

	variable_table vars_t;
	vars_t.add_ind("a");
	vars_t.add_ind("b");
	vars_t.add_ind("aab");

	bool check2 = vars_t.add_ind("a"); //попытка добавить уже наличиествующий, false, ok

	bool check3 = vars_t.check_ind_in_table("aab"); //проверка на наличие наличиествующего, true, ok
	bool check4 = vars_t.check_ind_in_table("c"); //проверка на наличие отсутствующего идентификатора - false, ок

	int n1, n2;
	vars_t.ind_adrress("b", n1, n2);

	vars_t.set_ind_type("a", 1);
	vars_t.set_ind_val("aab", true);

	lexeme t1, t2;
	vars_t.get_lexeme("aab", t1);
	vars_t.get_lexeme(n1, n2, t2);

	vars_t.set_type_address(n1, n2, 3);
	vars_t.set_value_address(n1, n2, true);

	return 0;
}