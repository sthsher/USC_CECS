#include <iostream>
using namespace std;

template<class dataType>
LListElement<dataType>::LListElement()
{
	next = NULL;
	prev = NULL;
}

template <class dataType>
LListElement<dataType>::~LListElement()
{

}

template <class dataType>
void LListElement<dataType>::setData(dataType x)
{
	data = x;
}

template <class dataType>
void LListElement<dataType>::setNext(LListElement<dataType> *n)
{
	next = n;
}

template <class dataType>
void LListElement<dataType>::setPrev(LListElement<dataType> *p)
{
	prev = p;
}

template <class dataType>
dataType LListElement<dataType>::returnData() const
{
	return data;
}

template <class dataType>
LListElement<dataType> *LListElement<dataType>::returnNext()
{
	return next;
}

template <class dataType>
LListElement<dataType> *LListElement<dataType>::returnPrev()
{
	return prev;
}
