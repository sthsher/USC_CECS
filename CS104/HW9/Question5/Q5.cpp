#include <iostream> 
#include "treeNode.h"
#include "twoThreeTree.h"
#include <string>

using namespace std;


int main()
{
	twoThreeTree<string, double> tree;

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
				tree.add(ID, GPA);

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
				cout << "Student" << ID << "'s GPA is: " <<	tree.get(ID) << endl;

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
				tree.remove(ID);

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
			cout << "---Program End---" << endl;
			return 0;
		}
		else if (choice = 'p' || choice == 'P')
		{
			tree.print();
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


/*
	twoThreeTree<int, int> test;


	test.add(50, 500);
	test.add(30, 300);
	test.add(10, 100);
	test.add(20, 200);
	test.add(40, 400);
	test.add(65, 650);
	test.add(90, 900);
	test.add(60, 600);
	test.add(70, 700);
	test.add(80, 800);
	test.add(100, 1000);

	test.print();

	cout << "Getting: " << endl;
	while (true)
	{
		int temp;
		cout << "Get:   "; cin >> temp;

		if (temp == 0)
			break;

		cout << "Value: " << test.get(temp) << endl;
	}



	while (true)
	{
		int temp;
		cout << "Remove: "; cin >> temp;

		if (temp == 0)
			break;

		test.remove(temp);

		test.print();

		cout << endl << "**************" << endl << endl;

	}	

	return 0;

	*/
}