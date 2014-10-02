#include <iostream> 
#include <fstream>
#include <string>
#include "quickSort/quickSort.h"
#include "stringAndFrequency.h"

using namespace std;


int main()
{
	ifstream fin;
	fin.open("Q3_text_file.txt");

	int size;
	fin >> size;

	string* array = new string[size];

	for (int i = 0; i < size; ++i)
	{
		string temp;
		fin >> temp;
		array[i] = temp;
	}

	quickSort<string> qSort(array, size);

	stringAndFrequency* safArray = new stringAndFrequency[size];
	int safSize = 0;

	int frequencyCount = 0;
	int highestFrequency = 1;

	for (int i = 0; i < size; ++i)
	{
		if (i == 0)
		{
			//first one, increase count
			++frequencyCount;
		}
		else if (array[i] == array[i-1])
		{
			++frequencyCount;
		}
		else if (array[i] != array[i-1])
		{
			//different string. create object
			stringAndFrequency temp(array[i-1], frequencyCount);
			safArray[safSize++] = temp;
			if (frequencyCount > highestFrequency)
				highestFrequency = frequencyCount;
			//reset count to 1 since array[i] right now is the first instance
			frequencyCount = 1;
		}
		if (i == size-1)
		{
			//last item
			if (frequencyCount > highestFrequency)
				highestFrequency = frequencyCount;
			stringAndFrequency temp(array[i], frequencyCount);
			safArray[safSize++] = temp;
		}
	}
/*
	for (int i = 0; i < size; ++i)
	{
		cout << array[i] << "  ";
	}

	cout << endl;
*/

/*
	for (int i = 0; i < safSize; ++i)
	{
		cout << safArray[i].getContent() << "  " << safArray[i].getFrequency() << endl;
	}
*/

	cout << endl << "The words with the highest frequency count (" << highestFrequency << ") is: " << endl;

	for (int i = 0; i < safSize; ++i)
	{
		if (safArray[i].getFrequency() == highestFrequency)
		{
			cout << "     " << safArray[i].getContent() << endl;
		}
	}

	//cout << "highest frequency: " << highestFrequency << endl;

	cout << endl << "---Program End---" << endl;

	return 0;
}