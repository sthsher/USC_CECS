#ifndef stackItem_H_
#define stackItem_H_

#include "../../mathVector/mathVector.h"
#include <string>

using namespace std;

class stackItem
{
public:

	stackItem();
	stackItem(const stackItem& other);	//copycat
	stackItem(char c);			//constructs with operator c
	stackItem(mathVector v);	//constructs with vector v


	bool checkType();			//returns true if a vector, otherwise returns false
	mathVector returnVector();	//gives the vector
	char returnOperator();		//gives the operator


private:

	bool isVector;				//default true means it is a vector, if false, means it is a operator
	mathVector *vectorItem;		//stores vector
	char operatorItem;			//stores operator

};


#endif //stackItem_H_