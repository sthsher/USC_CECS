#include <string>
#include <cmath>

#include "word.h"


using namespace std;

word::word()
{
	content = "";
}

word::word(string c)
{
	content = c;
}

word::~word()
{

}

int const word::hash() const
{
	int length = content.size();

	int value = 1;

	for (int i = 0; i < length; ++i)
	{
		value = abs(value*(int)content[i]);
	}

	return value;

}

bool word::operator==(const word & other)
{
	if (this->content == other.content)
		return true;
	return false;
}
