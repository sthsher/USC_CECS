#include <iostream>

//test if number is within size
bool isValid(int n, int size)
{
	//base case
	if (n == 0 && size == 0)
		return true;
	if (n < 0 || n > size) return false;
	return true;
}

//initial size is 10
template<class T>
abstractArray<T>::abstractArray()
{
	arrayPtr = new T[10];
	size = 10;
	numOfElements = 0;
}

//constructs with first element
template<class T>
abstractArray<T>::abstractArray(T initial)
{
	arrayPtr = new T[10];
	arrayPtr[0] = initial;
	size = 10;
	numOfElements = 1;
}

template<class T>
abstractArray<T>::~abstractArray()
{
	delete arrayPtr;
}

//Inserts to the left
template <class T>
void abstractArray<T>::insert (int pos, const T & item)
{

	if(isValid(pos, numOfElements) == false)
	{
		throw logic_error("Exception error 1: invalid position entered. Access array out of bounds");
	}

	//If no more space, extend array
	if (size == numOfElements) extendArray();

	//case: if empty
	if (numOfElements == 0)
	{
		arrayPtr[0] = item;
		numOfElements++;
		return;
	}

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

template <class T>
void abstractArray<T>::remove (int pos)
{

	if(isValid(pos, numOfElements) == false)
	{
		throw logic_error("Exception error 2: invalid position entered. Access array out of bounds");
	}

	T *newArray = new T[size];

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
	delete [] arrayPtr;

	//update array
	arrayPtr = newArray;

	numOfElements--;
									//this->pureNumOfElements--;
	return;
}

template <class T>
void abstractArray<T>::set (int pos, const T & item)
{
	if(isValid(pos, numOfElements) == false)
	{
		throw logic_error("Exception error 3: invalid position entered. Access array out of bounds");
	}

	arrayPtr[pos] = item;

	return;
}	

template <class T>
T const & abstractArray<T>::get (int pos) const
{
	if(isValid(pos, numOfElements) == false)
	{
		throw logic_error("Exception error 4: heap is empty. Nothing to peek");
	}

	return arrayPtr[pos];
}

/*

template <class T>
void abstractArray<T>::printElement(int pos) const
{
	cout<<"Element "<<pos<<": "<<arrayPtr[pos]<<endl;
}

template <class T>
void abstractArray<T>::printArray() const
{
	cout<<"Now printing all the elements: "<<endl;

	for (int i = 0; i < numOfElements; i++)
	{
		cout<<arrayPtr[i]<<" ";
	}

	cout<<endl;
}
*/
