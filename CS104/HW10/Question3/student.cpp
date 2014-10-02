#include <string>
#include <iostream>
#include <cmath>

#include "student.h"


using namespace std;

student::student()
{
	content = "";
}

student::student(string c)
{
	content = c;
}

student::~student()
{

}

int const student::hash() const
{
	int length = content.size();

	int value = 1;

	for (int i = 0; i < length; ++i)
	{
		value = abs(value*(int)content[i]);
	}

	return value;

}

bool student::operator==(const student & other)
{
	if (this->content == other.content)
		return true;
	return false;
}
