#include <iostream>
#include <cmath>
#include "userKey.h"
using namespace std;

userKey::userKey()
{
	content = "";
}

userKey::userKey(string s)
{
	content = s;
}

userKey::~userKey()
{

}

int userKey::hash()
{
	int length = content.size();
	int value = 1;
	
	for (int i = 0; i < length; ++i)
	{
		value = abs(value*(int)content[i]);
	}

	return value;
}


bool userKey::operator== (userKey const & other)
{
	if (this->content == other.content)
		return true;
	return false;
}
bool userKey::operator!= (userKey const & other)
{
	if (this->content != other.content)
		return true;
	return false;
}