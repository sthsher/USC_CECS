#ifndef LLList_H_
#define LLList_H_

#include "Element/LListElement.h"

using namespace std;

template <class dataType>
class LLList: public pureList<dataType>
{
	public:

		LLList();

		virtual ~LLList();

		virtual void insert (int pos, const dataType & item);
	
		void removePtr(LListElement<dataType> *p);
		virtual void remove (int pos);

		virtual void set (int pos, const dataType & item);

		virtual dataType const & get (int pos) const;

		virtual void printElement(int pos) const;

		virtual void printArray() const;

	private:

		LListElement<dataType>* getToPos(int pos) const;

		LListElement<dataType> *start, *end;
		int size;

};

#include "LLList.hpp"

#endif //LLList_H_