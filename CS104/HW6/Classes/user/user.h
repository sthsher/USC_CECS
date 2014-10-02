#ifndef user_H_
#define user_H_

class userList;


#include "../wall/wall.h"
#include "../userList/userList.h"

using namespace std;

class user
{
	public:
		user();
		user(string info[]);					//initializes with user's information
		~user();

		void setUserInfo(string s, int n);		//n is the array position
		void setWall(wall *newWall);
		void setWall(wall *newWall, const int field, const int direction);
		void setNetwork (doubleSizeArray<user*> *network);
			void addFriend(user * newFriend);
			void removeFriend(int index);

		void setRequests (doubleSizeArray<user*> *requests);
			void addRequest(user * newFriend);
			void removeRequest(int index);

		string returnUserInfoInt(int n);		//uses index of the userInformation array to return information
		string returnUserInfoString(string s);	//Uses string to return the user's information
												//eg "firstname" or "fname" will return the firstname field
		string returnFullName();
		doubleSizeArray<user*>* network ();
		doubleSizeArray<user*>* requests ();

		wall *returnWall();
		user* returnThis();

		void printUserInfo();
		//void printWall();

		//allows comparison between users
		bool operator==(const user &other);
		bool operator!=(const user &other);
		bool testLogIn(const user &other);

		//Utilities
		void editField(int index, const int direction);



	private:
		string userInfo[6];						//first name
		wall *userWall;							//last name
		doubleSizeArray<user*> *friendNetwork;	//age
		doubleSizeArray<user*> *friendRequests;	//password
		int numOfFriends;						//number of posts
		int numOfRequests;						//number of friends

};

#include "user.hpp"

#endif //user_H_