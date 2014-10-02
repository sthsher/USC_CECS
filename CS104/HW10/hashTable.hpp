

template <class keyT, class valueT>
hashTable<keyT, valueT>::hashTable ()
{
	this->resize(20);
	tableSize = 20;
	numOfEntries = 0;

	for (int i = 0; i < tableSize; ++i)
	{
		this->at(i) = NULL;
	}
}

template <class keyT, class valueT>
hashTable<keyT, valueT>::~hashTable()
{
	
}

template <class keyT, class valueT>
void hashTable<keyT, valueT>::rehash()
{


	int storageIndex = 0;

	//store all the entries
	vector< node<keyT, valueT>* > storage;
	storage.resize(tableSize);
	for (int i = 0; i < tableSize; ++i)
	{
		if (this->at(i) == NULL)
			{	}//do nothing
		else
		{
			//make a node holder
			node<keyT, valueT>* holder = this->at(i);
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
		this->add(storage.at(i)->key, storage.at(i)->value);
	}

}

template <class keyT, class valueT>
void hashTable<keyT, valueT>::add (const keyT & addKey, const valueT & addValue)
{
	
	//key has hash method
	int index = 0;

	index = indexValue(addKey.hash());

	//null case
	if (this->at(index) == NULL)
	{
		this->at(index) = new node<keyT, valueT>;
		this->at(index)->key = addKey;
		this->at(index)->value = addValue;
		this->at(index)->nextNode = NULL;
	}
	else
	{
		// pointer to hold last node
		node<keyT, valueT>* lastNode;
		//start off with first node
		lastNode = this->at(index);
		// while (this->at(index)->nextNode != NULL)
		while (true)
		{
			if (lastNode->key == addKey)
				throw logic_error("Exception: Key already exists in table");
			//stop if last node
			if (lastNode->nextNode == NULL)
				break;

			lastNode = lastNode->nextNode;
		}

		//make a new node
		node<keyT, valueT>* newNode = new node<keyT, valueT>;
		newNode->key = addKey;
		newNode->value = addValue;
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

template <class keyT, class valueT>
void hashTable<keyT, valueT>::remove(const keyT & removeKey)
{
	int index = 0;
	index = indexValue(removeKey.hash());

	//case: index is empty
	if (this->at(index) == NULL)
		throw logic_error("Exception: Remove key does not exist");

	//look through linked list
	//hold node
	node<keyT, valueT>* currentNode = this->at(index);

	//test base case
	if (currentNode->key == removeKey)
	{
		this->at(index) = currentNode->nextNode;
		delete currentNode;
		numOfEntries--;
		return;
	}

	while (currentNode->nextNode != NULL)
	{
		if(currentNode->nextNode->key == removeKey)
		{
			node<keyT, valueT>* toDelete = currentNode->nextNode;
			currentNode->nextNode = toDelete->nextNode;
			delete toDelete;
			numOfEntries--;
			return;
		}

		currentNode = currentNode->nextNode;
	}

	throw logic_error("Exception: Remove key does not exist");

}

template <class keyT, class valueT>
valueT hashTable<keyT, valueT>::get (const keyT & getKey)
{
	int const index = indexValue(getKey.hash());

	node<keyT, valueT>* currentNode = this->at(index);

	while (currentNode != NULL)
	{
		if(currentNode->key == getKey)
			return currentNode->value;

		currentNode = currentNode->nextNode;
	}

	throw logic_error("Exception: Get key does not exist");

	// if (currentNode->key == getKey)
	// {
	// 	return &(this->at(index)->value);
	// }

	// while(currentNode->nextNode != NULL)
	// {
	// 	if(currentNode->nextNode->key == getKey)
	// 	{
	// 		return 
	// 	}
	// }

}

template <class keyT, class valueT>
int hashTable<keyT, valueT>::indexValue(int value)
{
	return (value)%(tableSize);
}

template <class keyT, class valueT>
void hashTable<keyT, valueT>::print()
{
	for(int i = 0; i < tableSize; ++i)
	{
		if (this->at(i) == NULL)
		{
			cout << "0" << endl;
		}
		else
		{
			//create a holder
			node<keyT, valueT>* displayNode = this->at(i);
			while (displayNode != NULL)
			{
				cout << displayNode->key.content << "  ";
				displayNode = displayNode->nextNode;

			}
			cout << endl;
		}
	}

	cout << endl;
}

