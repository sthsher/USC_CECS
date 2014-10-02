

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

	vector<node<keyT, valueT>* > allNodes;

	allNodes.resize(numOfEntries);

	int num = 0;

	for (int i = 0; i < tableSize; ++i)
	{
		if (this->at(i) == NULL)
			{	}//do nothing
		else
		{
			node<keyT, valueT>* temp = this->at(i);
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
		this->at(index)->prevNode = NULL;
	}
	else
	{

		node<keyT, valueT>* checkNode;
		checkNode = this->at(index);

		//check for repeat of keys
		while (true)
		{
			if (checkNode->key.content == addKey.content)
				throw logic_error("Exception: Key already exists in table");
			if (checkNode->nextNode == NULL)
				break;
			checkNode = checkNode->nextNode;
		}

		node<keyT, valueT>* newNode = new node<keyT, valueT>;
		newNode->key = addKey;
		newNode->value = addValue;

		newNode->nextNode = this->at(index);
		this->at(index)->prevNode = newNode;

		newNode->prevNode = NULL;

		this->at(index) = newNode;

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

	while (currentNode != NULL)
	{
		if(currentNode->key == removeKey)
		{
			node<keyT, valueT>* toDelete = currentNode;

			//if only one node
			if (currentNode->nextNode == NULL && currentNode->prevNode == NULL)
			{
				delete currentNode;
				this->at(index) = NULL;
				return;
			}
			//if currentNode is first
			if (currentNode->prevNode == NULL)
			{
				currentNode->nextNode->prevNode = NULL;
				this->at(index) = currentNode->nextNode;
			}
			else if (currentNode->nextNode == NULL)
			{
				currentNode->prevNode->nextNode = NULL;
			}
			else
			{
				currentNode->prevNode->nextNode = currentNode->nextNode;
				currentNode->nextNode->prevNode = currentNode->prevNode;
			}

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

