#ifndef userList_H_
#define userList_H_

class user;

#include "../hash/hashtable.h"
#include "../user/user.h"
#include "../wall/wall.h"
#include "../userKey/userKey.h"

#include <vector>
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

		bool containsUser(string uName);			//returns true if user exists with given name and password

		user* returnUser(string uName);				//returns user by its name and password
		hashTable<userKey*, user*>* returnTable();
		vector<user*>* returnVector();

		void removeUser(user *toDelete);

		user* getUserPtr(string uName);

		void printAllUsers() const;																		//prints all users and their information

	private:
		int maxID;
		hashTable<userKey*, user*>* userTable;
		int totalUsers;
		vector<user*>* IDUserVector;

};

#endif //userList_H_