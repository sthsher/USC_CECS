#include <iostream>
using namespace std;

template<class T>
LListElement<T>::LListElement()
{
	next = NULL;
	prev = NULL;
}

template <class T>
LListElement<T>::~LListElement()
{

}

template <class T>
void LListElement<T>::setData(T x)
{
	data = x;
}

template <class T>
void LListElement<T>::setNext(LListElement<T> *n)
{
	next = n;
}

template <class T>
void LListElement<T>::setPrev(LListElement<T> *p)
{
	prev = p;
}

template <class T>
T LListElement<T>::returnData() const
{
	return data;
}

template <class T>
LListElement<T> *LListElement<T>::returnNext()
{
	return next;
}

template <class T>
LListElement<T> *LListElement<T>::returnPrev()
{
	return prev;
}
