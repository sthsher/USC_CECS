#include <math.h>

template <class dataType>
addTenPercent<dataType>::addTenPercent()
{
	this->size = 10;
	this->numOfElements = 0;
	this->arrayPtr = new dataType[10];
	
									//this->pureSize = 10;
									//this->numOfElements = 0;
}

template <class dataType>
addTenPercent<dataType>::addTenPercent(int initial)
{
	this->size = 10;

	this->numOfElements = 1;
	this->arrayPtr = new dataType[10];
	this->arrayPtr[0] = initial;

									//this->pureSize = 10;
									//this->pureNumOfElements = 1;
}

template <class dataType>
addTenPercent<dataType>::~addTenPercent()
{

}

template <class dataType>
void addTenPercent<dataType>::extendArray()
{
	//create new array of add 10%
	double newSizeD = ceil((this->size)*(1.1));
	int newSize = static_cast<int>(newSizeD);
	dataType *newArray = new dataType[newSize];

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


template <class dataType>
int addTenPercent<dataType>::returnSize()
{
	return this->size;
}

template <class dataType>
int addTenPercent<dataType>::returnNumOfElements()
{
	return this->numOfElements;
}
