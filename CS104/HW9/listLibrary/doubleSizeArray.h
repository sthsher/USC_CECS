#ifndef doubleSizeArray_H_
#define doubleSizeArray_H_

#include <iostream>

using namespace std;

template <class T>
class doubleIterator;

template <class T>
class doubleSizeArray
{
	public:
		doubleSizeArray();
		doubleSizeArray(T initial);
		~doubleSizeArray();

		void insert (int pos, const T & item);
		void remove (int pos);
		void set (int pos, const T & item);
		T const & get (int pos) const;
		bool isEmpty()const;
		void clear();

		//Iterator stuff
		T* returnStartPtr();

		doubleIterator<T> begin();		//returns an iterator at beginning of array
		doubleIterator<T> end();		//returns an iterator at the end of the array

		int returnSize();
		int returnNumOfElements();

		friend class doubleIterator<T>;

	private:

		T* arrayPtr;
		int size;
		int numOfElements;
		
		void extendArray();
			/* Extends the array */
};

template <class T>
class doubleIterator
{
	public:
		doubleIterator<T>();
		doubleIterator<T>(doubleSizeArray<T> *ptr);
		~doubleIterator<T>();

		//pass in the array you wish to iterate
		void setArrayID(doubleSizeArray<T> *ptr);

		//getting back a T pointer
		T * operator*() const;
		doubleIterator<T> operator++();
		bool operator==(const doubleIterator<T> &other);
		bool operator!=(const doubleIterator<T> &other);

	private:
		T *currentPtr;					//returns pointer of T
		int pos;
		doubleSizeArray<T> *arrayID;

};

#include "doubleSizeArray.hpp"

#endif //doubleSizeArray_H_