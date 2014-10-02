#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

bool checkExisting(int** toAdd, int userNum, int size[], int num)
{
	for (int i = 0; i < size[userNum]; ++i)
	{
		if ((toAdd[userNum])[i] == num)
		{
			return true;
		}
	}

	return false;
}

string constructString(string A, string B, string C, string D, string E)
{
	string post;

	stringstream ss;
	ss.str(A + " " + B + " " + C + " " + D + " " + E);
	post = ss.str();

	return post;
}

int main()
{
	int numOfUsers;
	int numOfPosts;
	int numOfComments;
	int numOfFriends;
	int numOfRequests;
		

	cout << endl << "Please enter : " << endl;
	cout << "             The number of users to generate: "; cin >> numOfUsers;
	cout << "           The number of posts for each user: "; cin >> numOfPosts;
	cout << "        The number of comments for each post: "; cin >> numOfComments;
	cout << "         The number of friends each user has: "; cin >> numOfFriends;
	cout << "The number of pending requests for each user: "; cin >> numOfRequests;

	srand(time(NULL));
	int randNum;

	ifstream ageFile;
	ageFile.open("Data/ageValues.txt");

	ifstream wordsFile;
	wordsFile.open("Data/random_words.txt");

	ifstream timeFile;
	timeFile.open("Data/timestamps.txt");

	ifstream nameFile;
	nameFile.open("Data/names.txt");

	ofstream fout;
	fout.open("user_info_file_generate.txt");

	//make 10000 users first
	//each user has 4 wallposts
	//each post has 3 comments
	//each user has 100 friends
	//each user has 10 pending requests
	for (int i = 1; i <= numOfUsers; ++i)
	{

		string fName;
		string lName;
		int age;
		string password;

		nameFile >> fName;
		nameFile >> lName;
		ageFile >> age;
		wordsFile >> password;

		fout << fName << " ";				//first name
		fout << lName << " ";				//last name
		fout << age << " ";					//age
		fout << password << " ";			//password
		fout << numOfPosts << " ";			//number of posts
		fout << numOfFriends << " ";		//number of friends
		fout << numOfRequests << " ";		//number of pending requests
		fout << i << endl;					//ID

	}

	fout << "<<<END>>>" << endl;



	int **toAdd = new int*[numOfUsers];
	for (int i = 0; i < numOfUsers; ++i)
	{
		(toAdd[i]) = new int[numOfUsers];
	}
	int size[numOfUsers];
	for (int z = 0; z < numOfUsers; ++z)
	{
		size[z] = 0;
	}

	//posts

	for (int i = 0; i < numOfUsers; ++i)
	{

		//make posts
		for (int j = 0; j < numOfPosts; ++j)
		{
			int timeNum;
			randNum = rand()%(numOfUsers-2)+1;

			//author and number of comments
			fout << randNum << " " << numOfComments << " ";

			if (!checkExisting(toAdd, i, size, randNum))
			{
				toAdd[i][(size[i])++] = randNum;
			}

			//number of comments
			timeFile >> timeNum;		//timestamp
			fout << timeNum << endl;

			//get five words
			string A, B, C, D, E;
			wordsFile >> A;
			wordsFile >> B;	wordsFile >> C;	wordsFile >> D;	wordsFile >> E;
			string line = constructString(A, B, C, D, E);

			//content
			fout << line << endl;

			for (int h = 0; h < numOfComments; ++h)
			{

				//now make comments
				randNum = rand()%(numOfUsers-2)+1;
				fout << randNum << " ";

				if (!checkExisting(toAdd, i, size, randNum))
				{
					toAdd[i][(size[i])++] = randNum;
				}

				timeFile >> timeNum;
				fout << timeNum << endl;

				wordsFile >> A;
				wordsFile >> B;	wordsFile >> C;	wordsFile >> D;	wordsFile >> E;		
				line = constructString(A, B, C, D, E);

				fout << line << endl;
			}
		}

		//fout << endl;

	}

	//now do friends
	if (numOfFriends == 0)
	{
		for (int i = 0; i < numOfUsers; ++i)
		{
			fout << "NONE" << endl;
		}
	}
	else
	{
		for (int i = 0; i < numOfUsers; ++i)
		{
			//get the remaining number of friends to add to the target
			int remaining = numOfFriends-size[i];

			//print out the current friends
			for (int j = 0; j < size[i]; ++j)
			{
				fout << (toAdd[i])[j] << " ";
			}

			for (int j = 0; j < remaining; ++j)
			{
				randNum = rand()%(numOfUsers-2)+1;
				//check to see if the id already exists

				if (!checkExisting(toAdd, i, size, randNum))
				{
					//output it;
					toAdd[i][(size[i])++] = randNum;
					fout << randNum << " ";
				}
				else
				{
					//already exists, repeat again
					--j;
				}

			}
			fout << endl;

			//cout << "User " << i << " has " << size[i] << "friend" << endl;
		}
	}

	//now for requests

	if (numOfRequests == 0)
	{
		for (int i = 0; i < numOfUsers; ++i)
		{
			fout << "NONE" << endl;
		}
	}
	else
	{
		for (int i = 0; i < numOfUsers; ++i)
		{

			
			for (int j = 0; j < numOfRequests; ++j)
			{
				
				randNum = rand()%(numOfUsers-2)+1;
				//check to see if the id already exists

				if (!checkExisting(toAdd, i, size, randNum))
				{
					//output it;
					fout << randNum << " ";
				}
				else
				{
					//already exists, repeat again
					--j;
				}

			}
			fout << endl;
		
		}
	}

/*
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < size[i]; ++j)
		{
			cout << (toAdd[i])[j] << "  ";
		}
		
		cout << endl;
	}

*/
	ageFile.close();

	wordsFile.close();

	timeFile.close();

	nameFile.close();

	fout.close();
		



	for (int i = 0; i < numOfUsers; ++i)
	{
		delete toAdd[i];
	}
	delete [] toAdd;

	

	return 0;

}

