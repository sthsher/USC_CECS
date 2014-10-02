#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>	//atoi

#include "user.h"

using namespace std;

class userList;

//convert integer to string
string intToString(int n)
{
		string foo;

		stringstream ss;
		ss << n;
		foo = ss.str();

		return foo;
}

/*
//increment or decrement number fields
//index is the field to edit (4 being number of posts and 5 being the number of friends)
//direction 1 is to decrement, direction 2 is to increment
void user::editField(int index, const int direction)
{
	int num;

	if (direction == 2)
	{
		num = atoi((userInfo[index]).c_str());
		++num;
	}
	else if (direction == 1)
	{
		num = atoi((userInfo[index]).c_str());
		--num;
	}

	userInfo[index] = intToString(num);
}
*/

int user::returnNumOfPosts()
{
	return numOfPosts;
}
int user::returnNumOfFriends()
{
	return numOfFriends;
}
int user::returnNumOfRequests()
{
	return numOfRequests;
}
void user::setPostNum(int n)
{
	numOfPosts = n;
}
void user::setFriendNum(int n)
{
	numOfFriends = n;
}
void user::setRequestNum(int n)
{
	numOfRequests = n;
}

//return the full name in one string
string user::returnFullName()
{
	stringstream ss;
	ss.str(userInfo[0] + " " + userInfo[1]);

	return ss.str();
}

user::user()
{

	//set everything as empty string
	for (int i = 0; i < 4; ++i)
	{
		userInfo[i] = "";
	}

	userID = 0;

	userWall = NULL;

	friendNetwork = NULL;
	friendRequests = NULL;
	numOfPosts = 0;
	numOfFriends = 0;
	numOfRequests = 0;

	sortingMethod = NULL;

}

user::user(string info[])
{
	//goes through array and set the corresponding information as the userInfo's information
	for (int i = 0; i < 4; i++)
	{
		userInfo[i] = info[i];
	}

	userWall = NULL;
	friendNetwork = NULL;
	friendRequests = NULL;
	numOfFriends = 0;
	numOfRequests = 0;
}

user::~user()
{ 
	if (friendNetwork != NULL)
	{
		delete friendNetwork;
		friendNetwork = NULL;
	}
	
	if (friendRequests != NULL)
	{
		delete friendRequests;
		friendRequests = NULL;
	}
	
	//deleting wall will write the wall
	//this descturctor is only called in the end of the userLIst destructor
	//at that point the wall will have already been deleted


}

void user::setID(const int &n)
{
	userID = n;
}

int user::returnID()
{
	return userID;
}

void user::setUserInfo(string s, int n)
{
	userInfo[n] = s;
}

void user::setWall(wall *newWall)
{
	userWall = newWall;
}

/*
void user::setWall(wall *newWall, const int field, const int direction)
{
	//editField(field, direction);

	setWall(newWall);
}
*/
void user::setNetwork(doubleSizeArray<user*> *network)
{
	friendNetwork = network;
}

void user::addFriend(user * newFriend, bool increment)
{
	//if there is no network, make one
	if (friendNetwork == NULL)
	{
		friendNetwork = new doubleSizeArray<user*>;
	}

	//check if network already has the friend. If so, don't add the friend
	doubleIterator<user*> beginIt = friendNetwork->begin();
	doubleIterator<user*> endIt = friendNetwork->end();
	for (doubleIterator<user*> it = beginIt; it != endIt; ++it)
	{
		if ((*(*it)) == newFriend)
		{
			//found a repeat, return
			return;
		}
	}

	//increment number of friends
	//editField(5,2);
	friendNetwork->insert(numOfFriends, newFriend);


	if (increment)
		numOfFriends++;


	//cout << "end of addfriend: network: " << friendNetwork << endl;


}

void user::removeFriendByIndex(int index, bool increment)
{
	//decrement number of friends
	//editField(5,1);
	if (increment)
		numOfFriends--;
	friendNetwork->remove(index);

	//if no more friends, delete and make the network NULL
	if (numOfFriends == 0)
	{
		delete friendNetwork;
		friendNetwork = NULL;
	}
}

void user::removeFriendByPtr(user * toRemove, bool increment)
{
	int counter = 0;

	//go through the friendNetwork array and find the same pointer
	doubleIterator<user*> beginIt = friendNetwork->begin();
	doubleIterator<user*> endIt = friendNetwork->end();
	for (doubleIterator<user*> it = beginIt; it != endIt; ++it, ++counter)
	{
		if ((*(*it)) == toRemove)
		{
			//found the user to delete, counter holds the position
			cout << "removing: " << toRemove->returnFullName() << "from " << this->returnFullName() << endl;
			this->removeFriendByIndex(counter, increment);
			return;
		}
	}
}

void user::addPost(wallPost* newPost, bool increment)
{
	userWall->addPost(newPost);
	if (increment)
		numOfPosts++;
}

void user::removePostByIndex(int index, bool increment)
{
	userWall->removePostByIndex(index);
	if (increment)
		numOfPosts--;
}



void user::setRequests(doubleSizeArray<user*> *requests)
{
	friendRequests = requests;
}

void user::addRequest(user * newFriend, bool increment)
{
	//if there is no request network, make one
	if (friendRequests == NULL)
	{
		friendRequests = new doubleSizeArray<user*>;
	}

	//check if network already has the friend. If so, don't add the friend
	doubleIterator<user*> beginIt = friendRequests->begin();
	doubleIterator<user*> endIt = friendRequests->end();
	for (doubleIterator<user*> it = beginIt; it != endIt; ++it)
	{
		if ((*(*it)) == newFriend)
		{
			//found a repeat, return
			return;
		}
	}

	friendRequests->insert(numOfRequests, newFriend);


	if (increment)
		numOfRequests++;


}

void user::removeRequest(int index, bool increment)
{
	friendRequests->remove(index);
	if (increment)
		numOfRequests--;

	if (numOfRequests == 0)
	{
		delete friendRequests;
		friendRequests = NULL;
	}
}

string user::returnUserInfoInt(int n)
{
	return userInfo[n];
}

doubleSizeArray<user*>* user::network ()
{
	return friendNetwork;
}

doubleSizeArray<user*>* user::requests ()
{
	return friendRequests;
}
/*
//Checks for requested field by string input and returns that information
string user::returnUserInfoString(string s)
{
	if(s == "fName" || s == "firstName" || s == "firstname" || s == "FirstName" || s == "Firstname")
	{
		return userInfo[0];
	}
	if(s == "lName" || s == "lastName" || s == "lastname" || s == "LastName" || s == "Lastname")
	{
		return userInfo[1];
	}
	if(s == "Age" || s == "age")
	{
		return userInfo[2];
	}
	if(s == "Password" || s == "password" || s == "pwd" || s == "PWD")
	{
		return userInfo[3];
	}
	if(s == "numOfPosts" || s == "numberOfPosts")
	{
		return userInfo[4];
	}	
	if(s == "fullName" || s == "fullname" || s == "FullName" || s == "Fullname")
	{
		return userInfo[5];
	}
	if(s == "friends" || s == "Friends" || s == "FRIENDS")
	{
		return userInfo[6];
	}

	//None of the keywords recognized, return empty string
	//cout debugging statement
	cout<<"ERROR: NO VALID KEYWORD FOR FUNCTION"<<endl;
	cout<<"returnUserInfoString in class user"<<endl;
	return "";
}
*/
wall* user::returnWall()
{
	return userWall;
}

user* user::returnThis()
{
	return this;
}

void user::printUserInfo()
{
	cout << "--------------------------------------------------" << endl;
	cout << "Name:              " << userInfo[0] << " " << userInfo[1] << endl;
	cout << "Age:               " << userInfo[2] << endl;
	cout << "Password:          " << userInfo[3] << endl;
	cout << "Number of Posts:   " << numOfPosts << endl;
	cout << "Number of Friends: " << numOfFriends << endl;
	cout << "--------------------------------------------------" << endl;

	return;
}

bool user::operator==(const user &other)
{
	//only compare first name and last name
	if (this->userInfo[0] == other.userInfo[0] &&
		this->userInfo[1] == other.userInfo[1])
		return true;
	else
	{
		return false;
	}
}	

bool user::operator!=(const user &other)
{
	//only compare first name and last name
	//if any of them is not equal, then true
	if (this->userInfo[0] != other.userInfo[0] ||
		this->userInfo[1] != other.userInfo[1])
		return true;
	else
	{
		return false;
	}
}	

//tests for username and password
bool user::testLogIn(const user &other)
{
	//only compare first name and last name
	if (this->userInfo[0] == other.userInfo[0] &&
		this->userInfo[1] == other.userInfo[1] &&
		this->userInfo[3] == other.userInfo[3])
		return true;
	else
	{
		return false;
	}
}
