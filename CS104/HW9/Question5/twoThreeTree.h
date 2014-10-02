#ifndef twoThreeTree_H_
#define twoThreeTree_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include "treeNode.h"
#include "quickSort/quickSort.h"

using namespace std;

template <class keyT, class valueT>
class twoThreeTree: private vector<treeNode<keyT, valueT> >
{
	public:
		twoThreeTree();
		~twoThreeTree();

		void add (const keyT & addKey, const valueT & addValue);
		void remove (const keyT & removeKey);
		valueT get (const keyT & getKey) const;

		//debugging
		void print();

	private:
		void twoKeyParent(const int & currentPos, const int & parentPos);
		void oneKeyParent(const int & currentPos, const int & parentPos);
		void swap(int posA, int posB, keyT targetKey);
		int findSuccessor(const int & startingPos, const int & currentPos, const keyT & targetKey) const;
	
		int find(int currentPos, const keyT & targetKey) const;
		
		int traverseTo(int currentPos, const keyT & targetKey);
		void splitLeaf(const int & currentPos, const keyT & addKey, const valueT & addValue);
		void splitInternal(const int & currentPos, const keyT & addKey, const valueT & addValue, int childrenPos[]);
		void splitRoot(const keyT & addKey, const valueT & addValue, int childrenPos[]);
		
		int findParentPos(const int & currentPos);

		int numOfNodes;

};

#include "twoThreeTree.hpp"

#endif //twoThreeTree_H_