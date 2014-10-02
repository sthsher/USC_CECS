#include <math.h>

template <class T>
addTenPercent<T>::addTenPercent()
{
	this->size = 10;
	this->numOfElements = 0;
	this->arrayPtr = new T[10];
	
									//this->pureSize = 10;
									//this->numOfElements = 0;
}

template <class T>
addTenPercent<T>::addTenPercent(int initial)
{
	this->size = 10;

	this->numOfElements = 1;
	this->arrayPtr = new T[10];
	this->arrayPtr[0] = initial;

									//this->pureSize = 10;
									//this->pureNumOfElements = 1;
}

template <class T>
addTenPercent<T>::~addTenPercent()
{

}

template <class T>
void addTenPercent<T>::extendArray()
{
	//create new array of add 10%
	double newSizeD = ceil((this->size)*(1.1));
	int newSize = static_cast<int>(newSizeD);
	T *newArray = new T[newSize];

	//copy array
	for (int i = 0; i < this->numOfElements; i++)
	{
		newArray[i] = this->arrayPtr[i];
	}

	//delete and update
	delete this->arrayPtr;
	this->arrayPtr = newArray;

	this->size = newSize;
											//this->pureSize = newSize;
}


template <class T>
int addTenPercent<T>::returnSize()
{
	return this->size;
}

template <class T>
int addTenPercent<T>::returnNumOfElements()
{
	return this->numOfElements;
}
