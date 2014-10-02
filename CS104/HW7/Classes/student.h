#ifndef student_H_
#define student_H_

#include <iostream>
#include <string>

using namespace std;

class student
{
public:
	student();
	student(string n, string i);
	~student();

	void setName (const string &s);
	string getName ();

	void setID (const string &i);
	string getID ();

	void printStudent() const;

	//for operators, string class allows direct comparison using > and <. Therefore the overloading
	//turned out to be very simple
	bool operator< (student const & other);
	bool operator> (student const & other);
	bool operator== (student const & other);
	bool operator!= (student const & other);
	bool operator<= (student const & other);
	bool operator>= (student const & other);

private:
	string fullName;
	string ID;



};

#include "student.hpp"

#endif //student_H_