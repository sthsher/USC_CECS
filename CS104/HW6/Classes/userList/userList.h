#ifndef userList_H_
#define userList_H_

class user;

#include "../listLibrary/linkedList/LListSet.h"
#include "../user/user.h"
#include "../wall/wall.h"

#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

class userList
{
	public:
		userList();
		~userList();

		void addUser(user *newUser);																		//Adds user to the list

		int returnTotalUsers(); 																		//returns the total number of users

		bool containsUser(const string &fName, const string &lName, const string &password);			//returns true if user exists with given name and password

		user* returnUser(const string &fName, const string &lName, const string &password);				//returns user by its name and password
		LListSet<user*>* returnPtr();

		void removeUser(user *toDelete);

		void printAllUsers() const;																		//prints all users and their information

	private:
		LListSet<user*> *userListPtr;
		int totalUsers;

};

#include "userList.hpp"


#endif //userList_H_