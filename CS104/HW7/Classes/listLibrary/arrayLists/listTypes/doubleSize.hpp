#include <math.h>

template <class T>
doubleSize<T>::doubleSize()
{
	this->size = 10;
	this->numOfElements = 0;
	this->arrayPtr = new T[10];
	
									//this->pureSize = 10;
									//this->numOfElements = 0;
}

template <class T>
doubleSize<T>::doubleSize(int initial)
{
	this->size = 10;

	this->numOfElements = 1;
	this->arrayPtr = new T[10];
	this->arrayPtr[0] = initial;

									//this->pureSize = 10;
									//this->pureNumOfElements = 1;
}

template <class T>
doubleSize<T>::~doubleSize()
{

}

template <class T>
void doubleSize<T>::extendArray()
{
	//create new array of double size
	T *newArray = new T[(this->size) + (this->size)];

	//copy old array to new array
	for (int i = 0; i < this->numOfElements; i++)
	{
		newArray[i] = this->arrayPtr[i];
	}

	//delete and update
	delete this->arrayPtr;
	this->arrayPtr = newArray;

	this->size = (this->size + this->size);
											//this->pureSize = this->size;
}


template <class T>
int doubleSize<T>::returnSize()
{
	return this->size;
}

template <class T>
int doubleSize<T>::returnNumOfElements()
{
	return this->numOfElements;
}
