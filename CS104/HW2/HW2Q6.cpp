#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "stringLL.h"
using namespace std;

//Returns the filename inputted by the user
string getFileName()
{

	string fileName;

	cout<<endl;
	cout<<"Please enter the name of the file containing the array"<<endl;
	cout<<"Be sure to include \".txt\" in the file name"<<endl<<endl;
	cout<<"File Name: ";
	cin>>fileName;

				//fileName = "stringFile.txt";

	cout<<endl<<"The file name you have inputted is: "<<fileName<<endl<<endl;

	return fileName;

}

//Adds the new string s to the end of the linked list
//*****************************************************
//				    Question 5 Answer
//*****************************************************
void addtoLL(string s, stringLL **last, stringLL **first)
{
	//Make a temp element
	stringLL *temp = new stringLL;
	//Data is string s
	temp->setData(s);

	//This is the first object in the linked list
	if (*first == NULL)
	{
		//the first and last are both this object
		*first = temp;
		*last = temp;
	}
	//This is not the first object
	else
	{
		//link the last's next pointer to this address
		(*last)->setNext(temp);
		//set the last pointer to be this object, the new last
		*last = temp;
		//temp's next pointer is automatically set as NULL in the constructor
	}


}

//Reads the file <fileName> and makes a linked list
void readFile(string fileName, stringLL **fPtr, stringLL **lPtr)
{
	ifstream fin;
	string dump;

	fin.open(fileName.c_str());

	if(fin == NULL)
	{
		cout<<"Error: File not found, please check the file or the spelling"<<endl;
		cout<<"---Exiting Program---"<<endl;
		exit(1);
	}

	while (true)
	{
		if (fin.eof())
		{
			fin.close();
			return;
		}
		
		getline(fin,dump);

		//Adds new string dump to the Linked List
		addtoLL(dump, lPtr, fPtr);
		
	}
}

//Recursion to output the list backwards
void sayBackwards(stringLL *ptr)
{
	//Base case: is at the last element: output the element
	if (ptr->returnNext() == NULL)
	{
		cout<<ptr->returnData()<<" ";
		return;
	}

	//Keep going through the list
	sayBackwards(ptr->returnNext());

	//Output the current element
	cout<<ptr->returnData()<<" ";

	return;
}

int main()
{

//******************************************************************************************************
//												Declarations
//	
	string fileName;			//name of file containing the string list

	stringLL *first = NULL;		//pointer to first element in linked list
	stringLL *last = NULL;		//pointer to last element in linked list

	//Need a pointer-pointer in order to pass-by-pointer when adding elements
	stringLL **fPtr = &first;	//a pointer to the pointer first
	stringLL **lPtr = &last;	//a pointer to the pointer last

	char foo;					//Nothing special, just for a pause in the program

//******************************************************************************************************
//												Preparations
//	
	//Get fileName
	fileName = getFileName();

	//Read the file and make the linked list
	readFile(fileName, fPtr, lPtr);

//******************************************************************************************************
//												Outputs
//	
	stringLL *x;	//a temp object to output the list's data

	cout<<"The string from the file "<<fileName<<" is as follows:"<<endl<<endl;

	//loops until it hits the last element
	for (x = first; x != NULL; x = x->returnNext())
	{
		cout<<(x->returnData())<<" ";
	}

	cout<<endl<<endl<<"Now the file will output backwards"<<endl;
	cout<<"Enter any key to continue: ";
	cin>>foo;
	cin.ignore(256,'\n');
	cout<<endl;

	//Recursion to output the list backwards
	sayBackwards(first);

	cout<<endl<<endl;

	cout<<"---Program End---"<<endl;
	return 0;

}