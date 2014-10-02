#ifndef quickSort_H_
#define quickSort_H_

#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
class quickSort
{
	public:
		quickSort(T array[], int size);
		~quickSort();
		void sortArray(T array[], int size);

	private:
		void qSort(T array[], int left, int right);
		void swap(T array[], int i, int j);
		void merge (T arrayp[], int left, int right, int mid);
		void mergeSort (T array[], int left, int right);
		int partition (T array[], int left, int right);
		void printArray (int *array, int l, int r, int m);
	

};

#include "quickSort.hpp"

#endif //quickSort_H_