#include <string>
#include <iostream>
#include <cmath>

#include "food.h"


using namespace std;

food::food()
{
	content = "";
}

food::food(string c)
{
	content = c;
}

food::~food()
{

}

int const food::hash() const
{
	int length = content.size();

	int value = 1;

	for (int i = 0; i < length; ++i)
	{
		value = abs(value*(int)content[i]);
	}

	return value;

}

bool food::operator==(const food & other)
{
	if (this->content == other.content)
		return true;
	return false;
}
