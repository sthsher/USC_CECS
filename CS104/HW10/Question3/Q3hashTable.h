#ifndef hashTable_H_
#define hashTable_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <cmath>


using namespace std;

template <class keyT, class valueT>
struct node
{
	keyT key;
	valueT value;
	node<keyT, valueT>* nextNode;
	node<keyT, valueT>* prevNode;
};



template <class keyT, class valueT>
class hashTable: private vector< node<keyT, valueT>* >
{
	public:
		hashTable ();
		~hashTable();

		void add (const keyT & addKey, const valueT & addValue);
		void remove(const keyT & removeKey);
		valueT get (const keyT & getKey);

		void print();

	private:
		double numOfEntries;
		int tableSize;
		int indexValue(int value);

		void rehash();


};

#include "Q3hashTable.hpp"



#endif //hashTable_H_