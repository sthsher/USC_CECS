
template <class keyT, class valueT>
bool treeNode<keyT, valueT>::contains(const keyT & targetKey) const
{
	if (leftKey == targetKey)
		return true;
	else if (numOfKeys == 2 && rightKey == targetKey)
		return true;
	else
		return false;
}

template <class keyT, class valueT>
valueT treeNode<keyT, valueT>::getValue(const keyT & targetKey) const
{
	if (targetKey == leftKey)
		return leftValue;
	else
		return rightValue;

	//this should never be reached, but if so, throw an exception
	throw logic_error("EXCEPTION: USED getValue FUNCTION WHEN NOT CONFIRMED IT CONTAINS TARGETKEY");
}


template<class keyT, class valueT>
void treeNode<keyT, valueT>::copyLeftToRight()
{
	rightKey = leftKey;
	rightValue = leftValue;
}
template<class keyT, class valueT>
void treeNode<keyT, valueT>::copyRightToLeft()
{
	leftKey = rightKey;
	leftValue = rightValue;
}

/*

template <class keyT, class valueT>
treeNode<keyT, valueT>::treeNode (const keyT & key, const valueT & value)
{
	numOfKeys = 1;
	leftKey = key;
	leftValue = value;
	numOfChildren = 0;
	leftChild = 0;
	middleChild = 0;
	rightChild = 0;
}

template <class keyT, class valueT>
treeNode<keyT, valueT>::treeNode (const keyT & lKey, const valueT & lValue,
			const keyT & rKey, const valueT & rValue)
{
	numOfKeys = 2;
	leftKey = lKey;
	leftValue = lValue;
	rightKey = rKey;
	rightValue = rValue;
	numOfChildren = 0;
	leftChild = 0;
	middleChild = 0;
	rightChild = 0;
}

*/

template <class keyT, class valueT>
treeNode<keyT, valueT>::treeNode (const keyT & key, const valueT & value) :
	leftKey( key ), leftValue( value )
{
	numOfKeys = 1;
	numOfChildren = 0;
	leftChild = 0;
	middleChild = 0;
	rightChild = 0;
}

template <class keyT, class valueT>
treeNode<keyT, valueT>::treeNode 	(const keyT & lKey, const valueT & lValue,
									 const keyT & rKey, const valueT & rValue) :
	leftKey( lKey ), leftValue( lValue ), rightKey( rKey ), rightValue( rValue )
{
	numOfKeys = 2;
	numOfChildren = 0;
	leftChild = 0;
	middleChild = 0;
	rightChild = 0;
}

template <class keyT, class valueT>
treeNode<keyT, valueT>::~treeNode()
{

}


template <class keyT, class valueT>
treeNode<keyT, valueT> treeNode<keyT, valueT>::operator= (treeNode<keyT, valueT> const & other)
{
	this->numOfKeys = other.numOfKeys;
	this->numOfChildren = other.numOfChildren;
	this->leftChild = other.leftChild;
	this->middleChild = other.middleChild;
	this->rightChild = other.rightChild;
	this->leftKey = other.leftKey;
	this->rightKey = other.rightKey;
	this->leftValue = other.leftValue;
	this->rightValue = other.rightValue;

	return *this;
}
