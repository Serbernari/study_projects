#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void buildKey(vector<char>* myText, vector<char>* key)
{
	std::vector<unsigned long long> statistics(32); //statistics[0] is a, statistics[1] is б and so on
	for (unsigned long long i = 0; i < myText->size(); ++i)
	{
		++statistics[(*myText)[i] + 32];
	}

	int iter[32] = { 14, 5, 0, 8, 13, 18, 17, 16, 2, 11, 10, 12, 4, 15, 19,
				  31, 27, 28, 3, 7, 1, 23, 9, 21, 6, 24, 30, 22, 25, 29, 20, 26 }; //буквы по частоте 

	for (int j = 0; j < 32; ++j)
	{
		auto maxElem = max_element(statistics.begin(), statistics.end());
		(*key)[iter[j]] = (distance(statistics.begin(), maxElem) - 32);
		*maxElem = 0;
    }



}

void decodeIt(vector<char>* myText, vector<char>* key)
{
	buildKey(myText, key);

	char Alphabet[] = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
	int pos;

	for (unsigned long long i = 0; i < myText->size(); ++i)
	{
		//if (((*myText)[i] >= 'а') || ((*myText)[i] <= 'я')) //we don't need it if input text formated
		{
			pos = distance(key->begin(), find(key->begin(), key->end(), (*myText)[i]));
			(*myText)[i] = Alphabet[pos];
		}
	}
}

int main()
{
	ifstream input; //open encoded text
	input.open("d:\\InputEncoded.txt");
	std::vector<char> myText;

	while (true)
	{
		char n;
		input >> n;
		if (input.eof()) break;
		myText.push_back(n);
	}

	ifstream keyFile; // open key
	keyFile.open("d:\\Key.txt");
	std::vector<char> myKey(32);

	/*while (true)
	{
		char n;
		keyFile >> n;
		if (keyFile.eof()) break;
		myKey.push_back(n);
	}*/

	decodeIt(&myText, &myKey); // decoding

	std::ofstream fout;
	fout.open("d:\\OutputDecoded.txt");
	for (const auto &e : myText) fout << e; 
	fout.close();
	
	return 0;
}

