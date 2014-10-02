#include <iostream>
#include <string>
#include "stringLL.h"
using namespace std;

stringLL::stringLL()
{
	data = "";
	next = NULL;
}

stringLL::~stringLL()
{

}

void stringLL::setData(string s)
{
	data = s;
}

void stringLL::setNext(stringLL *n)
{
	next = n;
}

string stringLL::returnData()
{
	return data;
}

stringLL* stringLL::returnNext()
{
	return next;
}
