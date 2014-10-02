#include <iostream>

//test if number is within size
bool isValid(int n, int size)
{
	if (n < 0 || n > size) return false;
	return true;
}

//initial size is 10
template<class dataType>
abstractArray<dataType>::abstractArray()
{
	arrayPtr = new dataType[10];
	size = 10;
	numOfElements = 0;
}

//constructs with first element
template<class dataType>
abstractArray<dataType>::abstractArray(dataType initial)
{
	arrayPtr = new dataType[10];
	arrayPtr[0] = initial;
	size = 10;
	numOfElements = 1;
}

template<class dataType>
abstractArray<dataType>::~abstractArray()
{
	
}

//Inserts to the left
template <class dataType>
void abstractArray<dataType>::insert (int pos, const dataType & item)
{

	if(isValid(pos, size) == false)
	{
		cout<<"Error: invalid position entered. Access array out of bounds"<<endl;
		return;
	}

	//If no more space, extend array
	if (size == numOfElements) extendArray();

	//start from end of array and add back to position, then add the new item in the position
	for (int i = numOfElements; i >= pos; i--)
	{
		arrayPtr[i] = arrayPtr[i-1];
	}
	arrayPtr[pos] = item;
	numOfElements++;
										//this->pureNumOfElements++;
	return;

}

template <class dataType>
void abstractArray<dataType>::remove (int pos)
{

	if(isValid(pos, size) == false)
	{
		cout<<"Error: invalid position entered. Access array out of bounds"<<endl;
		return;
	}

	dataType *newArray = new dataType[size];

	//copy data until right before the place to delete
	for (int i = 0; i < pos; i++)
	{
		newArray[i] = arrayPtr[i];
	}

	//copy all the data left one space, overwriting the item to delete
	for (int i = pos; i < size-1; i++)
	{
		newArray[i] = arrayPtr[i+1];
	}

	//delete the old array
	delete arrayPtr;

	//update array
	arrayPtr = newArray;

	numOfElements--;
									//this->pureNumOfElements--;
	return;
}

template <class dataType>
void abstractArray<dataType>::set (int pos, const dataType & item)
{
	if(isValid(pos, size) == false)
	{
		cout<<"Error: invalid position entered. Access array out of bounds"<<endl;
		return;
	}

	arrayPtr[pos] = item;

	return;
}	

template <class dataType>
dataType const & abstractArray<dataType>::get (int pos) const
{
	if(isValid(pos, size) == false)
	{
		cout<<"Error: invalid position entered. Access array out of bounds"<<endl;
		cout<<"Returning element 0 by default"<<endl;
		return arrayPtr[0];
	}

	return arrayPtr[pos];
}

template <class dataType>
void abstractArray<dataType>::printElement(int pos) const
{
	cout<<"Element "<<pos<<": "<<arrayPtr[pos]<<endl;
}

template <class dataType>
void abstractArray<dataType>::printArray() const
{
	cout<<"Now printing all the elements: "<<endl;

	for (int i = 0; i < numOfElements; i++)
	{
		cout<<arrayPtr[i]<<" ";
	}

	cout<<endl;
}
