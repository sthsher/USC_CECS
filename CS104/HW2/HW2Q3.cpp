#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace std;

//************************************************************************
//					Global Variables for Debugging
//					Feel free to ignore these

//int *path;
//int blah[20];
int counter = 0; 		//This keeps track of how many solutions found

//************************************************************************

//This function returns the absolute difference between two numbers
int calculateEnergyLost(int a, int b)
{
	return abs(a-b);
}

//This function gets the filename from the user through cin
string getFileName()
{

	string fileName;

	cout<<endl;
	cout<<"Please enter the name of the file containing the array"<<endl;
	cout<<"Be sure to include \".txt\" in the file name"<<endl<<endl;
	cout<<"File Name: "; cin>>fileName;cout<<endl<<endl;

				//fileName = "dieInfo.txt";	//For convinience only. Ignore

	cout<<"The file name you have inputted is: "<<fileName<<endl;

	return fileName;

}

//This function makes a virtual die in the code based on the text file
void makeDie(int **tsd, string fileName)
{
	ifstream fin;

	fin.open(fileName.c_str());

	if(fin == NULL)
	{
		cout<<"Error: File not found, please check the file or the spelling"<<endl;
		cout<<"---Exiting Program---"<<endl;
		exit(1);
	}

	while (true)
	{
		if(fin.eof())
		{
			fin.close();
			return;
		}
		//loop thrice to fill in the three adjacent sides. Loop until done with file
		for (int i = 0; i < 3; i++)
		{
			fin>>(*tsd)[i];
		}
		tsd++;
	}

}

//Inputs number n, and makes that number unavailable in the bool array
void makeUnavailable(int n, bool availableNums[])
{
	//num n is the number to make unavailable
	//meaning the number is located at n-1

	availableNums[n-1] = false;

	return;
}

//Makes number n available in the bool array
void makeAvailable(int n, bool availableNums[])
{
	availableNums[n-1] = true;
	return;
}

//if available, return true. if not, return false
bool checkAvailability(int n, bool availableNums[])
{
	//check number n, meaning at location n-1

	if (availableNums[n-1] == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//checks if all numbers have been used. If so, returns true
bool checkFinished(bool availableNums[])
{
	for (int i = 1; i < 21; i++)
	{
		if (checkAvailability(i, availableNums) == true)
		{
			return false;
		}
	}
	return true;
}

//This is the recursion
int calculateTotalE(int totalE, int currentPos, int **tsd, bool availableNums[], bool &isEnd, int &best)
{
	//First thing: make the current position unavailable in the bool array.
	makeUnavailable(currentPos, availableNums);

	//Now check if at base case: if all the numbers are unavailable.
	//If so, it means the code has arrived at one of the possible solutions
	isEnd = checkFinished(availableNums);

	if (isEnd == true)
	{
		if (best == 0) //best is zero if this is the first solution. Then just put the solution in best
		{
			best = totalE;
		}
		else if(totalE < best) //overwrite best if the current solution is better
		{
			best = totalE;
		}
											//**************************************
											//Debugging stuff. Don't worry about it
											
											///cout<<"TotalE: "<<totalE<<endl;
											counter++;	//Adds to the total number of solutions found.
											/*
											for (int i = 0; i < 20; i++)
											{
												cout<<blah[i]<<" ";
											}
											cout<<endl<<endl;
											*/
											//**************************************

		//Since this is one of the solutions, now need to backtrack and find other solutions
		//Make this current number available for future solutions, and return to backtrack
		makeAvailable(currentPos, availableNums);
		return totalE;
	}
											//More debugging stuff
											//cout<<"Current Position is: "<<currentPos<<endl;

	//At this point, this is not a solution, so first thing:
	//Check if the current position is at a dead end (all three adjacent sides are unavailable)
	if(	   checkAvailability(tsd[currentPos-1][0], availableNums) == false 
		&& checkAvailability(tsd[currentPos-1][1], availableNums) == false
		&& checkAvailability(tsd[currentPos-1][2], availableNums) == false)
	{
		//If it is at a dead end, make the number available for future use, and backtrack by returning
		makeAvailable(currentPos, availableNums);
		return totalE;
	}

	//Main part of recursion:
	//Goes to all the possible numbers.
	//For loop thrice to go through all three adjacent sides
	for (int i = 0; i < 3; i++)
	{	
		//If the adjacent side is not available, then skip and go to the next adjacent number
		//Only do the if statement if the number is available
		if(checkAvailability(tsd[currentPos-1][i],availableNums) == true)
		{
			//Confirmed that this number is the number will be travelling to, so add the difference to the sum
			totalE += calculateEnergyLost(tsd[currentPos-1][i], currentPos);
											
											//Debugging stuff, ignore it please
											//*path = tsd[currentPos-1][i];
											//path ++;

			//Now travel to the next number through recursion.
			totalE = calculateTotalE(totalE, tsd[currentPos-1][i], tsd, availableNums, isEnd, best);

			//At this point, the recursion has returned, meaning it is backtracking
			//To backtrack, make the number available (done already before returning)
			//and subtract the energy difference from the total, which is this line here
			totalE -= calculateEnergyLost(tsd[currentPos-1][i], currentPos);
											
											//You guessed it. More debugging stuff.
											//path --;
		}
	}

	//If gone through the whole for loop thrice, it means that it has visited all three numbers.
	//Meaning, more backtracking, so make the current number available, and return to backtrack
	makeAvailable(currentPos,availableNums);
	return totalE;

}






int main()
{


//******************************************************************************************************
//												Declarations
//												------------
	int best = 0;		//Best solution
	int totalE = 0;		//Total Energy so far. Keeps track of the current sum of energy lost
	int currentPos = 1;	//Curren position the ant is on. Starts on 1
	bool isEnd = false;	//Is at a solution (end). False if not at a solution. True if it is
	int **tsd;			//Twenty Sided Die (thus tsd). A 2D array of 20 elements (one for each number) and within each element are three more elements, holding the three adjacent numbers for that side
		tsd = new int*[20];

		//Simply makes the 2D array
		for (int i = 0; i < 20; i++)
		{
			tsd[i] = new int[3];
		}

	bool availableNums[20];	//Keep track of which numbers are still available to go to.
		for (int i = 1; i < 20; i++)
		{
			availableNums[i] = true;	//To begin, every number is available
		}		
		availableNums[0]=false;			//Except number 1. We start here
	
										//Debugging stuff, no need to pay attentio here
										//path = blah;
										//*path = 1;
										//path ++;

	string fileName;		//Holds the filename of the text file containing the information of the die

//******************************************************************************************************
//												Make the die
//	
	//Get the filename
	fileName = getFileName();

	cout<<"Making die with: "<<fileName<<endl<<endl;

	//Make the die with the text file
	makeDie(tsd, fileName);

//******************************************************************************************************
//												Recursion: Find solutions
//	
	//Start recursion
	cout<<"Now finding solutions..."<<endl;
	totalE = calculateTotalE(totalE, currentPos, tsd, availableNums, isEnd, best);


//******************************************************************************************************
//												Results
//	

	char dump; //not important what this holds
	cout<<endl<<"Finished finding solutions"<<endl;
	cout<<"Enter any key to view solutions: ";
	cin>>dump;
	cin.ignore(256,'\n');

	cout<<endl<<endl<<"The least possible amount of energy lost is: "<<best<<endl;
	cout<<"The total number of solutions found is: "<<counter<<endl;

	cout<<"---Program End---"<<endl;
	return 0;


}