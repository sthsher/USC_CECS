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

		T returnData() const;
		LListElement<T> *returnNext();

	private:
		T data;
		LListElement<T> *next;

};


#include "LListElementImpl.h"


#endif //LListElement_H_