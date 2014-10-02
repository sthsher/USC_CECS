#include <iostream>
#include <string>
#include "Q3hashTable.h"
#include "student.h"
#include <stdexcept>
#include <fstream>

using namespace std;



int main()
{

	hashTable<student, double> studentTable;

	while (true)
	{
		cout << "----------------------------------" << endl;
		cout << "  Welcome to Stephen's Gradebook  " << endl;
		cout << "----------------------------------" << endl;
		cout << "Please select an action:" << endl;
		cout << "(1) Add a student to the records" << endl;
		cout << "(2) Search for a student's GPA" << endl;
		cout << "(3) Remove a student from the records" << endl;
		cout << "(Q) Quit" << endl << endl;

		char choice;
		cout << "Choice: "; cin >> choice; cout << endl << endl;;
		if (choice == '1')
		{
			string ID;
			double GPA;
		
			cout << "----------------------------" << endl;
			cout << "  Add a student to records  " << endl;
			cout << "----------------------------" << endl;
			cout << "Please enter the student's ID:  "; cin >> ID;
			cout << "Please enter the student's GPA: "; cin >> GPA; cout << endl;
			
			try
			{
				student newStudent(ID);

				studentTable.add(newStudent, GPA);

				cout << "---Student Successfully Added---" << endl;
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			}
			catch(logic_error & e)
			{
				cout << e.what() << endl;
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			}

		}
		else if (choice == '2')
		{
			string ID;
		
			cout << "-------------------------------------" << endl;
			cout << "  Search for a student from records  " << endl;
			cout << "-------------------------------------" << endl;
			cout << "Please enter the student's ID:  "; cin >> ID;
			
			try
			{
				student getStudent(ID);
				cout << "Student" << ID << "'s GPA is: " <<	studentTable.get(getStudent) << endl;

				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			}
			catch(logic_error & e)
			{
				cout << e.what() << endl;
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			}

		}
		else if (choice == '3')
		{
			string ID;
		
			cout << "---------------------------------" << endl;
			cout << "  Remove a student from records  " << endl;
			cout << "---------------------------------" << endl;
			cout << "Please enter the student's ID:  "; cin >> ID; cout << endl;
			
			try
			{
				student removeStudent(ID);

				studentTable.remove(removeStudent);

				cout << "---Student Successfully Removed---" << endl;
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			}
			catch(logic_error & e)
			{
				cout << e.what() << endl;
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			}
		}
		else if (choice == 'q' || choice == 'Q')
		{
			break;
		}
		else if (choice = 'p' || choice == 'P')
		{
			studentTable.print();
		}
		else
		{
			cout << "Error: Invalid input" << endl;
			char dump;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');

		}
	}

	cout << "---Program End---" << endl;
 

	return 0;
}