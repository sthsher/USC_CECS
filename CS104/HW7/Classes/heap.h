#ifndef heap_H_
#define heap_H_

#include "listLibrary/pureList.h"
#include <cmath>

using namespace std;

template <class T>
class heap
{
	public:
		heap (int d, bool maxHeap);
		~heap ();

		T & peek () const;
		void remove ();
		void add (const T &item);

		//for debuggin only
		//void printHeap() const;

	private:
		bool isMax;
		int factor;
		pureList<T> *arrayPtr;
		int size;

		void swap (int indexA, int indexB);

		int largestChildIndex(T* childArray, int arraySize, int firstIndex);
		int smallestChildIndex(T* childArray, int arraySize, int firstIndex);

		void trickleDown(int currentNode);
		void trickleUp(int currentNode);


		bool checkLeaf(int node);
};

#include "heap.hpp"

#endif //heap_H_