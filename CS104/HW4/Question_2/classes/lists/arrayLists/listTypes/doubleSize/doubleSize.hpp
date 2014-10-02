#include <math.h>

template <class dataType>
doubleSize<dataType>::doubleSize()
{
	this->size = 10;
	this->numOfElements = 0;
	this->arrayPtr = new dataType[10];
	
									//this->pureSize = 10;
									//this->numOfElements = 0;
}

template <class dataType>
doubleSize<dataType>::doubleSize(int initial)
{
	this->size = 10;

	this->numOfElements = 1;
	this->arrayPtr = new dataType[10];
	this->arrayPtr[0] = initial;

									//this->pureSize = 10;
									//this->pureNumOfElements = 1;
}

template <class dataType>
doubleSize<dataType>::~doubleSize()
{

}

template <class dataType>
void doubleSize<dataType>::extendArray()
{
	//create new array of double size
	dataType *newArray = new dataType[(this->size) + (this->size)];

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


template <class dataType>
int doubleSize<dataType>::returnSize()
{
	return this->size;
}

template <class dataType>
int doubleSize<dataType>::returnNumOfElements()
{
	return this->numOfElements;
}
