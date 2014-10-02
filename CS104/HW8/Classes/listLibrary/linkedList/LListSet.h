#ifndef LListSet_H_
#define LListSet_H_

#include <stdlib.h>
#include <iostream>

using namespace std;

//Elements
template <class T>
class LLElement
{
	public:
		LLElement();
		~LLElement();

		void setData(T s);
		void setNext(LLElement<T> *n);
		void setPrev(LLElement<T> *p);

		T returnData() const;
		LLElement<T> *returnNext();
		LLElement<T> *returnPrev();

	private:
		T data;
		LLElement<T> *next, *prev;

};

//forward declaration
template <class T>
class LLIterator;

template <class T>
class LListSet
{
	public:
		LListSet();
		~LListSet();
		void add (const T & item);
		void remove (const T & item);
		bool contains(const T & item);
		bool isEmpty();
		int returnSize() const;

		friend class LLIterator<T>;

		LLIterator<T> begin();		//returns iterator positioned at beginning
		LLIterator<T> end();		//returns iterator positioned at end

	private:
		void removePtr(LLElement<T> *p);
		LLElement<T> *startPtr, *endPtr;
		int size;

};

template <class T>
class LLIterator
{

	public:
		LLIterator<T>();
		LLIterator<T>(LListSet<T> *ptr, LLElement<T> *place);		//give the linked list and the element position for the iterator
		~LLIterator<T>();

		//pass in the array you wish to iterate
		void setArrayID(LListSet<T> *ptr, LLElement<T> *place);		//give the linked list and the element position for the iterator

		//getting back a T pointer
		T operator*() const;
		LLIterator<T> operator++();
		bool operator==(const LLIterator<T> &other);
		bool operator!=(const LLIterator<T> &other);

	private:
		LLElement<T> *currentPtr;					//returns pointer of T
		int pos;
		LListSet<T> *arrayID;

};

#include "LListSet.hpp"


#endif //LListSet_H_