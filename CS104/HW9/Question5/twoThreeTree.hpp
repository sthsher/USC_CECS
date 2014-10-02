template <class keyT, class valueT>
twoThreeTree<keyT, valueT>::twoThreeTree()
{
	numOfNodes = 0;
}

template <class keyT, class valueT>
twoThreeTree<keyT, valueT>::~twoThreeTree()
{

}

template <class keyT, class valueT>
int twoThreeTree<keyT, valueT>::findParentPos(const int & currentPos)
{
	int parentPos = 0;
	//Find parent index
	for (int i = 0; i < numOfNodes; ++i)
	{
		if(	this->at(i).leftChild == currentPos ||
			this->at(i).middleChild == currentPos ||
			this->at(i).rightChild == currentPos)
		{
			return i;
		}
	}
}


//returns index of the target item
template <class keyT, class valueT>
int twoThreeTree<keyT, valueT>::find(int currentPos, const keyT & targetKey) const
{
	//base case 1: the current node contains the targetKey
	if ((this->at(currentPos)).contains(targetKey))
	{
		//success
		return currentPos;
	}

	//base case 2: (this->at(currentPos)) has no more children, and haven't found targetKey
	if ((this->at(currentPos)).numOfChildren == 0)
	{
		throw logic_error("Exception: Specified key not contained in tree");
	}

	//traverse to
	//one key: only have left and right child
	if ((this->at(currentPos)).numOfKeys == 1)
	{
		//go left
		if (targetKey < (this->at(currentPos)).leftKey)
		{
			//recursively call function
			return find(this->at(currentPos).leftChild, targetKey);
		}
		//go right
		else
		{
			return find(this->at(currentPos).rightChild, targetKey);
		}
	}
	//two keys
	else if ((this->at(currentPos)).numOfKeys == 2)
	{
		//left
		if (targetKey < (this->at(currentPos)).leftKey)
		{
			return find(this->at(currentPos).leftChild, targetKey);
		}
		//middle case
		else if (targetKey > (this->at(currentPos)).leftKey && targetKey < (this->at(currentPos)).rightKey)
		{
			return find(this->at(currentPos).middleChild, targetKey);
		}
		//right case
		else
		{
			return find(this->at(currentPos).rightChild, targetKey);
		}
	}

	throw logic_error("Exception 1: Unexpected number of keys");
}

template <class keyT, class valueT>
int twoThreeTree<keyT, valueT>::findSuccessor(const int & startingPos, const int & currentPos, const keyT & targetKey) const
{
	//base case: current node is a leaf
	if (this->at(currentPos).numOfChildren == 0)
	{
		return currentPos;
	}

	//case: if it is the first iteration, travel right
	if (startingPos == currentPos)
	{
		//case: if the starting node has 2 children: go to right child
		if (this->at(currentPos).numOfChildren == 2)
		{
			return findSuccessor(startingPos, this->at(currentPos).rightChild, targetKey);
		}
		//case: if node has 3 children, test to see which key it is
		else
		{
			//if left key, go down middle
			if (this->at(currentPos).leftKey == targetKey)
				return findSuccessor(startingPos, this->at(currentPos).middleChild, targetKey);
			else
				return findSuccessor(startingPos, this->at(currentPos).rightChild, targetKey);
		}
	}
	//case: move left
	else
	{
		return findSuccessor(startingPos, this->at(currentPos).leftChild, targetKey);
	}
}


//this will return the index node that the targetKey is suppose to go
template <class keyT, class valueT>
int twoThreeTree<keyT, valueT>::traverseTo(int currentPos, const keyT & targetKey)
{
	//base case 1: the current node contains the targetKey
	//this should never happen though
	if (this->at(currentPos).contains(targetKey))
	{
		throw logic_error("Exception: Tree already contains specified key");
	}

	//base case 2: currentNode has no more children, a leaf
	if (this->at(currentPos).numOfChildren == 0)
	{
		return currentPos; 
	}

	//traverse to
	//one key: only have left and right child
	if (this->at(currentPos).numOfKeys == 1)
	{
		//go left
		if (targetKey < this->at(currentPos).leftKey)
		{
			//recursively call function
			return traverseTo(this->at(currentPos).leftChild, targetKey);
		}
		//go right
		else
		{
			return traverseTo(this->at(currentPos).rightChild, targetKey);
		}
	}
	//two keys
	else if(this->at(currentPos).numOfKeys == 2)
	{
		//left
		if (targetKey < this->at(currentPos).leftKey)
		{
			return traverseTo(this->at(currentPos).leftChild, targetKey);
		}
		//middle case
		else if (targetKey > this->at(currentPos).leftKey && targetKey < this->at(currentPos).rightKey)
		{
			return traverseTo(this->at(currentPos).middleChild, targetKey);
		}
		//right case
		else
		{
			return traverseTo(this->at(currentPos).rightChild, targetKey);
		}
	}
	throw logic_error("Exception 2: Unexpected number of keys");
}

template<class keyT, class valueT>
void twoThreeTree<keyT, valueT>::splitRoot(const keyT & addKey, const valueT & addValue, int childrenPos[])
{
	//determine the middle value
	keyT keyArray[3] = {this->at(0).leftKey, this->at(0).rightKey, addKey};
	quickSort<keyT> qSort(keyArray, 3);

	valueT valueArray[3];
	for (int i = 0; i < 3; ++i)
	{
		if (keyArray[i] == this->at(0).leftKey)
			valueArray[i] = this->at(0).leftValue;
		if (keyArray[i] == this->at(0).rightKey)
			valueArray[i] = this->at(0).rightValue;
		if (keyArray[i] == addKey)
			valueArray[i] = addValue;
	}

	//split the old root into two new nodes
	treeNode<keyT, valueT> smallNode(keyArray[0], valueArray[0]);
	treeNode<keyT, valueT> largeNode(keyArray[2], valueArray[2]);

	//set the children
	if (childrenPos[0] == 0 || childrenPos[1] == 0)
		smallNode.numOfChildren = 0;
	else
		smallNode.numOfChildren = 2;

	smallNode.leftChild = childrenPos[0];
	smallNode.rightChild = childrenPos[1];

	if (childrenPos[2] == 0 || childrenPos[3] == 0)
		largeNode.numOfChildren = 0;
	else
		largeNode.numOfChildren = 2;

	largeNode.leftChild = childrenPos[2];
	largeNode.rightChild = childrenPos[3];

	//add these two new nodes at the back
	this->push_back(smallNode);
	numOfNodes++;
	int smallPos = this->size()-1;

	this->push_back(largeNode);
	numOfNodes++;
	int largePos = this->size()-1;

	//make a new node to be new root. Value is middle value
	treeNode<keyT, valueT> newRoot(keyArray[1], valueArray[1]);
	//set new Root's children
	newRoot.numOfChildren = 2;
	newRoot.leftChild = smallPos;
	newRoot.rightChild = largePos;

	//set new root
	this->at(0) = newRoot;

	return;

}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::splitInternal(const int & currentPos, const keyT & addKey, const valueT & addValue, int childrenPos[])
{
	//find parent index
	int parentPos = findParentPos(currentPos);

	//store all of the current node's information
	treeNode<keyT, valueT> currentNode = this->at(currentPos);

	//make two new nodes to replace the current one
	//but first determine which is smallest, middle, largest
	keyT keyArray[3] = {currentNode.leftKey, currentNode.rightKey, addKey};


	quickSort<keyT> qSort(keyArray, 3);

	//make corresponding sorted array of values
	valueT valueArray[3];
	for (int i = 0; i < 3; ++i)
	{
		if (keyArray[i] == currentNode.leftKey)
			valueArray[i] = currentNode.leftValue;
		if (keyArray[i] == currentNode.rightKey)
			valueArray[i] = currentNode.rightValue;
		if (keyArray[i] == addKey)
			valueArray[i] = addValue;
	}


	//now make two new nodes. one with the smallest value, one with the largest value
	treeNode<keyT, valueT> smallNode(keyArray[0], valueArray[0]);
	treeNode<keyT, valueT> largeNode(keyArray[2], valueArray[2]);

	//the smaller node will replace currentPos
	this->at(currentPos) = smallNode;
	int smallPos = currentPos;

	this->push_back(largeNode);
	//pos is numOfNodes
	numOfNodes++;
	int largePos = this->size()-1;
	
	
	//This is an internal node, so set children
	this->at(smallPos).numOfChildren = 2;
	this->at(smallPos).leftChild = childrenPos[0];
	this->at(smallPos).rightChild = childrenPos[1];

	this->at(largePos).numOfChildren = 2;
	this->at(largePos).leftChild = childrenPos[2];
	this->at(largePos).rightChild = childrenPos[3];
	

	//set the parent's information
	//If parent has only one key
	if (this->at(parentPos).numOfKeys == 1)
	{
		if (this->at(parentPos).leftChild == currentPos)
		{
			//Case: splitting leftChild
			//leftChild is smallNode
			this->at(parentPos).leftChild = smallPos;
			//middleChild is largeNode
			this->at(parentPos).middleChild = largePos;

			//set parent's key information
			this->at(parentPos).copyLeftToRight();
			//pos 1 of array holds middle key and value
			this->at(parentPos).leftKey = keyArray[1];
			this->at(parentPos).leftValue = valueArray[1];

			this->at(parentPos).numOfKeys = 2;
			this->at(parentPos).numOfChildren = 3;

			//done
			return;
		}
		else
		{
			//Case: splitting rightChild
			this->at(parentPos).rightChild = largePos;
			this->at(parentPos).middleChild = smallPos;

			this->at(parentPos).rightKey = keyArray[1];
			this->at(parentPos).rightValue = valueArray[1];

			this->at(parentPos).numOfKeys = 2;
			this->at(parentPos).numOfChildren = 3;			

			return;
		}

	}

	//Case internal node
	if (this->at(parentPos).numOfKeys == 2)
	{
		//pushing middleKey up and need to split an internal node
		//need the position of the four children
		int childrenPos[4];
		//got three cases
		if (this->at(parentPos).leftChild == currentPos)
		{
			childrenPos[0] = smallPos;
			childrenPos[1] = largePos;
			childrenPos[2] = this->at(parentPos).middleChild;
			childrenPos[3] = this->at(parentPos).rightChild;
		}
		else if (this->at(parentPos).middleChild == currentPos)
		{
			childrenPos[0] = this->at(parentPos).leftChild;
			childrenPos[1] = smallPos;
			childrenPos[2] = largePos;
			childrenPos[3] = this->at(parentPos).rightChild;		
		}
		else
		{
			childrenPos[0] = this->at(parentPos).leftChild;
			childrenPos[1] = this->at(parentPos).middleChild;
			childrenPos[2] = smallPos;
			childrenPos[3] = largePos;		
		}

		//now call splitInternal
		//Case: root node
		if (parentPos == 0)
		{
			splitRoot(keyArray[1], valueArray[1], childrenPos);
		}
		else 
		{
			splitInternal(parentPos, keyArray[1], valueArray[1], childrenPos);
		}
	}
}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::splitLeaf(const int & currentPos, const keyT & addKey, const valueT & addValue)
{
	//find parent pos
	int parentPos = findParentPos(currentPos);

	//leaf case: if current node is the root (height of 2), go to splitRoot
	if (currentPos == 0)
	{
		int emptyPos[4] = {0,0,0,0};
		splitRoot(addKey, addValue, emptyPos);
		return;
	}

	//store all of the current node's information
	treeNode<keyT, valueT> currentNode = this->at(currentPos);

	//make two new nodes to replace the current one
	//but first determine which is smallest, middle, largest
	keyT keyArray[3] = {currentNode.leftKey, currentNode.rightKey, addKey};


	quickSort<keyT> qSort(keyArray, 3);

	//make corresponding sorted array of values
	valueT valueArray[3];
	for (int i = 0; i < 3; ++i)
	{
		if (keyArray[i] == currentNode.leftKey)
			valueArray[i] = currentNode.leftValue;
		if (keyArray[i] == currentNode.rightKey)
			valueArray[i] = currentNode.rightValue;
		if (keyArray[i] == addKey)
			valueArray[i] = addValue;
	}

	//now make two new nodes. one with the smallest value, one with the largest value
	treeNode<keyT, valueT> smallNode(keyArray[0], valueArray[0]);
	treeNode<keyT, valueT> largeNode(keyArray[2], valueArray[2]);

	//the smaller node will replace currentPos
	this->at(currentPos) = smallNode;
	int smallPos = currentPos;

	this->push_back(largeNode);		
	//pos is numOfNodes
	int largePos = this->size()-1;
	numOfNodes++;

	//set the parent's information
	//If parent has only one key
	if (this->at(parentPos).numOfKeys == 1)
	{
		if (this->at(parentPos).leftChild == currentPos)
		{
			//Case: splitting leftChild
			//leftChild is smallNode

			this->at(parentPos).numOfKeys = 2;
			this->at(parentPos).numOfChildren = 3;
			this->at(parentPos).leftChild = smallPos;
			//middleChild is largeNode
			this->at(parentPos).middleChild = largePos;

			//set parent's key information
			this->at(parentPos).copyLeftToRight();
			//pos 1 of array holds middle key and value
			this->at(parentPos).leftKey = keyArray[1];
			this->at(parentPos).leftValue = valueArray[1];

			//done
			return;
		}
		else
		{
			//Case: splitting rightChild
			this->at(parentPos).numOfKeys = 2;
			this->at(parentPos).numOfChildren = 3;
			this->at(parentPos).rightChild = largePos;
			this->at(parentPos).middleChild = smallPos;

			this->at(parentPos).rightKey = keyArray[1];
			this->at(parentPos).rightValue = valueArray[1];

			return;
		}


	}

	//Case internal node
	if (this->at(parentPos).numOfKeys == 2)
	{
		//pushing middleKey up and need to split an internal node
		//need the position of the four children
		int childrenPos[4];
		//got three cases
		if (this->at(parentPos).leftChild == currentPos)
		{
			childrenPos[0] = smallPos;
			childrenPos[1] = largePos;
			childrenPos[2] = this->at(parentPos).middleChild;
			childrenPos[3] = this->at(parentPos).rightChild;
		}
		else if (this->at(parentPos).middleChild == currentPos)
		{
			childrenPos[0] = this->at(parentPos).leftChild;
			childrenPos[1] = smallPos;
			childrenPos[2] = largePos;
			childrenPos[3] = this->at(parentPos).rightChild;		
		}
		else
		{
			childrenPos[0] = this->at(parentPos).leftChild;
			childrenPos[1] = this->at(parentPos).middleChild;
			childrenPos[2] = smallPos;
			childrenPos[3] = largePos;		
		}

		//now call splitInternal
		if (parentPos == 0)
		{
			splitRoot(keyArray[1], valueArray[1], childrenPos);
		}
		else 
		{
			splitInternal(parentPos, keyArray[1], valueArray[1], childrenPos);
		}
	}
}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::add (const keyT & addKey, const valueT & addValue)
{

	//case 1: tree is empty. Simply add to index 0
	if (numOfNodes == 0)
	{
		//make a new node
		treeNode<keyT, valueT> newNode(addKey, addValue);
		if (this->size() == 0)
			this->push_back(newNode);
		else
			this->at(0) = newNode;

		++numOfNodes;

		return;
	}

	//traverse to the target node
	int targetPos = traverseTo(0, addKey);
	treeNode<keyT, valueT> targetNode = this->at(targetPos);

	//Case 1: target node has room in it
	if (targetNode.numOfKeys == 1)
	{

		//Case A: addKey is larger, then just put it as rightKey
		if (addKey > targetNode.leftKey)
		{
			targetNode.numOfKeys = 2;
			targetNode.rightKey = addKey;
			targetNode.rightValue = addValue;
			this->at(targetPos) = targetNode;

			return;
		}
		//Case B: addKey is smaller
		if (addKey < targetNode.leftKey)
		{

			//move the left key to the right
			targetNode.numOfKeys = 2;
			targetNode.copyLeftToRight();
			targetNode.leftKey = addKey;
			targetNode.leftValue = addValue;
			this->at(targetPos) = targetNode;	

			return;
		}
	}

	//Case 2: target node has no more room in it
	//push up the middle value
	if (targetNode.numOfKeys == 2)
	{
		splitLeaf(targetPos, addKey, addValue);
	}
}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::swap(int posA, int posB, keyT targetKey)
{
	//case: if targetKeys is at the left key value
	if (this->at(posA).leftKey == targetKey)
	{
		//make a temp key and value
		keyT tempKey = this->at(posA).leftKey;
		valueT tempValue = this->at(posA).leftValue;

		this->at(posA).leftKey = this->at(posB).leftKey;
		this->at(posA).leftValue = this->at(posB).leftValue;

		this->at(posB).leftKey = tempKey;
		this->at(posB).leftValue = tempValue;

	}
	//targetKey is at right
	else
	{
		keyT tempKey = this->at(posA).rightKey;
		valueT tempValue = this->at(posB).rightValue;

		this->at(posA).rightKey = this->at(posB).leftKey;
		this->at(posA).rightValue = this->at(posB).leftValue;

		this->at(posB).leftKey = tempKey;
		this->at(posB).leftValue = tempValue;
	}
}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::oneKeyParent(const int & emptyPos, const int & parentPos)
{
	//check to see if there is any two-key sibling
	bool isTwoKeySibling = false;
	bool isLeftChild = false;
	int siblingPos;
	bool isLeaf = false;

	//test to see if emptyPos is the left child or not
	if (this->at(parentPos).leftChild == emptyPos)
	{
		isLeftChild = true;
		siblingPos = this->at(parentPos).rightChild;
	}
	else
	{
		isLeftChild = false;
		siblingPos = this->at(parentPos).leftChild;
	}

	//test to see sibling has two keys or not
	if (this->at(siblingPos).numOfKeys == 2)
		isTwoKeySibling = true;
	else
		isTwoKeySibling = false;

	//test to see if the nodes are leaves
	if (this->at(siblingPos).numOfChildren == 0)
		isLeaf = true;
	else
		isLeaf = false;


	if (isTwoKeySibling)
	{
		//case: parent has 1 key, has a two-key child to redistribute

		//case: empty is at left
		if (isLeftChild)
		{
			//set value of the empty node with the parent's information
			this->at(emptyPos).leftKey = this->at(parentPos).leftKey;
			this->at(emptyPos).leftValue = this->at(parentPos).leftValue;
			this->at(emptyPos).numOfKeys = 1;
			if (!isLeaf)
				this->at(emptyPos).numOfChildren = 2;
			else
				this->at(emptyPos).numOfChildren = 0;
			this->at(emptyPos).rightChild = this->at(siblingPos).leftChild;

			//set the parent value as sibling's left key
			this->at(parentPos).leftKey = this->at(siblingPos).leftKey;
			this->at(parentPos).leftValue = this->at(siblingPos).leftValue;
			this->at(parentPos).numOfKeys = 1;
			this->at(parentPos).numOfChildren = 2;
			this->at(parentPos).leftChild = emptyPos;
			this->at(parentPos).rightChild = siblingPos;

			//set sibling node's information
			this->at(siblingPos).copyRightToLeft();
			this->at(siblingPos).numOfKeys = 1;
			if (!isLeaf)
				this->at(siblingPos).numOfChildren = 2;
			else
				this->at(siblingPos).numOfChildren = 0;
			this->at(siblingPos).leftChild = this->at(siblingPos).middleChild;
			return;
		}
		//case: empty is at right
		else
		{
			//set value of the empty node with the parent's information
			this->at(emptyPos).leftKey = this->at(parentPos).leftKey;
			this->at(emptyPos).leftValue = this->at(parentPos).leftValue;
			this->at(emptyPos).numOfKeys = 1;
			if (!isLeaf)
				this->at(emptyPos).numOfChildren = 2;
			else
				this->at(emptyPos).numOfChildren = 0;
			this->at(emptyPos).rightChild = this->at(emptyPos).leftChild;
			this->at(emptyPos).leftChild = this->at(siblingPos).rightChild;

			//set the parent value as sibling's right key
			this->at(parentPos).leftKey = this->at(siblingPos).rightKey;
			this->at(parentPos).leftValue = this->at(siblingPos).rightValue;
			this->at(parentPos).numOfKeys = 1;
			this->at(parentPos).numOfChildren = 2;
			this->at(parentPos).leftChild = siblingPos;
			this->at(parentPos).rightChild = emptyPos;

			//set sibling node's information
			this->at(siblingPos).numOfKeys = 1;
			if (!isLeaf)
				this->at(siblingPos).numOfChildren = 2;
			else
				this->at(siblingPos).numOfChildren = 0;
			this->at(siblingPos).rightChild = this->at(siblingPos).middleChild;
			return;
		}
	}
	else
	{
		//case: all one key nodes
		//case: emptyNode is at left
		if (isLeftChild)
		{
			//merge: emptyNode's left is the parent, right is the sibling
			treeNode<keyT, valueT> newNode(this->at(parentPos).leftKey, this->at(parentPos).leftValue, this->at(siblingPos).leftKey, this->at(siblingPos).leftValue);

			//set the children
			if (!isLeaf)
				newNode.numOfChildren = 3;
			else
				newNode.numOfChildren = 0;
			newNode.leftChild = this->at(emptyPos).leftChild;
			newNode.middleChild = this->at(siblingPos).leftChild;
			newNode.rightChild = this->at(siblingPos).rightChild;

			//set new node at the emptyPos
			this->at(emptyPos) = newNode;

			//parent is now the emptyNode. Set child at emptyPos
			this->at(parentPos).numOfKeys = 0;
			this->at(parentPos).numOfChildren = 1;
			this->at(parentPos).leftChild = emptyPos;

			//find the next parent's position

			if (parentPos == 0)
			{
				//root case
				//set the root as the parent
				this->at(0) = this->at(emptyPos);
				return;
			}

			int nextParent = findParentPos(parentPos);	

			if (this->at(nextParent).numOfKeys == 1)
				oneKeyParent(parentPos, nextParent);
			else
				twoKeyParent(parentPos, nextParent);

		}
		//case: emptyNode is at the right
		else
		{
			//merge: emptyNode's right is the parent, left is the sibling
			treeNode<keyT, valueT> newNode(this->at(siblingPos).leftKey, this->at(siblingPos).leftValue, this->at(parentPos).leftKey, this->at(parentPos).leftValue);
			//set the children
			if (!isLeaf)
				newNode.numOfChildren = 3;
			else
				newNode.numOfChildren = 0;
			newNode.rightChild = this->at(emptyPos).leftChild;
			newNode.leftChild = this->at(siblingPos).leftChild;
			newNode.middleChild = this->at(siblingPos).rightChild;

			//set new node at the emptyPos
			this->at(emptyPos) = newNode;

			//parent is now the emptyNode. Set child at emptyPos
			this->at(parentPos).numOfKeys = 0;
			this->at(parentPos).numOfChildren = 1;
			this->at(parentPos).leftChild = emptyPos;

			if (parentPos == 0)
			{
				//root case
				//set the root as the parent
				this->at(0) = this->at(emptyPos);
				return;
			}

			//find the next parent's position
			int nextParent = findParentPos(parentPos);

			if (this->at(nextParent).numOfKeys == 1)
				oneKeyParent(parentPos, nextParent);
			else
				twoKeyParent(parentPos, nextParent);
		}
	}

}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::twoKeyParent(const int & emptyPos, const int & parentPos)
{
	bool isTwoKeySibling = false;

	int childArray[3] = {this->at(parentPos).leftChild, this->at(parentPos).middleChild, this->at(parentPos).rightChild};
	int emptyChild;

	for (int i = 0; i < 3; ++i)
	{
		if (childArray[i] == emptyPos)
			emptyChild = i;
		if (this->at(childArray[i]).numOfKeys == 2)
			isTwoKeySibling = true;
	}

	bool isLeaf = false;
	if (this->at(emptyPos).numOfChildren == 0)
		isLeaf = true;


	//case: no two key sibling
	if (!isTwoKeySibling)
	{
		//case: empty at left child
		if (emptyChild == 0)
		{
			//make emptyNode contain two elements
			this->at(emptyPos).numOfKeys = 2;
			if (!isLeaf)
				this->at(emptyPos).numOfChildren = 3;
			else
				this->at(emptyPos).numOfChildren = 0;

			this->at(emptyPos).leftKey = this->at(parentPos).leftKey;
			this->at(emptyPos).leftValue = this->at(parentPos).leftValue;
			this->at(emptyPos).rightKey = this->at(childArray[1]).leftKey;
			this->at(emptyPos).rightValue = this->at(childArray[1]).leftValue;
			this->at(emptyPos).middleChild = this->at(childArray[1]).leftChild;
			this->at(emptyPos).rightChild = this->at(childArray[1]).rightChild;

			//change parent
			this->at(parentPos).numOfKeys = 1;
			this->at(parentPos).numOfChildren = 2;
			this->at(parentPos).copyRightToLeft();
			this->at(parentPos).leftChild = childArray[0];
			this->at(parentPos).rightChild = childArray[2];

			//done
			return;
		}
		else if (emptyChild == 2)
		{
			//make emptyNode contain two elements
			this->at(emptyPos).numOfKeys = 2;
			if (!isLeaf)
				this->at(emptyPos).numOfChildren = 3;
			else
				this->at(emptyPos).numOfChildren = 0;

			this->at(emptyPos).rightKey = this->at(parentPos).rightKey;
			this->at(emptyPos).rightValue = this->at(parentPos).rightValue;
			this->at(emptyPos).leftKey = this->at(childArray[1]).leftKey;
			this->at(emptyPos).leftValue = this->at(childArray[1]).leftValue;
			this->at(emptyPos).leftChild = this->at(childArray[1]).leftChild;
			this->at(emptyPos).middleChild = this->at(childArray[1]).rightChild;

			//change parent
			this->at(parentPos).numOfKeys = 1;
			this->at(parentPos).numOfChildren = 2;
			this->at(parentPos).leftChild = childArray[0];
			this->at(parentPos).rightChild = childArray[2];

			//done
			return;
		}
		else
		{
			//case: empty node is at middle
			//make emptyNode contain two elements
			this->at(childArray[0]).numOfKeys = 2;
			if (!isLeaf)
				this->at(childArray[0]).numOfChildren = 3;
			else
				this->at(childArray[0]).numOfChildren = 0;
			this->at(childArray[0]).rightKey = this->at(parentPos).leftKey;
			this->at(childArray[0]).rightValue = this->at(parentPos).leftValue;
			this->at(childArray[0]).middleChild = this->at(childArray[0]).rightChild;
			this->at(childArray[0]).rightChild = this->at(emptyPos).leftChild;

			//change parent
			this->at(parentPos).numOfKeys = 1;
			this->at(parentPos).numOfChildren = 2;
			this->at(parentPos).copyRightToLeft();
			this->at(parentPos).leftChild = childArray[0];
			this->at(parentPos).rightChild = childArray[2];

			//done
			return;
		}
	}
	//case: two key sibling
	{
		//case: empty node is left child
		if (emptyChild == 0)
		{
			//case: middleChild has two keys
			if (this->at(childArray[1]).numOfKeys == 2)
			{
				this->at(emptyPos).numOfKeys = 1;
				if (!isLeaf)
					this->at(emptyPos).numOfChildren = 2;
				else
					this->at(emptyPos).numOfChildren = 0;
				this->at(emptyPos).leftKey = this->at(parentPos).leftKey;
				this->at(emptyPos).leftValue = this->at(parentPos).leftValue;
				this->at(emptyPos).rightChild = this->at(childArray[1]).leftChild;

				//change parent
				this->at(parentPos).leftKey = this->at(childArray[1]).leftKey;
				this->at(parentPos).leftValue = this->at(childArray[1]).leftValue;

				//change middle child
				this->at(childArray[1]).copyRightToLeft();
				this->at(childArray[1]).numOfKeys = 1;
				if (!isLeaf)
					this->at(childArray[1]).numOfChildren = 2;
				else
					this->at(childArray[1]).numOfChildren = 0;
				this->at(childArray[1]).leftChild = this->at(childArray[1]).middleChild;

				return;
			}
			//case: middleChild has one key, but right child has 2 keys
			else
			{
				//set emptyPos
				this->at(emptyPos).numOfKeys = 1;
				if (!isLeaf)
					this->at(emptyPos).numOfChildren = 2;
				else
					this->at(emptyPos).numOfChildren = 0;
				this->at(emptyPos).leftKey = this->at(parentPos).leftKey;
				this->at(emptyPos).leftValue = this->at(parentPos).leftValue;
				this->at(emptyPos).rightChild = this->at(childArray[1]).leftChild;

				//set parent leftKey
				this->at(parentPos).leftKey = this->at(childArray[1]).leftKey;
				this->at(parentPos).leftValue = this->at(childArray[1]).leftValue;

				//set middle child
				this->at(childArray[1]).leftKey = this->at(parentPos).rightKey;
				this->at(childArray[1]).leftValue = this->at(parentPos).rightValue;
				this->at(childArray[1]).leftChild = this->at(childArray[1]).rightChild;
				this->at(childArray[1]).rightChild = this->at(childArray[2]).leftChild;

				//set parent rightKey
				this->at(parentPos).rightKey = this->at(childArray[2]).leftKey;
				this->at(parentPos).rightValue = this->at(childArray[2]).leftValue;

				//set right child
				this->at(childArray[2]).copyRightToLeft();
				this->at(childArray[2]).numOfKeys = 1;
				if (!isLeaf)
					this->at(childArray[2]).numOfChildren = 2;
				else
					this->at(childArray[2]).numOfChildren = 0;
				this->at(childArray[2]).leftChild = this->at(childArray[2]).middleChild;
				return;

			}
		}
		//case: empty node is in the middle
		else if (emptyChild == 1)
		{
			//case: if left child has 2 keys
			if (this->at(childArray[0]).numOfKeys == 2)
			{
				//do empty node
				this->at(emptyPos).numOfKeys = 1;

				if (!isLeaf)
					this->at(emptyPos).numOfChildren = 2;
				else
					this->at(emptyPos).numOfChildren = 0;

				this->at(emptyPos).leftKey = this->at(parentPos).leftKey;
				this->at(emptyPos).leftValue = this->at(parentPos).leftValue;
				this->at(emptyPos).rightChild = this->at(emptyPos).leftChild;
				this->at(emptyPos).leftChild = this->at(childArray[0]).rightChild;

				//do parent's left key
				this->at(parentPos).leftKey = this->at(childArray[0]).rightKey;
				this->at(parentPos).leftValue = this->at(childArray[0]).rightValue;

				//do left child
				this->at(childArray[0]).numOfKeys = 1;
				if (!isLeaf)
					this->at(childArray[0]).numOfChildren = 2;
				else
					this->at(childArray[0]).numOfChildren = 0;
				this->at(childArray[0]).rightChild = this->at(childArray[0]).middleChild;

				return;
			}
			//case: right child has 2 keys
			else
			{
				//do empty node
				this->at(emptyPos).numOfKeys = 1;

				if (!isLeaf)
					this->at(emptyPos).numOfChildren = 2;
				else
					this->at(emptyPos).numOfChildren = 0;

				this->at(emptyPos).leftKey = this->at(parentPos).rightKey;
				this->at(emptyPos).leftValue = this->at(parentPos).rightValue;
				this->at(emptyPos).rightChild = this->at(childArray[2]).leftChild;

				//do parent's right key
				this->at(parentPos).rightKey = this->at(childArray[2]).leftKey;
				this->at(parentPos).rightValue = this->at(childArray[2]).leftValue;

				//do right child
				this->at(childArray[2]).copyRightToLeft();
				if (!isLeaf)
					this->at(childArray[2]).numOfChildren = 2;
				else
					this->at(childArray[2]).numOfChildren = 0;
				this->at(childArray[2]).leftChild = this->at(childArray[2]).middleChild;

				return;
			}
		}
		//Case: empty node is at the right
		else
		{
			//case: middle sibling has two keys
			if (this->at(childArray[1]).numOfKeys == 2)
			{
				//set emptyNode
				this->at(emptyPos).numOfKeys = 1;
				if (!isLeaf)
					this->at(emptyPos).numOfChildren = 2;
				else
					this->at(emptyPos).numOfChildren = 0;
				this->at(emptyPos).leftKey = this->at(parentPos).rightKey;
				this->at(emptyPos).leftValue = this->at(parentPos).rightValue;
				this->at(emptyPos).rightChild = this->at(emptyPos).leftChild;
				this->at(emptyPos).leftChild = this->at(childArray[1]).rightChild;

				//set parent
				this->at(parentPos).rightKey = this->at(childArray[1]).rightKey;
				this->at(parentPos).rightValue = this->at(childArray[1]).rightValue;

				//fix middle child
				this->at(childArray[1]).numOfKeys = 1;
				if (!isLeaf)
					this->at(childArray[1]).numOfChildren = 2;
				else
					this->at(childArray[1]).numOfChildren = 0;

				this->at(childArray[1]).rightChild = this->at(childArray[1]).middleChild;
				return;
			}
			//case: middle has one key, meaning left child has two keys
			else
			{
				//set emptyNode
				this->at(emptyPos).numOfKeys = 1;
				if (!isLeaf)
					this->at(emptyPos).numOfChildren = 2;
				else
					this->at(emptyPos).numOfChildren = 0;

				this->at(emptyPos).leftKey = this->at(parentPos).rightKey;
				this->at(emptyPos).leftValue = this->at(parentPos).rightValue;
				this->at(emptyPos).rightChild = this->at(emptyPos).leftChild;
				this->at(emptyPos).leftChild = this->at(childArray[1]).rightChild;

				//set parent right key
				this->at(parentPos).rightKey = this->at(childArray[1]).leftKey;
				this->at(parentPos).rightValue = this->at(childArray[1]).leftValue;

				//fix middle child
				this->at(childArray[1]).leftKey = this->at(parentPos).leftKey;
				this->at(childArray[1]).leftValue = this->at(parentPos).leftValue;
				if (!isLeaf)
					this->at(childArray[1]).numOfChildren = 2;
				else
					this->at(childArray[1]).numOfChildren = 0;
				this->at(childArray[1]).rightChild = this->at(childArray[1]).leftChild;
				this->at(childArray[1]).leftChild = this->at(childArray[0]).rightChild;

				//set left key of parent
				this->at(parentPos).leftKey = this->at(childArray[0]).rightKey;
				this->at(parentPos).leftValue = this->at(childArray[0]).rightValue;

				//set left child
				this->at(childArray[0]).numOfKeys = 1;
				if (!isLeaf)
					this->at(childArray[0]).numOfChildren = 2;
				else
					this->at(childArray[0]).numOfChildren = 0;

				this->at(childArray[0]).rightChild = this->at(childArray[0]).middleChild;
				return;

			}
		}
	}
}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::remove (const keyT & removeKey)
{
	//root case:
	if (this->at(0).numOfKeys == 1 && this->at(0).numOfChildren == 0)
	{
		this->at(0).numOfKeys = 0;
		numOfNodes = 0;
		return;
	}

	//find the removeKey's position
	int removeKeyPos = find(0, removeKey);


	int successorPos;

	//now find in-order successor
	//only if it is not a leaf
	if (this->at(removeKeyPos).numOfChildren != 0)
	{
		successorPos = findSuccessor(removeKeyPos, removeKeyPos, removeKey);

		//swap it
		swap(removeKeyPos, successorPos, removeKey);

	}
	else
		successorPos = removeKeyPos;

	//case 1: successorPos is a twoKey node
	if (this->at(successorPos).numOfKeys == 2)
	{
		//to remove is at the left
		if (this->at(successorPos).leftKey == removeKey)
		{
			//simply remove the left key
			this->at(successorPos).numOfKeys = 1;
			this->at(successorPos).copyRightToLeft();
			//numOfNodes--;
			return;
		}
		//to remove is at right
		else
		{
			this->at(successorPos).numOfKeys = 1;
			//numOfNodes--;			
			return;
		}
	}

	//case: successorPos is a oneKey node
	//make successorPos into empty node
	this->at(successorPos).numOfChildren = 0;
	this->at(successorPos).numOfKeys = 0;

	//look at the parent
	int parentPos = findParentPos(successorPos);
	if (this->at(parentPos).numOfKeys == 1)
		oneKeyParent(successorPos, parentPos);
	else
		twoKeyParent(successorPos, parentPos);

	//numOfNodes--;


}

template <class keyT, class valueT>
valueT twoThreeTree<keyT, valueT>::get (const keyT & getKey) const
{
	int containPos = find(0, getKey);
	//this only happens if value is found, otherwise an exception is thrown
	return (this->at(containPos)).getValue(getKey);
}

template <class keyT, class valueT>
void twoThreeTree<keyT, valueT>::print()
{
	if (numOfNodes == 0)
	{
		cout << "Tree is empty" << endl;
		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	for (int i = 0; i < numOfNodes; ++i)
	{
		cout << "Pos " << i << ": " << endl;
		if (this->at(i).numOfKeys == 1)
		{
			cout << this->at(i).numOfKeys << " keys" << endl;
			cout << "Key: " << this->at(i).leftKey << ", Value: " << this->at(i).leftValue << endl;
			cout << this->at(i).numOfChildren << " children" << endl;
			cout << "Left: " << this->at(i).leftChild << ", Right: " << this->at(i).rightChild << endl;
		}
		else if (this->at(i).numOfKeys == 2)
		{
			cout << this->at(i).numOfKeys << " keys" << endl;			
			cout << "Key1: " << this->at(i).leftKey << ", Value1: " << this->at(i).leftValue << endl;
			cout << "Key2: " << this->at(i).rightKey << ", value2: " << this->at(i).rightValue << endl;
			cout << this->at(i).numOfChildren << " children" << endl;			
			cout << "Left: " << this->at(i).leftChild << ", Middle: " << this->at(i).middleChild << ", Right: " << this->at(i).rightChild << endl;
		
		}
		cout << endl;
	}
}


