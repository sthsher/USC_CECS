template <class dataType>
addOne<dataType>::addOne()
{
	this->size = 10;
	this->numOfElements = 0;
	this->arrayPtr = new dataType[10];
	
									//this->pureSize = 10;
									//this->numOfElements = 0;
}

template <class dataType>
addOne<dataType>::addOne(dataType initial)
{
	this->size = 10;

	this->numOfElements = 1;
	this->arrayPtr = new dataType[10];
	this->arrayPtr[0] = initial;

									//this->pureSize = 10;
									//this->pureNumOfElements = 1;
}

template <class dataType>
addOne<dataType>::~addOne()
{

}

template <class dataType>
void addOne<dataType>::extendArray()
{
	//new array of size+1
	dataType *newArray = new dataType[this->size+1];

	//copy all the information
	for (int i = 0; i < this->numOfElements; i++)
	{
		newArray[i] = this->arrayPtr[i];
	}

	//delete old array and update
	delete this->arrayPtr;
	this->arrayPtr = newArray;

	this->size++;
											//this->pureSize++;
}


template <class dataType>
int addOne<dataType>::returnSize()
{
	return this->size;
}

template <class dataType>
int addOne<dataType>::returnNumOfElements()
{
	return this->numOfElements;
}
