#include <iostream>
#include <string>
#include "Q6hashTable.h"
#include "word.h"
#include <stdexcept>
#include <fstream>

using namespace std;



int main()
{

	ifstream fin;
	fin.open("Q6_input.txt");

	int size;
	fin >> size;

	string* stringArray = new string[size];

	//string stores the word, int stores the line it exists on
	hashTable<word, int> googleTable(size*60);

	//get empty value
	string dump;
	getline (fin, dump);

	for (int i = 0; i < size; ++i)
	{
		string line;
		getline(fin, line);

		stringArray[i] = line;

		// do string analysis and add individual words into the hashtable
		int stringSize = line.size();

		int lineIndex = 0;
		int wordIndex = 0;

		string subWord;

		int startingPos = 0;
		int subSize = 0;

		for (int j = 0; j < stringSize+1; ++j)
		{
			if (line[j] == ' ' || j == stringSize)
			{
				subSize = j-startingPos;
				subWord = line.substr(startingPos, subSize);

				//add subword
				word newWord(subWord);
				//cout << newWord.content << "  ";

				googleTable.add(newWord, i);

				//++ to skip space
				startingPos = ++j;
			}
		}

	}

	// googleTable.print();

	while (true)
	{
		string query;

		cout << "-------------------------------------------------" << endl;
		cout << "  Welcome to Stephen's Mini-Google Seach Engine  " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Enter \"IWantToQuitStephen'sSearchEngine\" anytime to exit the program" << endl;
		cout << "Please enter a search query: "; cin >> query; cout << endl;

		if (query == "IWantToQuitStephen'sSearchEngine" ||
			query == "iwanttoquitstephen'sserachengine")
		{
			break;
		}

		else
		{
			try
			{
				word searchWord(query);
				googleTable.get(searchWord, stringArray);
			}
			catch(const logic_error & e)
			{cout << e.what() << endl << endl;}
		}

		
	}


	cout << "---Program End---" << endl;

	return 0;
}