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

		void setID(const int &n);
		int returnID();
		void setUserInfo(string s, int n);		//n is the array position
		void setWall(wall *newWall);
		//void setWall(wall *newWall, const int field, const int direction);
		void setNetwork (doubleSizeArray<user*> *network);
			void addFriend(user * newFriend, bool increment);
			void removeFriendByIndex(int index, bool increment);
			void removeFriendByPtr(user * toRemove, bool increment);

		void setRequests (doubleSizeArray<user*> *requests);
			void addRequest(user * newFriend, bool increment);
			void removeRequest(int index, bool increment);

		void addPost(wallPost* newPost, bool increment);
		void removePostByIndex(int index, bool increment);

		string returnUserInfoInt(int n);		//uses index of the userInformation array to return information
		//string returnUserInfoString(string s);	//Uses string to return the user's information
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
		//void editField(int index, const int direction);
		void setPostNum(int n);
		void setFriendNum(int n);
		void setRequestNum(int n);
		int returnNumOfPosts();
		int returnNumOfFriends();
		int returnNumOfRequests();

		//Comparing functions
		//A public member because the user should change the sorting method
		//however they want
		bool (*sortingMethod)(wallPost*, wallPost*);
		bool isMax;


	private:
		int userID;
		string userInfo[4];						//first name
		wall *userWall;							//last name
		doubleSizeArray<user*> *friendNetwork;	//age
		doubleSizeArray<user*> *friendRequests;	//password
		int numOfPosts;
		int numOfFriends;						
		int numOfRequests;						
};

#endif //user_H_