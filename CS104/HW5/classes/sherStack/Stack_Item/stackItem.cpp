#include "stackItem.h"
#include <stdexcept>
using namespace std;


stackItem::stackItem()
{
	//by default, it is a null char
	bool isVector = false;
	vectorItem = NULL;
	operatorItem = '\0';
}

stackItem::stackItem(const stackItem& other)
{
	isVector = other.isVector;
	vectorItem = other.vectorItem;
	operatorItem = other.operatorItem;
}


stackItem::stackItem(char c)
{
	isVector = false;
	operatorItem = c;
	vectorItem = NULL;
}
stackItem::stackItem(mathVector v)
{
	isVector = true;
	operatorItem = '\0';
	vectorItem = new mathVector(v);

}

bool stackItem::checkType()
{
	return isVector;
}

mathVector stackItem::returnVector()
{
	return *vectorItem;
}

char stackItem::returnOperator()
{
	return operatorItem;
}