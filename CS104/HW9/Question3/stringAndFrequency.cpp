#include "stringAndFrequency.h"

stringAndFrequency::stringAndFrequency()
{
	content = "";
	frequency = 1;
}

stringAndFrequency::stringAndFrequency(string s)
{
	content = s;
	frequency = 1;
}

stringAndFrequency::stringAndFrequency(string s, int f)
{
	content = s;
	frequency = f;
}


stringAndFrequency::~stringAndFrequency()
{

}

void stringAndFrequency::setContent(string s)
{
	content = s;
}


void stringAndFrequency::incrementFrequency()
{
	++frequency;
}


string stringAndFrequency::getContent() const
{
	return content;
}


int stringAndFrequency::getFrequency()
{
	return frequency;
}