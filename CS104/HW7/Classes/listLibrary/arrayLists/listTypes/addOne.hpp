template <class T>
addOne<T>::addOne()
{
	this->size = 10;
	this->numOfElements = 0;
	this->arrayPtr = new T[10];
	
									//this->pureSize = 10;
									//this->numOfElements = 0;
}

template <class T>
addOne<T>::addOne(T initial)
{
	this->size = 10;

	this->numOfElements = 1;
	this->arrayPtr = new T[10];
	this->arrayPtr[0] = initial;

									//this->pureSize = 10;
									//this->pureNumOfElements = 1;
}

template <class T>
addOne<T>::~addOne()
{

}

template <class T>
void addOne<T>::extendArray()
{
	//new array of size+1
	T *newArray = new T[this->size+1];

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


template <class T>
int addOne<T>::returnSize()
{
	return this->size;
}

template <class T>
int addOne<T>::returnNumOfElements()
{
	return this->numOfElements;
}
