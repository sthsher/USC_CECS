#include <iostream>
#include <iomanip>
#include "classes/sherStack/sherStack.h"
#include "classes/sherStack/Stack_Item/stackItem.h"
#include "classes/mathVector/mathVector.h"
#include <stdexcept>
#include <stdlib.h>

using namespace std;

//just text instructions on formatting for the code.
void instructions()
{
	cout<<"--------------" << endl;
	cout<<"|Instructions|" << endl;
	cout<<"*---------------------------------------------------------*"<<endl;
	cout<<"|"<<setw(57)<<" "																	<<"|"<<endl;
	cout<<"|"<<setw(57)<<" The calculator must follow a strict format, otherwise"				<<"|"<<endl;
	cout<<"|"<<setw(57)<<" exceptions will be thrown at you."									<<"|"<<endl;
	cout<<"|"<<setw(57)<<" "																	<<"|"<<endl;
	cout<<"|"<<setw(57)<<" Format for writing a vector:"										<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - Must start and end with square brackets: \"[]\""					<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - Each element of the vector must be separated"						<<"|"<<endl;
	cout<<"|"<<setw(57)<<"   by a comma"														<<"|"<<endl;	
	cout<<"|"<<setw(57)<<" - There should be no spaces in the vector"							<<"|"<<endl;
	cout<<"|"<<setw(57)<<"   (eg. [23.2, 42.5])"												<<"|"<<endl;	
	cout<<"|"<<setw(57)<<"   is incorrect because of the space after the comma)"				<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - Make sure you enter numbers, not letters or"						<<"|"<<endl;
	cout<<"|"<<setw(57)<<"   other weird stuff"													<<"|"<<endl;	
	cout<<"|"<<setw(57)<<" "																	<<"|"<<endl;
	cout<<"|"<<setw(57)<<" Format for writing the equation"										<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - When writing vectors, follow the vector formatting"				<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - Do not put any spaces inbetween operators"							<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - The program only calculates addition +, subtraction -"				<<"|"<<endl;
	cout<<"|"<<setw(57)<<"   and multiplcation *"												<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - Scalar multiplcation will work (eg a scalar "						<<"|"<<endl;
	cout<<"|"<<setw(57)<<"   multiplied by a vector)"											<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - Multiplcation of vectors of the same size will"					<<"|"<<endl;
	cout<<"|"<<setw(57)<<"   produce a dot product"												<<"|"<<endl;
	cout<<"|"<<setw(57)<<" - Add and subtract vectors of the same size"							<<"|"<<endl;
	cout<<"|"<<setw(57)<<" "																	<<"|"<<endl;
	cout<<"*---------------------------------------------------------*"							<<endl<<endl;

	char foo;
	cout << "Enter any key to return to the main menu: "; cin>>foo; cout << endl;
	cin.ignore(256, '\n');

}

//test to see if it is a valid character
bool isValidChar(char c)
{
	char valid[] = {'0','1','2','3','4','5','6','7','8','9','+','-','*','[',']','(',')','.',','};

	for (int k = 0; k < 19; ++k)
	{
		if (c == valid[k])
			return true;
	}
	return false;
}

//test to see if it is an operator
bool isOperatorChar(char c)
{
	char operators[] = {'+','-','*','[',']','(',')',','};

	for (int k = 0; k < 8; ++k)
	{
		if (c == operators[k])
			return true;
	}
	return false;

}

//tests if the char is one that needs to be pushed
//')' is an exception so don't search for that
bool isPushOperator(char c)
{
	char operators[] = {'+','-','*','('};
	
	for (int k = 0; k < 4; ++k)
	{
		if (c == operators[k])
			return true;
	}
	return false;
}

//test to see if it is a number or a negative sign number
bool isNumber(char c)
{
	char operators[] = {'0','1','2','3','4','5','6','7','8','9','-'};
	
	for (int k = 0; k < 11; ++k)
	{
		if (c == operators[k])
			return true;
	}
	return false;
}

//returns a vector that is the result of an operation
mathVector doOperation(mathVector vectorOne, mathVector vectorTwo, char operation)
{
	//order matters. vectorOne is on the left, and vectorTwo is on the right
	if (operation == '+')
	{
		return (vectorOne + vectorTwo);
	}
	else if (operation == '-')
	{
		return (vectorOne - vectorTwo);
	}
	else if (operation == '*')
	{
		return (vectorOne * vectorTwo);
	}
	else
	{
		throw logic_error("Exception error: Unexpected operation in equation");
		return vectorOne;
	}

}

//stores the appropriate info in a vector or char from the item
bool storeItemInfo(char &c, mathVector &vec, stackItem item)
{
	if (item.checkType() == true)
	{
		//a vector;
		vec = item.returnVector();
		return true;
	}
	else
	{
		c = item.returnOperator();
		return false;
	}
}

//test to see if item is what we want it to be
bool testItem(string type, stackItem item)
{
	if (type == "operator")
	{
		if (item.checkType() == true)
		{
			//want an operator, but a vec
			throw logic_error("Exception error: Unexpected vector when expecting an operator");
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (type == "vector")
	{
		if (item.checkType() == false)
		{
			//want a vector, but an operator
			throw logic_error("Exception error: Unexpected operator when expecting a vector");
			return false;
		}
		else
		{
			return true;
		}
	}

	throw logic_error("Stephen check your spelling");
	return false;
}

//pass in a stack with operations and vectors, do the operation, and return the resulting vector
mathVector calculateStack(sherStack<stackItem> stack, int numOfItems)
{
	//if there are 5 elements, there are 2 operations. The relationship is elements-1/2
	int numOfOperations = (numOfItems-1)/2;

	//each operation requires three items: two vectors and an operator
	mathVector result;		//holds the result of operation
	mathVector vectorOne;	//holds first vector
	mathVector vectorTwo;	//holds second vector
	char operation;			//holds the operation we need to do

	stackItem tempItem;

	//does the operation the appropriate number of times
	for (int i = 0; i < numOfOperations; ++i)
	{
		//get the first three items
		//if it's not what we expect, throw an exception
		try
		{
			tempItem = stack.top(); stack.pop();
			testItem("vector", tempItem);
		}
		catch(logic_error const &e)
		{cout << e.what() << endl;}


		//got the first vector
		vectorOne = tempItem.returnVector();

		//now get the operator
		try
		{
			tempItem = stack.top(); stack.pop();
			testItem("operator", tempItem);
		}
		catch(logic_error const &e)
		{cout << e.what() << endl;}

		operation = tempItem.returnOperator();

		//now get the second vector
		try
		{
			tempItem = stack.top(); stack.pop();
			testItem("vector", tempItem);
		}
		catch(logic_error const &e)
		{cout << e.what() << endl;}

		vectorTwo = tempItem.returnVector();

		//get the result vector by doing the operation
		result = doOperation(vectorOne, vectorTwo, operation);

		//push it back in the tempstack, and repeat process
		stackItem resultItem(result);
		stack.push(resultItem);
	}

	//at this point stack only has one item: the final result in the parenthesis. top and pop it, and return it
	result = stack.top().returnVector();

	stack.pop();
	return result;

}

//reformats the equation to have () at beginning and end
string reformatEquation(string originalEquation, int &size)
{
	string newEquation;
	newEquation[0] = '(';
	for (int i = 0; i < size; ++i)
	{
		newEquation[i+1] = originalEquation[i];
	}

	newEquation[size+1] = ')';
	newEquation[size+2] = '\0';

	size = size + 2;

	return newEquation;
}

//all the calculations are contained in here
void calculate()
{
	string equation;	//stores the equation to compute in a string

	cout << "Please enter the equation you wish to calculate:" << endl;
	cout << "Equation: "; cin >> equation; cout << endl;					//debugging:
																			//equation = "(([1.1,2.2]+[3.3,4.4])*2)*[1,1]";
																			//cout << equation << endl;

	//stores the size of the string
	int size = equation.size();

	//do checks for parenthesis at beginning and end
	//first check if there are an equal number of ( and ) operators
	//same with [ and ]
		int openCounter = 0;
		int closeCounter = 0;
		int squareOpenCounter = 0;
		int squareCloseCounter = 0;

		for (int i = 0; i < equation.size(); ++i)
		{
			if (equation[i] == '(')
				openCounter++;
			if (equation[i] == ')')
				closeCounter++;
			if (equation[i] == '[')
				squareOpenCounter++;
			if (equation[i] == ']')
				squareCloseCounter++;
		}

		if (openCounter != closeCounter)
		{
			throw logic_error("Exception error: Unequal number of parentheses \"(\" and \")\"");
			return;
		}
		if (squareOpenCounter != squareCloseCounter)
		{
			throw logic_error("Exception error: Unequal number of square brackets");
			return;
		}

	//now format to have ( and ) at the start and end of the equation
	if (equation[0] != '(' || equation[size-1] != ')')
	{
		//reformats, and updates size
		equation = reformatEquation(equation, size);
	}
																			//debugging
																			//cout << "new equation: " << equation.c_str() << endl;

	sherStack<stackItem> equationStack;	//holds the vector and operators

	bool isNegative = false;

	//goes through each char in the equation
	for (int i = 0; i < size; ++i)
	{

		//check for negative sign. determine whether it's a minus operator or a negative sign.
		if (equation[i] == '-')
		{
			//first operator, then it is a negative sign
			if (i == 1)
			{
				isNegative = true;
			}
			//if the character before is + or - or * or (
			else if (isPushOperator(equation[i-1]))
			{
				//a negative sign
				isNegative = true;
			}
		}

		//test if character is valid
		if (isValidChar(equation[i]) == false)
		{
			throw logic_error("Exception error: unexpected character in equation");
			return;
		}

		//test if operator )
		else if (equation[i] == ')')
		{
			//make a temporary stack to work with
			sherStack<stackItem> tempStack;

			//pass the parentheses things into the tempstack;
			char testChar = '\0';		//testChar and testVec are to store the information temporarily to pass into the stack
			mathVector testVec(0);
			bool isVec = false;

			//get the first item
			stackItem messenger = equationStack.top(); equationStack.pop();	//messenger is an item to go into the temp stack from the equation stack
			isVec = storeItemInfo(testChar,testVec,messenger);

			//counts how many items in the parenthesis
			int counter = 0;

			//enter this loop with a new item, storing the item in the tempstack will happen in the loop
			//only end when the ( is met
			while (testChar != '(')
			{
				//If in loop, it means that righ tnow messenger stores something in the parenthesis
				tempStack.push(messenger);
				counter++;
																				/* Debugging
																				if (isVec)
																				{
																					cout << messenger.returnVector().toString() << endl;
																				}
																				else
																				{
																					cout << messenger.returnOperator() << endl;
																				}
																				*/

				//now get the next item
				messenger = equationStack.top(); equationStack.pop();
				isVec = storeItemInfo(testChar,testVec,messenger);

			}

																				//cout << "num o items: " << counter << endl;

			//upon exiting the while loop, testChar now holds the ( operator. Already poppped from the equationStack. So no need to pop again

			//Now calculate the tempstack
			mathVector result(calculateStack(tempStack,counter));

			//now result holds the result of the parenthesis. store it in item and push it onto the stack again
			stackItem newItem(result);
			equationStack.push(newItem);

			//by the end of this function, the (function) will be replaced by a single vector

		}

		//test for vector
		else if (equation[i] == '[')
		{
			//Goal: get the vector, and push it onto the stack
			string newVectorString;		//stores the vector in a string
			int newVectorCounter = 0;	//a counter to construct the vector string

			//construct the vector string until meeting the end of the vector, signaled by ']'
			while (equation[i] != ']')
			{
				newVectorString[newVectorCounter] = equation[i];
				i++;

				//test to see if the next character in the equation is valid
				if (isValidChar(equation[i]) == false)
				{
					throw logic_error("Exception error: unexpected character in equation");
					return;
				}

				newVectorCounter++; 
			}

			//we also want the ]. i and counter already incremented
			newVectorString[newVectorCounter] = equation[i];

			//make a vector with newVector
			mathVector pushVector(newVectorString);						//debugging
																		//string temp = pushVector.toString();
																		//cout << "vector:   " << temp << endl;

			//Create item and push!
			stackItem pushItem(pushVector);

			equationStack.push(pushItem);
		}

		//test for operator
		else if (isPushOperator(equation[i]) == true && isNegative == false)
		{
			//make char into item and push
			stackItem pushItem(equation[i]);
			equationStack.push(pushItem);
		}

		//test for number
		//Goal: get number into string and convert it to a double, then a vector, and push the vector onto the stack
		else if (isNumber(equation[i]) == true)
		{
			//get the number into a string
			string newVectorString;		//stores the number in a string
			int newVectorCounter = 0;	//counter to construct the number

			//may be possible that the number is a negative number
			//so get the first char in before going into loop
			newVectorString[newVectorCounter] = equation[i];
			i++;

			if (isValidChar(equation[i]) == false)
			{
				throw logic_error("Exception error: unexpected character in equation");
				return;
			}

			newVectorCounter++;

			//until it meets a new pushOperator
			while (isOperatorChar(equation[i]) == false)
			{
				newVectorString[newVectorCounter] = equation[i];
				i++;

				//test to see if next char in equation is valid
				if (isValidChar(equation[i]) == false)
				{
					throw logic_error("Exception error: unexpected character in equation");
					return;
				}

				newVectorCounter++;
			}

			//reset the string
			newVectorString[newVectorCounter] = '\0';
																	//debugging
																	//cout << "new: " << newVectorString.c_str() << endl;

			//move back to appropriate place since i right now is pointing at the char after the number
			i--;

			//turn into 1D vector and push
			//first convert into double
			double newNum = atof(newVectorString.c_str());
			mathVector pushVector(newNum);

			stackItem pushItem(pushVector);
			equationStack.push(pushItem);

			//reset everything
			newVectorString[0] = '\0';
			newVectorCounter = 0;

																			//Debugging stuff
																			//stackItem tempI = equationStack.top();
																			//mathVector mVec= tempI.returnVector();
																			//string vec = mVec.toString();

																			//cout << "number:   " << vec << endl;
		}

		//reset boolean
		isNegative = false;

	}


	//at this point, since the last char in the equation is also a ), everythin will have been computed.
	//the stack will only hold one item: the answer vector. top and pop it, and output it onto the terminal

	stackItem finalAnswer = equationStack.top(); equationStack.pop();
	cout << endl << "The answer to the equation is: " << finalAnswer.returnVector().toString() << endl << endl;

	return;

}

int main()
{

	char choice;
	bool menuLoop = true;
	bool choiceLoop = true;

	while (menuLoop == true)
	{
		choiceLoop = true;

		cout<<left;
		cout<<"*---------------------------------------------------------*"<<endl;
		cout<<"|"<<setw(57)<<" "																<<"|"<<endl;
		cout<<"|             Welcome to Vectulator v.1.0!                |"<<endl;
		cout<<"|"<<setw(57)<<" "																<<"|"<<endl;
		cout<<"|"<<setw(57)<<" This is a mathematical vector calculator created by"				<<"|"<<endl;
		cout<<"|"<<setw(57)<<" Stephen Tsung-Han Sher for CS104"								<<"|"<<endl;
		cout<<"|"<<setw(57)<<" "																<<"|"<<endl;
		cout<<"|"<<setw(57)<<" Please select an action to perform:"								<<"|"<<endl;
		cout<<"|"<<setw(57)<<" 1) Instructions"													<<"|"<<endl;
		cout<<"|"<<setw(57)<<" 2) Make a calculation"											<<"|"<<endl;
		cout<<"|"<<setw(57)<<" Enter \"Q\" to Quit"												<<"|"<<endl;
		cout<<"|"<<setw(57)<<" "																<<"|"<<endl;
		cout<<"*---------------------------------------------------------*"						<<endl<<endl;

	 	choiceLoop = true;
	 	while (choiceLoop == true)
	 	{
	 		cout<<"Input: ";cin>>choice;

	 		if (choice == '1')
	 		{
				instructions();
				choiceLoop = false;
	 		}
	 		else if (choice == '2')
	 		{
	 			try
	 			{calculate();}
	 			catch(logic_error const &e)
	 			{cout << e.what() << endl;}

				char dump;
				cin.ignore(256,'\n');
				cout << "Enter any key to return to the main menu"; cin >> dump; cout << endl << endl;
				cin.ignore(256,'\n');

				choiceLoop = false;
	 		}
	 		else if (choice == 'q' || choice == 'Q')
	 		{
	 			choiceLoop = false;
	 			menuLoop = false;
	 		}
	 		else
	 		{
	 			cin.ignore(256,'\n');
	 			cout<<endl<<"Error: Invalid input"<<endl<<endl;
	 		}
	 	}

	}
	
	cout << "---Program End---" << endl;

	return 0;

}