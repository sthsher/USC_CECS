#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

#include "Classes/student.h"
#include "Classes/heap.h"

using namespace std;

//takes first name and last name and makes the entire full name in one string
string constructName(string firstName, string lastName)
{
		string fullName;

		stringstream ss;
		ss.str(firstName + " " + lastName);
		fullName = ss.str();

		return fullName;
}

void addStudent(heap<student> *studentHeap)
{
	string fName;
	string lName;
	string fullName;
	string id;

	cout << "-----------------" << endl;
	cout << "| Add a Student |" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << " Please enter the student's information" << endl;
	cout << "----------------------------------------------------" << endl;

	cout << "Student First Name: "; cin >> fName;
	cout << "Student Last Name:  "; cin >> lName;
	cout << "Studnet ID:         "; cin >> id; cout << endl;

	fullName = constructName(fName, lName);

	//make a new student and add it to the heap
	student temp(fullName, id);

	studentHeap->add(temp);

	cout << "---Student Record Successfully Added---" << endl;
	char dump;
	cout << "Enter any key to continue"; cin >> dump;
	cin.ignore(256, '\n');
}

int main()
{

	heap<student> *studentHeap = new heap<student>(2, false);

	while (true)
	{

		cout << "-----------------------------" << endl;
		cout << "| Student Records Main Menu |" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << " Please choose an action: " << endl;
		cout << " 1) Enter new student record" << endl;
		cout << " 2) Remove student record" << endl;
		cout << " 3) Quit" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << endl;

		cout << "The current alphabetically first student is:" << endl;
		try
		{
			//peek top student
			(studentHeap->peek()).printStudent();
			cout << endl;
		}
		catch (logic_error const &e)
		{
			cout << e.what() << endl;
		}

		char choice;
		cout << "Choice: "; cin >> choice; cout << endl;

		if (choice == '1')
		{
			addStudent(studentHeap);
		}
		else if (choice == '2')
		{
			try
			{
				studentHeap->remove();
				cout << "---First Student Successfully Removed---" << endl;
			}
			catch (logic_error &e)
			{
				cout << e.what() << endl;
			}

			char dump;
			cout << "Enter any key to continue"; cin >> dump;
			cin.ignore(256, '\n');


		}
		else if (choice == '3')
		{
			break;
		}
		else
		{
			cout << "Error: invalid input" << endl;
			cin.ignore(256, '\n');
		}

	}
	

	cout << "--- Program End ---" << endl;
	return 0;
}