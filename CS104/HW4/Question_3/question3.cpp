#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "classes/LList/Set/LListSet.h"


using namespace std;

//Reads text file and inputs:
//number of friends
//number of conflicts
//weight of each friend
//a 2D array containing the conflicts
void initializeData(int &numOfFriends, int &numOfConflicts, double **weightPtr, int ***conflictArrayPtr)
{
	ifstream fin;

	fin.open("Question_3/input.txt");

	if (fin == NULL)
	{
		cout<<"Error: cannot find file"<<endl;
		exit(1);
	}
	while(!fin.eof())
	{
		//get first line's information
		fin>>numOfFriends;
		fin>>numOfConflicts;

		//Dynamically create size of number of friedns to store their weight
		*weightPtr = new double[numOfFriends];

		//Store their weight
		for (int i = 0; i < numOfFriends; i++)
		{
			fin>>(*weightPtr)[i];
		}

		//Dynamically create array size numOfConflicts
		(*conflictArrayPtr) = new int*[numOfConflicts];

		for (int i = 0; i < numOfConflicts; i++)
		{
			//Create two slots
			(*conflictArrayPtr)[i] = new int[2];
			fin>>(*conflictArrayPtr)[i][0];
			fin>>(*conflictArrayPtr)[i][1];
		}

	}

}

//makes unavailable at pos in array (meaning Friend n's array position is n-1)
void makeUnavailable(int pos, bool* canInvite)
{
	canInvite[pos] = false;
}

//makes available at pos in array (meaning Friend n's array position is n-1)
void makeAvailable(int pos, bool* canInvite)
{
	canInvite[pos] = true;
}

//makes entire bool array as true
void resetAvailability(int numOfFriends, bool* canInvite)
{
	for (int i = 0; i < numOfFriends; i++)
	{
		canInvite[i] = true;
	}
}

//prints entire bool array for debugging purposes
void printAvailability(int numOfFriends, bool* canInvite)
{
	cout << "Printing bool array: " << endl;

	for (int i = 0; i < numOfFriends; i++)
	{
		cout << canInvite[i] << "  ";
	}
	cout << endl;
}

//returns true if enture bool array is false
bool isEnd(bool* canInvite, int numOfFriends)
{
	for (int i = 0; i < numOfFriends; i++)
	{
		if (canInvite[i]) return false;
	}

	return true;
}

//intakes friend number, and checks and marks "false" in bool array whereever there is a conflict
void markConflicts (int person, bool* canInvite, int numOfConflicts, int **conflictArray)
{
	for (int i = 0; i < numOfConflicts; i++)
	{
		if(conflictArray[i][0] == person) makeUnavailable(conflictArray[i][1]-1, canInvite);
		if(conflictArray[i][1] == person) makeUnavailable(conflictArray[i][0]-1, canInvite);
	}
}

//undos the function "markConflicts"
void undoConflicts (int person, bool* canInvite, int numOfConflicts, int **conflictArray)
{
	for (int i = 0; i < numOfConflicts; i++)
	{
		if(conflictArray[i][0] == person) makeAvailable(conflictArray[i][1]-1, canInvite);
		if(conflictArray[i][1] == person) makeAvailable(conflictArray[i][0]-1, canInvite);
	}
}

//Check if friend number is available to invite
bool checkFriend(int testFriend, bool* canInvite)
{
	return canInvite[testFriend-1];
}

//returns number of next avaiable friend
int availableFriend(int numOfFriends, bool* canInvite)
{
	for (int i = 0; i < numOfFriends; i++)
	{
		if(canInvite[i]) return (i+1);
	}
	return 0;
}

void invite(int currentFriend, int numOfFriends, int numOfConflicts, double *weightArray, int **conflictArray, bool *canInvite, double &currentFun, double &maxFun, LListSet<int>* inviteList, int** finalListPtr, int &finalSize)
{
	//Update current fun, make current friend unavailable, mark their conflicts, and add them to the list
	currentFun += weightArray[currentFriend-1];
	makeUnavailable(currentFriend-1, canInvite);
	markConflicts(currentFriend, canInvite, numOfConflicts, conflictArray);
	inviteList->add(currentFriend);


	//Test for base case
	if (isEnd(canInvite, numOfFriends))
	{

		//If first solution or an even better solution
		if (maxFun == 0 || currentFun > maxFun)
		{
			//overwrite maxFun, update final invite size, and update the final invite list
			maxFun = currentFun;
			finalSize = inviteList->returnSize();
			(*finalListPtr) = inviteList->convertToArray();

		}
		
		//backtrack: undo the adding of the fun, make available, undo the conflicts, and remove the personf rom the list, and backtrack
		currentFun -= weightArray[currentFriend-1];
		makeAvailable(currentFriend-1, canInvite);
		undoConflicts(currentFun, canInvite, numOfConflicts, conflictArray);
		inviteList->remove(currentFriend);
		return;
	}

	//Backtracking: goes through iterations with the next friend, then continue down the list until all possible secondary / tertiaray / etc cases are tried

	for (int nextFriend = currentFriend+1; nextFriend <= numOfFriends; nextFriend++)
	{
		//if the friend is available, then invite them to the list by running the backtracking function again
		if(checkFriend(nextFriend, canInvite))
		{
			invite(nextFriend, numOfFriends, numOfConflicts, weightArray, conflictArray, canInvite, currentFun, maxFun, inviteList, finalListPtr, finalSize);
		}
	}

	//end of this iteration, return, and start with the next initial friend

}

int main()
{

	//********************************************************************************************************
	//				Declarations

	//stores the weight of each friend in an array. ** is to pass by pointer in the initialization function
	double *weightArray;
	double **weightPtr = &weightArray;

	//stores the conflicts in a 2D array. *** is to pass by pointer in initialization function
	int **conflictArray;
	int ***conflictArrayPtr = &conflictArray;

	//keep track of friends and conflicts
	int numOfFriends = 0;
	int numOfConflicts = 0;

	//read file and store appropriate data
	initializeData(numOfFriends, numOfConflicts, weightPtr, conflictArrayPtr);

	//bool array to keep track of which friends are available and which are not
	bool *canInvite = new bool[numOfFriends];
		for (int i = 0; i < numOfFriends; i++)
		{
			canInvite[i] = true;
		}

	//Keeps track of the fun-factor of the growing party
	double currentFun = 0;
	//stores the most possible fun found thus far
	double maxFun = 0;

	//Stores the list of people to invite with the most possible fun
	int *finalList;
	int **finalListPtr = &finalList;
	int finalSize = 0;

	//stores the growing list of people to invite
	LListSet<int> *inviteList = new LListSet<int>;
	//stores an empty linked list for restarting purposes
	LListSet<int> *emptyList = new LListSet<int>;

	//********************************************************************************************************
	//				Recursion

	//A for loop to go through the recursion with every single friend.
	//Once you test all the combinations with friend 1, there is no need to try the possibility of
	//inviting friend 1 again when you are starting with friend 2 or 3 etc since you already tried the combination
	for (int i = 1; i < numOfFriends; i++)
	{
		//make every person before the starting person as unavailable to invite
		//testing all possible combinations, therefore no need to test combinations already tested
		for (int j = i; j != 0; j--)
		{
			makeUnavailable(j-1, canInvite);
		}

		//add fun factor of initial friend
		currentFun += weightArray[i-1];

		//mark all the conflicts for the initial friend
		markConflicts(i, canInvite, numOfConflicts, conflictArray);
		
		//Add initial friend to current list
		inviteList->add(i);

		//find the next available friend
		int next = availableFriend(numOfFriends,canInvite);

		//If there exists an available friend, invite the next friend and enter recursion
		if (next != 0)
		{
			invite(next, numOfFriends, numOfConflicts, weightArray, conflictArray, canInvite, currentFun, maxFun, inviteList, finalListPtr, finalSize);
		}
		else //meaning there are no more available friends, or the base case. Test to see if this is even better
		{
			if (maxFun == 0 || currentFun > maxFun)
			{
				maxFun = currentFun;
				finalSize = inviteList->returnSize();
				(*finalListPtr) = inviteList->convertToArray();
			}

		}

		//reset everything to start with the next friend
		currentFun = 0;
		inviteList = emptyList;
		resetAvailability(numOfFriends, canInvite);
	}

	//********************************************************************************************************
	//				Results

	cout<<endl<<"The people to invite to maximize fun and avoid conflicts are: "<<endl;
	for (int i = 0; i < finalSize; i++)
	{
		cout<<"Person: " << finalList[i]<<endl;
	}
	cout<<endl<<"The value of fun for this combination is: "<<maxFun<<endl;




	cout<<endl<<"---Program End---"<<endl<<endl;
	return 0;
}