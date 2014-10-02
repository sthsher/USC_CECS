#include "mathVector.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

//test if the dimension is 1. Honestly this is just to make the code look neater
bool isScalar(int dimension)
{
	if (dimension == 1)
		return true;
	return false;
}

//default stuff
mathVector::mathVector()
{
	dimension = 1;
	vectorPtr = NULL;
}

//copy constructor
mathVector::mathVector(const mathVector& other) : dimension(other.dimension), vectorPtr(other.vectorPtr)
{ }

mathVector::mathVector(double n)
{
	dimension = 1;
	vectorPtr = new double[1];
	vectorPtr[0] = n;
}

mathVector::mathVector(string s)
{
	dimension = 1;

	//counts the number of commas, and get the dimension
	for (int i = 0; s[i] != ']'; i++)
	{
		if (s[i] == ',')
			dimension++;
	}
																//debugging
																//cout << "Dimension: " << dimension << endl;

	//creates a double array of corresponding size
	vectorPtr = new double[dimension];


	//now get the individual vector dimensions in string

	int tempCounter = 0;		//counter to create the string of the number
	int vectorCounter = 0;		//counter to move in the vectorPtr array

	string temp = "";			//will be constructed into each individual number

	//goes through entire string
	for (int i = 1; s[i] != ']'; i++)
	{

		//base case: next char is a comma or the ]
		if (s[i+1] == ',' || s[i+1] == ']')
		{
			//get the current char in
			temp[tempCounter] = s[i];
			tempCounter++;

			//set the next char as the end of the string
			temp[tempCounter] = '\0';

			//convert temp into double
			double num = atof(temp.c_str());

			//set number into array and increment counter to get ready to set the next number
			vectorPtr[vectorCounter] = num;
			vectorCounter++;

			//reset the temp string to be all \0.
			//since manipulating it converts it into a char array, string functions no longer work
			//eg string.clear() or string.erase() does not work, so do it manually
			for (int z = 0; z < tempCounter+1; ++z)
			{
				temp[z] = '\0';
			}
			//reset counter
			tempCounter = 0;

			//if there is more numbers (meaning it is a comma and not a ]), then increment i to skip the comma
			if(s[i+1] == ',')
				i++;
		}
		else
		{
			//simple copying of the string
			temp[tempCounter] = s[i];
			tempCounter++;
		}
	}
}

string mathVector::toString()
{

	string vectorString;	//the final string to output
	string tempString;		//stores each number temporarily

	string *stringPtr;
	stringPtr = new string[dimension];	//create a string array to hold each number as strings

	//conversts each number in the vector array into a string and put it in the string array
	for (int i = 0; i < dimension; i++)
	{
		stringstream ss;
		ss << vectorPtr[i];
		tempString = ss.str();
		stringPtr[i] = tempString;

		//reset the string
		tempString.erase(tempString.begin(), tempString.end());
		tempString[0] = '\0';

	}

	stringstream ss;
	//add square brackets
	ss.str("[");

	//update vectorString
	vectorString = ss.str();

	//adds each element into the final string, except for the last element because we're not going to add a comma at the end
	for (int i = 0; i < dimension-1; i++)
	{
		//add the element and add a comma
		ss.str(vectorString + stringPtr[i] + ",");
		//update the vectorString to be reused
		vectorString = ss.str();
	}

	//add the last element, and finishi with a square bracket
	ss.str(vectorString + stringPtr[dimension-1] + "]");

	//update the vectorstring and return it
	vectorString = ss.str();									//debugging
																//cout << "real string: " << vectorString << endl;

	delete []stringPtr;

	return vectorString;

}

//makes a new vector called result, and does computation accordingly
mathVector mathVector::operator+ (mathVector const & other)
{

	if(other.dimension != this->dimension)
	{
		throw logic_error("Exception error: unable to add vectors with different dimensions");
	}
	else
	{
		mathVector result;
		result.dimension = other.dimension;
		result.vectorPtr = new double[result.dimension];

		for (int i = 0; i < other.dimension; ++i)
		{
			(result.vectorPtr)[i] = (other.vectorPtr)[i] + (this->vectorPtr)[i];
		}
		return result;
	}

}

//makes a new vector called result, and does computation accordingly
mathVector mathVector::operator- (mathVector const & other)
{
	


	if(other.dimension != this->dimension)



	{
		throw logic_error("Exception error: unable to subtract vectors with different dimensions");
	}
	else
	{
		mathVector result;
		result.dimension = other.dimension;
		result.vectorPtr = new double[result.dimension];
		for (int i = 0; i < other.dimension; ++i)
		{
			(result.vectorPtr)[i] = (this->vectorPtr)[i] - (other.vectorPtr)[i];
		}
		return result;
	}
}

//makes a new vector called result, and does computation accordingly
mathVector mathVector::operator* (mathVector const & other)
{

	bool isScalarThis = isScalar(this->dimension);
	bool isScalarOther = isScalar(other.dimension);

	//if both vectors are of different dimensions:
	if(other.dimension != this->dimension)
	{
		if(isScalarThis == true || isScalarOther == true)
		{
			//one of them is scalar, so it's ok
		}
		else
		{
			throw logic_error("Exception error: unable to add vectors with different dimensions");
		}
	}
	
	//if this is a scalar, do scalar multiplcation
	if (isScalarThis == true && isScalarOther == false)
	{
		mathVector result;
		result.dimension = other.dimension;
		result.vectorPtr = new double[result.dimension];

		int scalarMultiplier = (this->vectorPtr)[0];
		//this vector is a scalar, so scalar multiplcation
		for (int i = 0; i < other.dimension; ++i)
		{
			(result.vectorPtr)[i] = (scalarMultiplier)*((other.vectorPtr)[i]);
		}
		return result;
	}

	//other is a scalar, do scalar multiplcation
	else if (isScalarThis == false && isScalarOther == true)
	{
		mathVector result;
		result.dimension = this->dimension;
		result.vectorPtr = new double[result.dimension];

		int scalarMultiplier = (other.vectorPtr)[0];
		//other vector is scalar
		for (int i = 0; i < this->dimension; ++i)
		{
			(result.vectorPtr)[i] = (scalarMultiplier)*((this->vectorPtr)[i]);
		}
		return result;
	}

	else //both vectors have the same dimension, so dot product
	{
		double product = 0;
		for (int i = 0; i < other.dimension; ++i)
		{
			product += ((other.vectorPtr)[i])*((this->vectorPtr)[i]);
		}

		mathVector result(product);
		return result;
	}

	//exception thrown, return nonesense value
	mathVector nonesense(3.14);
	return nonesense;

}

//simple test to see if they are equal
bool mathVector::operator== (mathVector const & other)
{
	if (other.dimension != this->dimension)
	{
		//not the same size, therefore false anyways
		return false;
	}

	for (int i = 0; i < other.dimension; ++i)
	{
		//if any one of the elements are not equal, then return true
		if ((other.vectorPtr)[i] != (this->vectorPtr)[i])
			return false;
	}

	return true;
}

bool mathVector::operator!= (mathVector const & other)
{
	if (other.dimension == this->dimension)
	{
		//if same size, then reutrn true
		return true;
	}

	for (int i = 0; i < other.dimension; ++i)
	{
		//if any one of the elements are equal, then return true: it does not equal
		if ((other.vectorPtr)[i] == (this->vectorPtr)[i])
			return true;
	}

	return false;
}

//reset everything about this vector and make it equal to other
mathVector & mathVector::operator= (mathVector const & other)
{
	if (this == &other)
		return *this;
	//delete old vector
	delete this->vectorPtr;

	this->dimension = other.dimension;

	this->vectorPtr = new double[this->dimension];

	for (int i = 0; i < other.dimension; ++i)
	{
		(this->vectorPtr)[i] = (other.vectorPtr)[i];
	}

	return *this;
}

//access the element
double mathVector::operator[] (int index)
{
	//if they want to access index:1, it is at position 0, therefore minus 1
	index--;

	if (index >= dimension || index < 0)
	{
		throw logic_error("Exception error: Access out of bounds");
	}

	return vectorPtr[index];

}
