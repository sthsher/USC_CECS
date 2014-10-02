#ifndef LListElement_H_
#define LListElement_H_

using namespace std;

template <class T>
class LListElement
{
	public:
		LListElement();
		~LListElement();

		void setData(T s);
		void setNext(LListElement<T> *n);
		void setPrev(LListElement<T> *p);

		T returnData() const;
		LListElement<T> *returnNext();
		LListElement<T> *returnPrev();

	private:
		T data;
		LListElement<T> *next, *prev;

};


#include "LListElement.hpp"


#endif //LListElement_H_