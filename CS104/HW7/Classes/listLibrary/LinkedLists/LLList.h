#ifndef LLList_H_
#define LLList_H_

#include "Element/LListElement.h"

using namespace std;

template <class T>
class LLList: public pureList<T>
{
	public:

		LLList();

		virtual ~LLList();

		virtual void insert (int pos, const T & item);
	
		void removePtr(LListElement<T> *p);
		virtual void remove (int pos);

		virtual void set (int pos, const T & item);

		virtual T const & get (int pos) const;

		virtual void printElement(int pos) const;

		virtual void printArray() const;

	private:

		LListElement<T>* getToPos(int pos) const;

		LListElement<T> *start, *end;
		int size;

};

#include "LLList.hpp"

#endif //LLList_H_