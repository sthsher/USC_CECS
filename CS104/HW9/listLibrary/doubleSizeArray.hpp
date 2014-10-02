#include <math.h>
#include <iostream>

/*
//test if number is within size
inline bool isValid(int n, int size)
{
	if (n > 0 && n < size) return false;
	return true;
}
*/

//initial size is 10
template<class T>
doubleSizeArray<T>::doubleSizeArray()
{
	arrayPtr = new T[10];

	size = 10;
	numOfElements = 0;
}

//constructs with first element
template<class T>
doubleSizeArray<T>::doubleSizeArray(T initial)
{
	arrayPtr = new T[10];
	arrayPtr[0] = initial;
	size = 10;
	numOfElements = 1;
}

template<class T>
doubleSizeArray<T>::~doubleSizeArray()
{
	for (int i = 0; i < numOfElements; ++i)
	{
		remove(0);
	}
	if (arrayPtr != NULL)
	{
		delete[] arrayPtr;
		arrayPtr = NULL;
	}
	else
	{	}
}

//Inserts to the left
template <class T>
void doubleSizeArray<T>::insert (int pos, const T & item)
{

	if(pos < 0 || pos > size)
	{
		cout<<"Error 1: invalid position entered. Access array out of bounds"<<endl;
		return;
	}

	//If no more space, extend array
	if (size == numOfElements) extendArray();

	//empty case
	if (numOfElements == 0)
	{
		arrayPtr[0] = item;
	}

	//last case
	else if (pos == numOfElements)
	{
		arrayPtr[pos] = item;
	}

	//first case
	else if (pos == 0)
	{
		for (int i = numOfElements; i != 0; --i)
		{
			arrayPtr[i] = arrayPtr[i-1];
		}
		arrayPtr[0] = item;
	}

	//start from end of array and add back to position, then add the new item in the position
	else
	{

		for (int i = numOfElements; i >= pos; i--)
		{
			arrayPtr[i] = arrayPtr[i-1];
		}


		arrayPtr[pos] = item;
	}

	numOfElements++;

	return;
}

template <class T>
void doubleSizeArray<T>::clear()
{
	//clearing the content will be done with iterators in main
	numOfElements = 0;
}


template <class T>
void doubleSizeArray<T>::remove (int pos)
{

	if(pos < 0 || pos > size)
	{
		cout<<"Error 2: invalid position entered. Access array out of bounds"<<endl;
		return;
	}

	//shift all the data to the left from the position to be deleted
	//the last element will not be deleted, but since we decrememnt the number of elements
	//it will never be accessed and will be eventually overwritten
	for (int i = pos; i < numOfElements-1; ++i)
	{
		arrayPtr[i] = arrayPtr[i+1];
	}

	numOfElements--;

	return;
}

template <class T>
void doubleSizeArray<T>::set (int pos, const T & item)
{
	if(pos < 0 || pos > size)
	{
		cout<<"Error 3: invalid position entered. Access array out of bounds"<<endl;
		return;
	}

	arrayPtr[pos] = item;

	return;
}	

template <class T>
T const & doubleSizeArray<T>::get (int pos) const
{
	if(pos < 0 || pos > size)
	{
		cout<<"Error 4: invalid position entered. Access array out of bounds"<<endl;
		cout<<"Returning element 0 by default"<<endl;
		return arrayPtr[0];
	}

	return arrayPtr[pos];
}

template <class T>
bool doubleSizeArray<T> :: isEmpty() const
{
	if (numOfElements == 0)
	{
		return true;
	}
	return false;
}

template <class T>
void doubleSizeArray<T>::extendArray()
{
	//create new array of double size
	T *newArray = new T[(this->size) + (this->size)];

	//copy old array to new array
	for (int i = 0; i < this->numOfElements; i++)
	{
		newArray[i] = this->arrayPtr[i];
	}

	//delete and update
	delete [] this->arrayPtr;

	this->arrayPtr = newArray;

	this->size = (this->size + this->size);

}

template <class T>
int doubleSizeArray<T>::returnSize()
{
	return this->size;
}

template <class T>
int doubleSizeArray<T>::returnNumOfElements()
{
	return this->numOfElements;
}

template<class T>
T* doubleSizeArray<T>::returnStartPtr()
{
	return arrayPtr;
}

template<class T>
doubleIterator<T> doubleSizeArray<T>::begin()
{
	doubleIterator<T> beginIt(this);
	return beginIt;
}

template<class T>
doubleIterator<T> doubleSizeArray<T>::end()
{
	//move iterator to the end
	doubleIterator<T> endIt(this);
	for (int i = 0; i < numOfElements; ++i)
	{
		++endIt;
	}
	return endIt;
}








//Iterators

template<class T>
doubleIterator<T>::doubleIterator()
{
	currentPtr = NULL;
	arrayID = NULL;
	pos = 0;
}

template<class T>
doubleIterator<T>::doubleIterator(doubleSizeArray<T> *ptr)
{
	arrayID = ptr;
	currentPtr = ptr->arrayPtr;
	pos = 0;
}

template <class T>
doubleIterator<T>::~doubleIterator<T>()
{
	arrayID = NULL;
	currentPtr = NULL;
}

template<class T>
void doubleIterator<T>::setArrayID(doubleSizeArray<T> *ptr)
{
	arrayID = ptr;
	currentPtr = ptr->arrayPtr;
	pos = 0;
}

template<class T>
T* doubleIterator<T>::operator*() const
{
	return currentPtr;
}

template<class T>
doubleIterator<T> doubleIterator<T>::operator++()
{
	if(pos >= arrayID->numOfElements)
	{
		cout << "Iterator already at end of array" << endl;
	}
	else
	{
		currentPtr++;	//incrementing array pointer works
		pos++;
	}

	return *this;
}

template<class T>
bool doubleIterator<T>::operator==(const doubleIterator<T> &other)
{
	if (this->arrayID != other.arrayID)
	{
		return false;
	}

	if (this->pos == other.pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool doubleIterator<T>::operator!=(const doubleIterator<T> &other)
{
	if (this->arrayID != other.arrayID)
	{
		return true;
	}

	if (this->pos == other.pos)
	{
		return false;
	}
	else
	{
		return true;
	}
}


