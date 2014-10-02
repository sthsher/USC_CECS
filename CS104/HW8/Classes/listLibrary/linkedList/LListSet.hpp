#include <iostream>
using namespace std;

//****************************
//Element Implementation
//****************************
	
//Standard doubly linked list element

template<class T>
LLElement<T>::LLElement()
{
	next = NULL;
	prev = NULL;
}

template <class T>
LLElement<T>::~LLElement()
{
	next = NULL;
	prev = NULL;
}

template <class T>
void LLElement<T>::setData(T x)
{
	data = x;
}

template <class T>
void LLElement<T>::setNext(LLElement<T> *n)
{
	next = n;
}

template <class T>
void LLElement<T>::setPrev(LLElement<T> *p)
{
	prev = p;
}

template <class T>
T LLElement<T>::returnData() const
{
	return data;
}

template <class T>
LLElement<T> *LLElement<T>::returnNext()
{
	return next;
}

template <class T>
LLElement<T>* LLElement<T>::returnPrev()
{
	return prev;
}

//****************************
//LListSet Implementation
//****************************

//starndard double linked list implementation

template <class T>
LListSet<T> :: LListSet()
{
	startPtr = NULL;
	endPtr = NULL;
	size = 0;
}

template <class T>
LListSet<T> :: ~LListSet()
{
	LLElement<T> *check;
	LLElement<T> *checkNext;
	
	check = startPtr;
	checkNext = check->returnNext();

	while (checkNext != NULL)
	{
		delete check;
		check = checkNext;
		checkNext = check->returnNext();
	}
	delete check;

}

template <class T>
void LListSet<T> :: add (const T & item)
{
	LLElement<T> *toAdd = new LLElement<T>;
	toAdd->setData(item);
	toAdd->setNext(NULL);
	toAdd->setPrev(endPtr);

	if (startPtr == NULL)
	{
		startPtr = toAdd;
		endPtr = toAdd;
	}
	else
	{
		endPtr->setNext(toAdd);
		endPtr = toAdd;
	}

	endPtr->setNext(NULL);


	size++;

}

template <class T>
void LListSet<T> :: removePtr(LLElement<T> *p)
{
	if (p == startPtr)
	{
			startPtr = p->returnNext();
	}
	else
	{
			//the previous' element's next pointer is p's next element
			p->returnPrev()->setNext(p->returnNext());


	}

	//Same as above, but just the other way around
	if (p == endPtr)
	{
			endPtr = p->returnPrev();
	}
	else
	{
			p->returnNext()->setPrev(p->returnPrev());
	}

	delete p;
}

template <class T>
void LListSet<T> :: remove (const T & item)
{
	bool removed = false;

	LLElement<T> *temp = startPtr;
	while (temp != NULL)
	{
		if (temp->returnData() == item)
		{

			LLElement<T> *foo = temp->returnNext();

			removePtr(temp);

			temp = foo;
			removed = true;
			size--;
		}
		else
		{
				temp = temp->returnNext();
		}
	}

	endPtr->setNext(NULL);

	if (removed == true)
	{
			//cout<<"Elements containing "<<item<<" all removed"<<endl;
	}
	else
	{
			cout<<"Nothing to remove"<<endl;
	}
}

template <class T>
bool LListSet<T> :: contains(const T & item)
{
	LLElement<T> *check;

	for (check = startPtr; check != NULL; check = check->returnNext())
	{
			if (check->returnData() == item)
			{
					return true;
			}
	}

	return false;
}

template <class T>
bool LListSet<T> :: isEmpty()
{
	if (startPtr == NULL && endPtr == NULL)
		return true;
	return false;
}

template <class T>
int LListSet<T> :: returnSize() const
{
	return size;
}

template <class T>
LLIterator<T> LListSet<T> :: begin()
{
	return LLIterator<T>(this, startPtr);
}

template <class T>
LLIterator<T> LListSet<T> :: end()
{
	return LLIterator<T>(this, NULL);
}



//****************************
//Iterator Implementation
//****************************

template <class T>
LLIterator<T> :: LLIterator()
{
	currentPtr = NULL;
	pos = 0;
	arrayID = NULL;
}

template <class T>
LLIterator<T> :: LLIterator(LListSet<T> *ptr, LLElement<T> *place)
{
	arrayID = ptr;
	currentPtr = place;	
}

template <class T>
LLIterator<T> :: ~LLIterator()
{
	arrayID = NULL;
	currentPtr = NULL;
}

template <class T>
void LLIterator<T> :: setArrayID(LListSet<T> *ptr, LLElement<T> *place)
{
	arrayID = ptr;
	currentPtr = place;	
}

//return the data in the element
template <class T>
T LLIterator<T> :: operator*() const
{
	return (currentPtr->returnData());
}

//move the currentPtr to the next position
template <class T>
LLIterator<T> LLIterator<T> :: operator++()
{
	currentPtr = currentPtr->returnNext();
	return *this;
}

template <class T>
bool LLIterator<T> :: operator==(const LLIterator<T> &other)
{
	if (this->arrayID != other.arrayID || this->currentPtr != other.currentPtr)
	{
		return false;
	}
	else
		return true;
}

template <class T>
bool LLIterator<T> :: operator!=(const LLIterator<T> &other)
{
	if (this->arrayID == other.arrayID && this->currentPtr == other.currentPtr)
	{
		return false;
	}
	else
		return true;
}

