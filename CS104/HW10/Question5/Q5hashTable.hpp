

template <class T>
hashTable<T>::hashTable (int t)
{
	target = t;

	this->resize(t);
	tableSize = t;
	numOfEntries = 0;

	for (int i = 0; i < tableSize; ++i)
	{
		this->at(i) = NULL;
	}
}

template <class T>
hashTable<T>::~hashTable()
{
	vector<node<T>* > allNodes;

	allNodes.resize(numOfEntries);

	int num = 0;

	for (int i = 0; i < tableSize; ++i)
	{
		if (this->at(i) == NULL)
			{	}//do nothing
		else
		{
			node<T>* temp = this->at(i);
			while (temp != NULL)
			{
				allNodes.at(num++) = temp;
				temp = temp->nextNode;
			}
		}
	}

	for (int i = 0; i < numOfEntries; ++i)
	{
		delete this->at(i);
	}
}

template <class T>
void hashTable<T>::rehash()
{
	int storageIndex = 0;

	//store all the entries
	vector<node<T>* > storage;
	storage.resize(tableSize);
	for (int i = 0; i < tableSize; ++i)
	{
		if (this->at(i) == NULL)
			{	}//do nothing
		else
		{
			//make a node holder
			node<T>* holder = this->at(i);
			while (holder != NULL)
			{
				storage.at(storageIndex++) = holder;
				holder = holder->nextNode;
			}

		}

	}

	this->clear();

	//make a new hash table
	this->resize((tableSize + tableSize));

	tableSize = this->size();

	int tempNum = numOfEntries;
	numOfEntries = 0;


	for (int i = 0; i < tempNum; ++i)
	{
		this->add(storage.at(i)->content);
	}

}

template <class T>
void hashTable<T>::add (const T & addItem)
{
	int index = 0;

	index = indexValue(addItem);

	//null case
	if (this->at(index) == NULL)
	{
		this->at(index) = new node<T>;
		this->at(index)->content = addItem;
		this->at(index)->nextNode = NULL;
	}
	else
	{
		// pointer to hold last node
		node<T>* lastNode;
		//start off with first node
		lastNode = this->at(index);
		// while (this->at(index)->nextNode != NULL)
		while (true)
		{
			if (lastNode->content == addItem)
			{
				//found existing value. Dish with the specified value already exists, just return
				return;
			}
			//stop if last node
			if (lastNode->nextNode == NULL)
				break;

			lastNode = lastNode->nextNode;
		}

		//make a new node
		node<T>* newNode = new node<T>;
		newNode->content = addItem;
		newNode->nextNode = NULL;

		lastNode->nextNode = newNode;

	}

	numOfEntries++;

	double loadFactor = numOfEntries/tableSize;

	if ((numOfEntries/tableSize)>= 0.5)
	{
		rehash();
	}


}

template <class T>
void hashTable<T>::remove(const T & removeItem)
{
	int index = 0;
	index = indexValue(removeItem);

	//case: index is empty
	if (this->at(index) == NULL)
		throw logic_error("Exception: Remove item does not exist");

	//look through linked list
	//hold node
	node<T>* currentNode = this->at(index);

	//test base case
	if (currentNode->content == removeItem)
	{
		this->at(index) = currentNode->nextNode;
		delete currentNode;
		numOfEntries--;
		return;
	}

	while (currentNode->nextNode != NULL)
	{
		if(currentNode->nextNode->content == removeItem)
		{
			node<T>* toDelete = currentNode->nextNode;
			currentNode->nextNode = toDelete->nextNode;
			delete toDelete;
			numOfEntries--;
			return;
		}

		currentNode = currentNode->nextNode;
	}

	throw logic_error("Exception: Remove item does not exist");

}

template <class T>
T hashTable<T>::get (const T & getItem)
{
	node<T>* currentNode = this->at(getItem);


	if(currentNode != NULL)
		return currentNode->content;

	throw logic_error("Exception: Get item does not exist");

}

template <class T>
int hashTable<T>::indexValue(int value)
{
	return abs(target-value);
}

template <class T>
void hashTable<T>::print()
{
	for(int i = 0; i < tableSize; ++i)
	{
		if (this->at(i) == NULL)
		{
			cout << "NULL" << endl;
		}
		else
		{
			//create a holder
			node<T>* displayNode = this->at(i);
			while (displayNode != NULL)
			{
				cout << displayNode->content << "  ";
				displayNode = displayNode->nextNode;

			}
			cout << endl;
		}
	}

	cout << endl;
}

