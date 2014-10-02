#ifndef mathVector_H_
#define mathVector_H_

#include <string>
using namespace std;

class mathVector
{
public:
	mathVector();
	mathVector(const mathVector& other);	//copy constructor
	mathVector(double n);					//takes a double and makes a 1D vector with the value
	mathVector(string s);					//takes a string and converts into a vector

	string toString();

	//operators: they do what you expect them to do
	mathVector operator+ (mathVector const & other);
	mathVector operator- (mathVector const & other);
	mathVector operator* (mathVector const & other);
	bool operator== (mathVector const & other);
	bool operator!= (mathVector const & other);
	mathVector & operator= (mathVector const & other);
	double operator[] (int index);


private:
	int dimension;							//holds the number of dimensions the vector has
	double *vectorPtr;						//will contain an array with the numbers of the vector

};

#endif //mathVector_H_