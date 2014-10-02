using namespace std;

template <class T>
heap<T> :: heap (int d, bool maxHeap)
{
	factor = d;
	isMax = maxHeap;
	arrayPtr = new doubleSize<T>;
	size = 0;
}
	
template <class T>
heap<T> :: ~heap ()
{
	delete arrayPtr;
}

template <class T>
T & heap<T> :: peek () const
{
	if (size == 0)
	{
		throw logic_error("Exception error: heap is empty, nothing to peek");
	}
	arrayPtr->get(0);
}

template<class T>
void heap<T> :: swap (int indexA, int indexB)
{
	//create a duplicate for now
	T temp = arrayPtr->get(indexA);
	arrayPtr->set(indexA, (arrayPtr->get(indexB)));
	arrayPtr->set(indexB, temp);
	return;
}


template <class T>
bool heap<T> :: checkLeaf(int node)
{
	//check validity of youngest child. If noc hild, then leaf
	//first child is dn+1
	int child = (node*factor)+1;

	//child has to be within size
	if (child >= size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//returns index of the largest child
template <class T>
int heap<T> :: largestChildIndex(T* childArray, int arraySize, int firstIndex)
{
	//childArray points to an array containing all the values to be compared
	int largestIndex = firstIndex;
	T tempLargest = childArray[0];
	for (int i = 1; i < arraySize; ++i)
	{
		if (tempLargest < childArray[i])
		{
			//set as new largest
			tempLargest = childArray[i];
			//update index
			largestIndex = firstIndex + i;
		}
	}

	return largestIndex;
}

template <class T>
int heap<T> :: smallestChildIndex(T* childArray, int arraySize, int firstIndex)
{
	//childArray points to an array containing all the values to be compared
	int smallestIndex = firstIndex;
	T tempLargest = childArray[0];
	for (int i = 1; i < arraySize; ++i)
	{
		if (tempLargest > childArray[i])
		{
			//set as new smallest
			tempLargest = childArray[i];
			//update index
			smallestIndex = firstIndex + i;
		}
	}

	return smallestIndex;
}

//this is for delete
template <class T>
void heap<T> :: trickleDown(int currentNode)
{

	//check if is leaf
	bool isLeaf = checkLeaf(currentNode);
	if (isLeaf)
	{
		//a leaf, return
		return;
	}

	//find largest child: get the index
	//make an array with all the children's values inside
	T* childArray = new T[factor];

	//get the index of the first child
	int firstChild = (currentNode*factor)+1;
	int childIndex = (currentNode*factor)+1;
	int arraySize = 0;
	
	//fill array with the current node's children
	for (int i = 0; i < factor; ++i)
	{
		//no more children
		if (childIndex >= size)
		{
			break;
		}
		else
		{
			childArray[i] = arrayPtr->get(childIndex++);
			arraySize++;
		}
	}



/*
	for (int i = 0; i < arraySize; ++i)
	{
		//cout << "Child: " << childArray[i] << endl;
	}
*/

	//compiler won't allow functional programming for some odd reason for the comparisons, make individuals to compare
	T currentItem = arrayPtr->get(currentNode);

	//now find the necessary child
	if (isMax)
	{
		childIndex = largestChildIndex(childArray, arraySize, firstChild);

		T childItem = arrayPtr->get(childIndex);

		//maxHeap base case: if the largest child is still smaller than the current
		if ( currentItem > childItem )
		{
			delete [] childArray;
			return;
		}
	}
	else
	{
		childIndex = smallestChildIndex(childArray, arraySize, firstChild);
		
		T childItem = arrayPtr->get(childIndex);

		//minHeap base case: if the smallest child is still larger than the current
		if ( currentItem < childItem )
		{
			delete [] childArray;
			return;
		}	

	}

	//child index now holds largest child's index
	//now swap the current node with its largest child
	swap(currentNode, childIndex);

	//right now, the item to remvoe is at the childIndex's position
	delete [] childArray;
	return trickleDown(childIndex);



}

template <class T>
void heap<T> :: trickleUp(int currentNode)
{

	//Get the parent's index
	int parentIndex = ((currentNode-1)/factor);

	//cout << "Parent: " << arrayPtr->get(parentIndex) << endl;
	
	//compiler won't allow functional programming for some odd reason for the comparisons, make individuals to compare
	T currentItem = arrayPtr->get(currentNode);
	T parentItem = arrayPtr->get(parentIndex);

	//test whether need to swap or not
	if (isMax)
	{
		//if the parent is greater, base case: then no need to swap
		if (currentItem < parentItem)
		{
			return;
		}
		else
		{
			swap(currentNode, parentIndex);

			if (parentIndex == 0)
			{
				//cout << "root node" << endl;
				return;
				
			}			
			return trickleUp(parentIndex);
		}
	}
	else
	{
		//if the parent is smaller, base case: no need to  swap
		if (currentItem > parentItem)
		{
			return;
		}
		else
		{
			swap(currentNode, parentIndex);

			if (parentIndex == 0)
			{
				//cout << "root node" << endl;
				return;
				
			}	
			return trickleUp(parentIndex);
		}		
	}

}


template <class T>
void heap<T> ::  remove ()
{

	if (size == 0)
	{
		throw logic_error("Exception error: Heap is empty, nothing to remove");
	}
	else
	{
		//if only root, then just remove root
		if (size == 1)
		{
			arrayPtr->remove(0);
			size--;
		}
		else
		{


			//swap the first and last element, then trickle down
			swap(0, size-1);

			arrayPtr->remove(--size);
			trickleDown(0);
		}

	}
}

template <class T>
void heap<T> ::  add (const T &item)
{
	//if nothing in the heap, then just add it, no need to trickle

	arrayPtr->insert(size,item);
	if (size == 0)
	{
		size++;
		return;
	}


	trickleUp(size++);

}

/*
template <class T>
void heap<T> :: printHeap() const
{
	if (size == 0)
	{
		throw logic_error("Exception error: heap is empty. Nothing to print");
	}
	arrayPtr->printArray();
}
*/
