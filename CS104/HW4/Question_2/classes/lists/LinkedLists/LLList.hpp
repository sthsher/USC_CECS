#include <iostream>

//returns a Linked list element at the requested position in the linked list
template <class dataType>
LListElement<dataType>* LLList<dataType>::getToPos(int pos) const
{
	LListElement<dataType> *temp = start;

	for (int i = 0; i < pos; i++)
	{
		temp = temp -> returnNext();
	}

	return temp;
}


template <class dataType>
LLList<dataType>::LLList()
{
	start = NULL;
	end = NULL;
	size = 0;
}

//Deletes the list
template <class dataType>
LLList<dataType>::~LLList()
{
	LListElement<dataType> *temp = start;
	LListElement<dataType> *nextEle;

	for (temp; temp != NULL; temp = nextEle)
	{
		nextEle = temp->returnNext();
		delete temp;
	}
}

template <class dataType>
void LLList<dataType>::insert (int pos, const dataType & item)
{

	if (pos > size)
	{
		cout << "Error: position exceeds size" << endl;
		cout << "Item not added" << endl;
		return;
	}

	//craete new element with the item's information
	LListElement<dataType> *newEle = new LListElement<dataType>;
	newEle -> setData(item);

	//First element
	if (start == NULL && end == NULL)
	{
		start = newEle;
		end = newEle;
	}

	//Add as first element
	else if (pos == 0)
	{
		start -> setPrev(newEle);
		newEle -> setNext(start);
		start = newEle;
	}

	//Add as last element
	else if (pos == size)
	{
		LListElement<dataType> *temp = end;

		end -> setNext(newEle);
		end = newEle;
		end -> setPrev(temp);
	}
	else
	{
		//Add to the left of position
		LListElement<dataType> *after = getToPos(pos);
		LListElement<dataType> *before = getToPos(pos-1);

		after  -> setPrev(newEle);
		before -> setNext(newEle);
		newEle -> setPrev(before);
		newEle -> setNext(after);
	}
	
	size++;
							//this->pureSize++;
	return;
}

//Same as the previous implementations from previous homeworks
template<class dataType>
void LLList<dataType>::removePtr (LListElement<dataType> *p)
{
	//If the pointer is the start pointer, set the start as the second element
	if (p == start)
	{
		start = p->returnNext();
	}
	else
	{
		//the previous' element's next pointer is p's next element
		p->returnPrev()->setNext(p->returnNext());
	}

	//Same as above, but just the other way around
	if (p == end)
	{
		end = p->returnPrev();
	}
	else
	{
		p->returnNext()->setPrev(p->returnPrev());
	}
	delete p;
}


template <class dataType>
void LLList<dataType>::remove (int pos)
{

	if (pos > size)
	{
		cout << "Error: position exceeds size" << endl;
		cout << "Item not added" << endl;
		return;
	}

	LListElement<dataType> *temp = getToPos(pos);
	removePtr(temp);
	size--;
								//this->pureSize--;
}

template <class dataType>
void LLList<dataType>::set (int pos, const dataType & item)
{

	if (pos > size)
	{
		cout << "Error: position exceeds size" << endl;
		cout << "Item not added" << endl;
		return;
	}

	//First element
	if (start == NULL && end == NULL)
	{
		LListElement<dataType> *newEle = new LListElement<dataType>;
		newEle -> setData(item);	
		start = newEle;
		end = newEle;

		size++;
								//this->pureSize++;
		return;
	}

	LListElement<dataType> *temp = getToPos(pos);
	temp->setData(item);
}

template <class dataType>
dataType const & LLList<dataType>::get (int pos) const
{
	LListElement<dataType> *temp = getToPos(pos);
	temp->returnData();
}

template <class dataType>
void LLList<dataType>::printElement(int pos) const
{
	LListElement<dataType> *temp = getToPos(pos);
	cout << "Element at position " << pos << "is: " << temp->returnData() << endl;
}

template <class dataType>
void LLList<dataType>::printArray() const
{
	LListElement<dataType> *a;

	cout<<"Now printing list:"<<endl;

	for (a = start; a != NULL; a = a->returnNext())
	{
		cout<<a->returnData()<<"  ";
	}

	cout<<endl;
}
