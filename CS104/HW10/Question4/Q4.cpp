#include <iostream>
#include <string>
#include "Q4hashTable.h"
#include "food.h"
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;



int main()
{

	ifstream fin;
	fin.open("Q4_input.txt");

	int size;
	fin >> size;

	hashTable<food, int> foodTable(size);


	for (int i = 0; i < size; ++i)
	{
		string foodName;
		fin >> foodName;

		food newFood(foodName);
		foodTable.add(newFood, 1);
	}


	foodTable.printHighestFrequency(size);
	

	//run through the hash table and determine the highest frequency

	//for ()


	cout << "---Program End---" << endl;
 

	return 0;
}