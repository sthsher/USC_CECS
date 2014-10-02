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
		hashTable (int s);
		~hashTable();

		void add (const keyT & addKey, const valueT & addValue);
		void remove(const keyT & removeKey);
		valueT get (const keyT & getKey);


		void print();

		//for question 4
		void printHighestFrequency(int size);



	private:
		double numOfEntries;
		int tableSize;
		int indexValue(int value);

		void rehash();

		//for question 4
		int highestFrequency;


};

#include "Q4hashTable.hpp"



#endif //hashTable_H_