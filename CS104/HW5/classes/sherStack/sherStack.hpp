using namespace std;

//default constructor: everything is null
template <class T>
sherStack<T>::sherStack()
{
	start = NULL;
	end = NULL;
}

//return start's data
template <class T>
T sherStack<T> :: top() const
{
	if (start == NULL && end == NULL)
		{throw logic_error("Exception error: Stack is empty; nothing to top");}

	return start->returnData();
}

//delete the data
template<class T>
void sherStack<T> :: pop()
{
	if (start == NULL && end == NULL)
	{
		throw logic_error("Exception error: Stack is empty; nothing to pop");
		return;
	}

	//only one element left, so delete it, and revert it back to NULL for both start and end
	if (start == end)
	{
		delete start;
		start = NULL;
		end = NULL;
	}
	else
	{
		//make a new element, which is start's next
		LListElement<T> *newStart = start->returnNext();
		delete start;
		start = newStart;
	}
}

//all pretty standard
template<class T>
void sherStack<T> :: push(const T &item)
{
	LListElement<T> *newItem = new LListElement<T>;
	newItem->setData(item);

	if (start == NULL && end == NULL)
	{
		start = newItem;
		end = newItem;
		return;
	}
	else
	{
		newItem->setNext(start);
		start = newItem;
		return;
	}

}