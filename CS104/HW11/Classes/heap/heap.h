#ifndef heap_H_
#define heap_H_

#include "../listLibrary/arrayLists/doubleSizeArray.h"
#include <stdexcept>
#include <cmath>
#include <functional>

using namespace std;

template <class T>
class heap
{
	public:
		heap (int d, bool maxHeap);
		~heap ();

		T & peek () const;
		void remove (bool(*compareFunction)(T, T));
		void add (const T &item, bool(*compareFunction)(T, T));

		//for debuggin only
		//void printHeap() const;

	private:
		bool isMax;
		int factor;
		doubleSizeArray<T> *arrayPtr;
		int size;

		void swap (int indexA, int indexB);

		int largestChildIndex(T* childArray, int arraySize, int firstIndex, bool(*compareFunction)(T, T));
		int smallestChildIndex(T* childArray, int arraySize, int firstIndex, bool(*compareFunction)(T, T));

		void trickleDown(int currentNode, bool(*compareFunction)(T, T));
		void trickleUp(int currentNode, bool(*compareFunction)(T, T));


		bool checkLeaf(int node);
};

#include "heap.hpp"

#endif //heap_H_