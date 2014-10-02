#ifndef treeNode_H_
#define treeNode_H_

#include <iostream>
#include <stdexcept>

using namespace std;

template <class keyT, class valueT>
class treeNode
{
	public:
		//constructors
		//for one key
		treeNode (const keyT & key, const valueT & value);
		//for two keys
		treeNode (const keyT & leftKey, const valueT & leftValue,
					const keyT & rightKey, const valueT & rightValue);
		~treeNode();

		//test to see if node contains target key
		bool contains(const keyT & targetKey) const;

		//only used if node has target key
		//false is left, true is right
		valueT getValue(const keyT & targetKey) const;

		int numOfKeys;
		keyT leftKey, rightKey;
		valueT leftValue, rightValue;
		int numOfChildren;
		int leftChild, middleChild, rightChild;


		treeNode<keyT, valueT> operator= (treeNode<keyT, valueT> const & other);

		//Utilities
		void copyLeftToRight();
		void copyRightToLeft();



};

#include "treeNode.hpp"

#endif //treeNode_H_