#include <iostream>
using namespace std;


template <class dataType>
LListSet<dataType>::LListSet()
{
	start = NULL;
	end = NULL;
}

template <class dataType>
LListSet<dataType>::~LListSet()
{

}

template <class dataType>
void LListSet<dataType>::add (const dataType &x)
{

	LListElement<dataType> *ptr = new LListElement<dataType>;
	ptr -> setData(x);

	if (start == NULL && end == NULL)
	{
		//First element in set
		start = ptr;
		end = ptr;

		return;
	}
	else
	{
		//Add element to the end
		//LListElement<dataType> *temp = new LListElement<dataType>;
		//temp = end;

		LListElement<dataType> *temp = end;

		end->setNext(ptr);
		end = ptr;
		end->setPrev(temp);

		return;
	}

}

template<class dataType>
void LListSet<dataType>::removePtr (LListElement<dataType> *p)
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
void LListSet<dataType>::remove (dataType x)
{

	bool removed = false;

	LListElement<dataType> *z = start;
	while (z != NULL)
	{
		if (z->returnData() == x)
		{
			LListElement<dataType> *a = z->returnNext();
			removePtr(z);
			z = a;
			removed = true;
		}
		else
		{
			z = z->returnNext();
		}
	}



}

template <class dataType>
bool LListSet<dataType>::contains (const dataType &x)
{
	LListElement<dataType> *a;

	for (a = start; a != NULL; a = a->returnNext())
	{
		if (a->returnData() == x)
		{
			return true;
		}
	}

	return false;

}

template <class dataType>
void LListSet<dataType>::print() const
{

	
	LListElement<dataType> *a;

	cout<<"Now printing list:"<<endl;

	for (a = start; a != NULL; a = a->returnNext())
	{
		cout<<a->returnData()<<"  ";
	}

	cout<<endl;

}

template<class dataType>
dataType* LListSet<dataType>::convertToArray()
{
	int size = 0;
	LListElement<dataType> *a;


	for (a = start; a != NULL; a = a->returnNext())
	{
		size++;
	}

	dataType *arrayPtr = new dataType[size];

	int i = 0;

	for (a = start; a != NULL; a = a->returnNext())
	{
		arrayPtr[i++] = a->returnData();
	}

	return arrayPtr;

}

template<class dataType>
int LListSet<dataType>::returnSize()
{
	int size = 0;
	LListElement<dataType> *a;


	for (a = start; a != NULL; a = a->returnNext())
	{
		size++;
	}

	return size;
}

