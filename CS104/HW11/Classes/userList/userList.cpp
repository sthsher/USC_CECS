#include <iostream>
#include "userList.h"

using namespace std;

//Constructor: reads the file and initializes all data
userList::userList()
{

	string tempA, tempB;
	int tempInt;
	maxID = 0;

	userTable = new hashTable<userKey*, user*>;
	IDUserVector = new vector<user*>;
	IDUserVector->resize(10);
	for (int i = 0; i < 10; ++i)
		IDUserVector->at(i) = NULL;

	totalUsers = 0;

	ifstream fin;


	fin.open("user_info_file.txt");

	if(fin == NULL)
	{
		cout<<"Error: File not found, please check directory for info file"<<endl<<endl;
		cout<<"---Program End---"<<endl;
		exit(1);
	}

	if(fin.eof())
	{
		fin.close();
		return;
	}
	else
	{
		while (true)
		{
			//test to see if end of user section
			fin >> tempA;
			if (tempA == "<<<END>>>")
			{
				break;
			}

			//username is stored in tempA;
			string username = tempA;

			//now have tempA hold the first field of userInfo
			fin >> tempA;


			string userInfo[4];
			userInfo[0] = tempA;
			for (int i = 1; i < 4; ++i)
			{
				fin >> tempA;
				userInfo[i] = tempA;
			}
			user* newUser = new user(userInfo);

			newUser->setUsername(username);

			fin >> tempInt;
			newUser->setPostNum(tempInt);
			fin >> tempInt;
			newUser->setFriendNum(tempInt);

			fin >> tempInt;
			newUser->setRequestNum(tempInt);

			newUser->setID(totalUsers);
			if (tempInt > maxID)
				maxID = tempInt;

			//now for security questions
			string question, answer;
			getline(fin, question);	//getline bugs, get rid of first line
			getline(fin, question);
			getline(fin, answer);

			newUser->setSecurityQ(question);
			newUser->setSecurityA(answer);

			userKey* newKey = new userKey(username);

			userTable->add(newKey, newUser);

			if (newUser->returnID() >= IDUserVector->size())
			{
				int oldSize = IDUserVector->size();
				int newSize = ((IDUserVector->size())*2);
				IDUserVector->resize(newSize);

				for (int i = oldSize; i < newSize; ++i)
					IDUserVector->at(i) = NULL;
			}

			IDUserVector->at(newUser->returnID()) = newUser;


			totalUsers++;

		}

		for (int t = 0; t < totalUsers; ++t)
		{
			//first string will be the owner's username
			string userN;
			fin >> userN;

			user* wallOwner;

			userKey* tempKey = new userKey(userN);

			wallOwner = userTable->get(tempKey);

			delete tempKey;

			int authorID;
			int commentNum;
			int creationTime;
			wall *newWall = new wall;

			//loop though the number of posts the person has
			int postNum = wallOwner->returnNumOfPosts();
			for (int i = 0; i < postNum; ++i)
			{
				fin >> authorID;
				fin >> commentNum;
				fin >> creationTime;
				getline(fin, tempA);		//getline bugs: getline twice to get the move to the actual line to get
				getline(fin, tempA);

				wallPost* newPost = new wallPost;
				newPost->setAuthorID(authorID);
				newPost->setCreationTime(creationTime);

				newPost->setAuthor((IDUserVector->at(authorID))->returnUsername());


				//Now set comments
				newPost->setNumOfComments(0);
				for (int j = 0; j < commentNum; ++j)
				{
					int commentAuthorID;
					string commentContent;
					fin >> commentAuthorID;
					fin >> creationTime;
					//cout << "Comment Author ID: " << commentAuthorID << endl;
					getline(fin, commentContent);
					getline(fin, commentContent);
					//cout << "Content: " << commentContent << endl;

					//make a new comment
					postComment* newComment = new postComment;
					newComment->setAuthorID(commentAuthorID);
					newComment->setCreationTime(creationTime);

					newComment->setAuthor((IDUserVector->at(commentAuthorID))->returnUsername());

					newComment->setComment(commentContent);

					newPost->addComment(newComment, true);

				}

			

				newPost->setPost(tempA);

				newWall->addPost(newPost);

			}
			//wall is made, set it
			wallOwner->setWall(newWall);

		}

		//set friends for user
		for (int t = 0; t < totalUsers; ++t)
		// for (LLIterator<user*> it = beginIt; it != endIt; ++it)
		{
			//first string is owner of the friend list
			string ownerName;
			fin >> ownerName;

			user* owner;

			userKey* tempKey = new userKey(ownerName);


			owner = userTable->get(tempKey);


			delete tempKey;

			int friendNum = owner->returnNumOfFriends();
			if (friendNum == 0)
			{
				string dump;
				fin >> dump;
			}
			else
			{
				owner->setFriendNum(0);
				int friendID;
				for (int i = 0; i < friendNum; ++i)
				{
					fin >> friendID;

					//have the ID, find the friend's username
					user* friendUser = IDUserVector->at(friendID);

					owner->addFriend(friendUser, true);


				}
			}


		}


		//set pending requests
		for (int t = 0; t < totalUsers; ++t)
		// for (LLIterator<user*> it = beginIt; it != endIt; ++it)
		{
			//first string is username
			string ownerName;
			fin >> ownerName;

			user* owner;

			userKey* tempKey = new userKey(ownerName);

			owner = userTable->get(tempKey);


			int requestNum = owner->returnNumOfRequests();
			if (requestNum == 0)
			{
				string dump;
				fin >> dump;
			}
			else
			{
				owner->setRequestNum(0);
				int requestID;
				for(int i = 0; i < requestNum; ++i)
				{
					fin >> requestID;

					user* friendUser = IDUserVector->at(requestID);
					owner->addRequest(friendUser, true);

				}
			}
		}


	}
	

}

//destructor, file output
userList::~userList()
{

	ofstream fout;

	//make a new file
	remove("user_info_file.txt");
	fout.open("user_info_file.txt");

	bool isLast = false;

	int tempCounter = 0; //keeps track of how many users have been written

	for (int i = 0; i < IDUserVector->size(); ++i)
	{
		if (IDUserVector->at(i) == NULL)
		{	}	//do nothing
		
		else	
		{
			//test if this is last user
			if ((i) == totalUsers-1)
			{	
				isLast = true;
			}

			//write user information first
			//get the current user the iterator is on
			user *outUser = IDUserVector->at(i);

			//print username
			fout << outUser->returnUsername() << " ";

			for (int i = 0; i < 4; i++)
			{
				fout<<outUser->returnUserInfoInt(i)<<" ";
			}

			fout << outUser->returnNumOfPosts() << " ";
			fout << outUser->returnNumOfFriends() << " ";
			fout << outUser->returnNumOfRequests() << " ";
			fout << endl;
			fout << outUser->getSecurityQ() << endl;
			fout << outUser->getSecurityA() << endl;

			if(isLast)
			{
				fout<<"<<<END>>>";
				fout << endl;
				//fout.close();
				break;
			}
			
		}
	}

	fout.close();

	for (int j = 0; j < IDUserVector->size(); ++j)
	{
		if (IDUserVector->at(j) != NULL)
		{
			fout.open("user_info_file.txt", ios::app);
			
			wall* outWall = IDUserVector->at(j)->returnWall();
			//print the wall's owner:
			fout << IDUserVector->at(j)->returnUsername() << endl;
			fout.close();
			delete outWall;
		}
	}

	fout.open("user_info_file.txt", ios::app);

	//write friends
	for (int j = 0; j < IDUserVector->size(); ++j)
	{
		if (IDUserVector->at(j) != NULL)
		{
			int friendNum = IDUserVector->at(j)->returnNumOfFriends();
			if (friendNum == 0)
			{
				fout << IDUserVector->at(j)->returnUsername() << " ";
				fout << "NONE" << endl;
			}
			else
			{
				fout << IDUserVector->at(j)->returnUsername() << " ";

				for (int i = 0; i < friendNum; ++i)
				{
					fout << IDUserVector->at(j)->network()->get(i)->returnID() << " ";
				}
				fout << endl;
			}
		}
	}

	//write requests
	for (int j = 0; j < IDUserVector->size(); ++j)
	{
		if (IDUserVector->at(j) != NULL)
		{
			int requestNum = IDUserVector->at(j)->returnNumOfRequests();
			if (requestNum == 0)
			{
				fout << IDUserVector->at(j)->returnUsername() << " ";
				fout << "NONE" << endl;
			}
			else
			{

				fout << IDUserVector->at(j)->returnUsername() << " ";

				for (int i = 0; i < requestNum; ++i)
				{
					fout << IDUserVector->at(j)->requests()->get(i)->returnID() << " ";
				}
				fout << endl;
			}
		}
	}	


}

void userList::addUser(user *newUser)
{
	//giver user its ID
	newUser->setID(++maxID);

	userKey* newKey = new userKey(newUser->returnUsername());

	IDUserVector->push_back(newUser);

	userTable->add(newKey, newUser);
	totalUsers++;
}

hashTable<userKey*, user*>* userList::returnTable()
{
	return userTable;
}

vector<user*>* userList::returnVector()
{
	return IDUserVector;
}


user* userList::returnUser(string uName)
{
	//creates a checkUser based on the given information
	user* checkUser;

	userKey* tempKey = new userKey(uName);

	checkUser = userTable->get(tempKey);

	delete tempKey;

	return checkUser;

}

void userList::removeUser(user *toDelete)
{
	//toDelete->printUserInfo();

	userKey* removeKey = new userKey(toDelete->returnUsername());

	userTable->remove(removeKey);
	totalUsers--;

	//remove from the vector too
	IDUserVector->at(toDelete->returnID()) = NULL;

	//once the user is removed, have to remove their friendships from all the networks
	

	for (int t = 0; t < IDUserVector->size(); ++t)
	{

		if (IDUserVector->at(t) == NULL)
			{	}	//do nothing
		else
		{
			user* editUser = IDUserVector->at(t);

			int counter = 0;

			doubleSizeArray<user*> *ptr;
			doubleIterator<user*> dBegin;
			doubleIterator<user*> dEnd;


			if (editUser->network() == NULL)
			{
				// don't bother fixing the network
			}
			else
			{
				//get network and clear the network of toDelete
				ptr = editUser->network();
				dBegin = ptr->begin();
				dEnd = ptr->end();

				for (doubleIterator<user*> dIt = dBegin; dIt != dEnd; ++dIt)
				{
					if ((*(*dIt)) == toDelete)
					{
						editUser->removeFriendByIndex(counter, true);
						break;
					}
					++counter;
				}

				counter = 0;
			}
			
			//same process with pending requests
			if (editUser->requests() == NULL)
			{
				//don't bother fixing the requests since it's empty
			}
			else
			{
				ptr = editUser->requests();
				dBegin = ptr->begin();
				dEnd = ptr->end();
				for (doubleIterator<user*> dIt = dBegin; dIt != dEnd; ++dIt)
				{
					if ((*(*dIt)) == toDelete)
					{
						editUser->removeRequest(counter, true);
						break;
					}
					++counter;
				}

				counter = 0;
			}

		}
	}
	
}

void userList::printAllUsers() const
{

	for (int t = 0; t < IDUserVector->size(); ++t)
	{
		if (IDUserVector->at(t) == NULL)
			{	} // do nothing
		else
		{
			(IDUserVector->at(t))->printUserInfo();
			cout << endl;
		}
	}

}


int userList::returnTotalUsers()
{
	return totalUsers;
}

bool userList::containsUser(string uName)
{
	//only checks for username

	user* checkUser;

	userKey* tempKey = new userKey(uName);

	bool found = userTable->contains(tempKey); 

	delete tempKey;


	return found;


}

user* userList::getUserPtr(string uName)
{
	userKey* tempKey = new userKey(uName);

	user* result = userTable->get(tempKey);

	delete tempKey;
	return result;
}

