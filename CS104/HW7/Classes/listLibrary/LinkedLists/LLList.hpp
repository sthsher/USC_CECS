#include <iostream>

//returns a Linked list element at the requested position in the linked list
template <class T>
LListElement<T>* LLList<T>::getToPos(int pos) const
{
	LListElement<T> *temp = start;

	for (int i = 0; i < pos; i++)
	{
		temp = temp -> returnNext();
	}

	return temp;
}


template <class T>
LLList<T>::LLList()
{
	start = NULL;
	end = NULL;
	size = 0;
}

//Deletes the list
template <class T>
LLList<T>::~LLList()
{
	LListElement<T> *temp = start;
	LListElement<T> *nextEle;

	for (temp; temp != NULL; temp = nextEle)
	{
		nextEle = temp->returnNext();
		delete temp;
	}
}

template <class T>
void LLList<T>::insert (int pos, const T & item)
{

	if (pos > size)
	{
		cout << "Error: position exceeds size" << endl;
		cout << "Item not added" << endl;
		return;
	}

	//craete new element with the item's information
	LListElement<T> *newEle = new LListElement<T>;
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
		LListElement<T> *temp = end;

		end -> setNext(newEle);
		end = newEle;
		end -> setPrev(temp);
	}
	else
	{
		//Add to the left of position
		LListElement<T> *after = getToPos(pos);
		LListElement<T> *before = getToPos(pos-1);

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
template<class T>
void LLList<T>::removePtr (LListElement<T> *p)
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


template <class T>
void LLList<T>::remove (int pos)
{

	if (pos > size)
	{
		cout << "Error: position exceeds size" << endl;
		cout << "Item not added" << endl;
		return;
	}

	LListElement<T> *temp = getToPos(pos);
	removePtr(temp);
	size--;
								//this->pureSize--;
}

template <class T>
void LLList<T>::set (int pos, const T & item)
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
		LListElement<T> *newEle = new LListElement<T>;
		newEle -> setData(item);	
		start = newEle;
		end = newEle;

		size++;
								//this->pureSize++;
		return;
	}

	LListElement<T> *temp = getToPos(pos);
	temp->setData(item);
}

template <class T>
T const & LLList<T>::get (int pos) const
{
	LListElement<T> *temp = getToPos(pos);
	temp->returnData();
}

template <class T>
void LLList<T>::printElement(int pos) const
{
	LListElement<T> *temp = getToPos(pos);
	cout << "Element at position " << pos << "is: " << temp->returnData() << endl;
}

template <class T>
void LLList<T>::printArray() const
{
	LListElement<T> *a;

	cout<<"Now printing list:"<<endl;

	for (a = start; a != NULL; a = a->returnNext())
	{
		cout<<a->returnData()<<"  ";
	}

	cout<<endl;
}
