#ifndef hashTable_H_
#define hashTable_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <cmath>


using namespace std;

template <class T>
struct node
{
	T content;
	node* nextNode;
	node* prevNode;
};

template <class T>
class hashTable: private vector< node<T>* >
{
	public:
		hashTable (int t);
		~hashTable();

		void add (const T & addItem);
		void remove(const T & removeItem);
		T get (const T & getItem);


		void print();


	private:
		double numOfEntries;
		int tableSize;
		int indexValue(int value);

		void rehash();

		int target;


};

#include "Q5hashTable.hpp"



#endif //hashTable_H_