#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

void formatText(vector<char>* myText)  //
{
	int spaceSkip = abs('A' - 'a');
	for (int i = 0; i < myText->size(); ++i)
	{
		if (((*myText)[i] >= 'À') && ((*myText)[i] <= 'ß'))//change capital letters to small ones
			(*myText)[i] += spaceSkip;
		else if ( ((*myText)[i] < 'à') || ((*myText)[i] > 'ÿ') ) //delete symbol if it's not a letter
		{
			myText->erase(myText->begin() + i);
			--i;
		}
	}
}

void makeKey(vector<char>* key)
{
	for (int i = 0; i < 32; ++i) // itteration on 32 russian alphabet letters (all except " ¸ ")
		(*key)[i] = 'à' + i;

	std::random_device rd;
	std::mt19937 g(rd()); //generator of pseudo-random 32-bit numbers with a state size of 19937 bits.

	std::shuffle(key->begin(), key->end(), g);
}

void encrypteIt(vector<char>* myText, vector<char>* key)
{
	formatText(myText);
	makeKey(key);

	for (unsigned long long i = 0; i < myText->size(); ++i)
	{
		if (((*myText)[i] >= 'à') || ((*myText)[i] <= 'ÿ')) 
		{
			(*myText)[i] = (*key)[(*myText)[i] + 32]; //32 is differece between code of letter
					 //and it number in alphabet array, e.g. 'a'= -32 and a is #0 in alphabet
		}
	}
}

int main()
{
	vector <char> key(32);
	ifstream input;
	input.open("D:\\coderinput.txt");

	std::vector<char> myText;

	while (true)
	{
		char n;
		input >> n;
		if (input.eof()) break;
		myText.push_back(n);
	}
	encrypteIt(&myText, &key);

	input.close();

	std::ofstream fkey;
	fkey.open("D:\\Key.txt");
	for (const auto &e : key) fkey << e; //???
	fkey.close();

	std::ofstream fout;
	fout.open("D:\\encodedoutput.txt");
	for (const auto &e : myText) fout << e; //???
	fout.close();



	return 0;
}

