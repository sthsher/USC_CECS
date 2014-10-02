#include <iostream> 
#include <fstream>
#include <string>
#include "quickSort/quickSort.h"

using namespace std;

bool binarySearch (int array[], int target, int left, int right)
{
	if (right < left)
	{
		return false;
	}
	else
	{
		int mid = (left + right)/2;
		if (array[mid] > target)
		{
			return binarySearch(array, target, left, mid-1);
		}
		else if (array[mid] < target)
		{
			return binarySearch(array, target, mid+1, right);
		}
		else if (array[mid] == target)
		{
			return true;
		}
	}
}

int main()
{
	ifstream fin;
	fin.open("Q4_text_file.txt");

	int size;
	fin >> size;

	int target;
	fin >> target;

	int* array = new int[size];

	for (int i = 0; i < size; ++i)
	{
		int temp;
		fin >> temp;
		array[i] = temp;
	}

	quickSort<int> sort(array, size);

	//get rid of repeats
	int newSize = 0;
	for (int i = 1; i < size; ++i)
	{
		if (array[i] > target)
			break;
		if (array[i] != array[i-1])
		{
			array[newSize++] = array[i];
		}
	}

	bool foundAnswer = false;
	int numA, numB;

	for (int i = 0; i < newSize; ++i)
	{
		int difference = target - array[i];
		foundAnswer = binarySearch(array, difference, 0, newSize);
		if (foundAnswer)
		{
			numA = array[i];
			numB = difference;
			break;
		}
	}

	cout << endl;

	if (foundAnswer)
	{
		cout << target << " = " << numA << " + " << numB << endl;
	}
	else
	{
		cout << "No valid result found" << endl;
	}

	cout << endl << "---Program End---" << endl;

	return 0;
}