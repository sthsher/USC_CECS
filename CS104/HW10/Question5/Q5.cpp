#include <iostream>
#include <fstream>
#include <cmath>
#include "Q5hashTable.h"

using namespace std;

int main()
{
	ifstream fin;
	fin.open("Q5_input.txt");

	int numOfTurkey = 0;
	int numOfSides = 0;
	int target = 0;

	fin >> numOfTurkey;
	fin >> numOfSides;
	fin >> target;

	hashTable<int> turkeyTable(target);

	for (int i = 0; i < numOfTurkey; ++i)
	{
		int cal;
		fin >> cal;

		//If calorie of the dish is larget than target, then ignore.
		//There cannot be a dish with negative calories
		if (cal > target)
		{	}
		else
		{
			turkeyTable.add(cal);
		}
	}

	bool isSolution = false;

	for (int i = 0; i < numOfSides; ++i)
	{
		int cal;
		fin >> cal;

		try
		{
			turkeyTable.get(cal);

			//will only reach this line if solution is found
			isSolution = true;
			cout << target << " = " << turkeyTable.get(cal) << " + " << cal << endl;

		} 
		catch(logic_error & e)
		{	}	//don't really want to do anything, just keep going


	}

	if (!isSolution)
	{
		cout << endl << "No Combination Available" << endl << endl;
	}



	cout << "---Program End---" << endl;
	return 0;


}