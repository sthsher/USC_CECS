#include <iostream>
#include "userList.h"

using namespace std;

//Constructor: reads the file and initializes all data
userList::userList()
{

	string tempA, tempB;
	int tempInt;
	maxID = 0;

	userListPtr = new LListSet<user*>;	//makes new list


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

			string userInfo[4];
			userInfo[0] = tempA;
			for (int i = 1; i < 4; ++i)
			{
				fin >> tempA;
				userInfo[i] = tempA;
			}
			user* newUser = new user(userInfo);

			fin >> tempInt;
			newUser->setPostNum(tempInt);
			fin >> tempInt;
			newUser->setFriendNum(tempInt);
			fin >> tempInt;
			newUser->setRequestNum(tempInt);
			fin >> tempInt;
			newUser->setID(tempInt);
			if (tempInt > maxID)
				maxID = tempInt;

			userListPtr->add(newUser);

			totalUsers++;

			//newUser->printUserInfo();

		}

		//cout << "Done with user" << endl;

		//Set posts for each user
		LLIterator<user*> beginIt = userListPtr->begin();
		LLIterator<user*> endIt   = userListPtr->end();
		for (LLIterator<user*> it = beginIt; it != endIt; ++it)
		{
			int authorID;
			int commentNum;
			int creationTime;
			wall *newWall = new wall;

			//loop though the number of posts the person has
			int postNum = ((*it))->returnNumOfPosts();
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

				//newPost->setNumOfComments(commentNum);

				//iterate through list and find corresponding user
				for (LLIterator<user*> itz = beginIt; itz != endIt; ++itz)
				{
					if ((*itz)->returnID() == authorID)
					{
						newPost->setAuthor((*itz)->returnFullName());
						break;
					}
				}

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

					//iterate through list and find corresponding user
					for (LLIterator<user*> itz = beginIt; itz != endIt; ++itz)
					{
						if ((*itz)->returnID() == commentAuthorID)
						{
							newComment->setAuthor((*itz)->returnFullName());
							break;
						}
					}
					newComment->setComment(commentContent);

					//newComment->printComment(1);

					newPost->addComment(newComment, true);

				}

				//newPost->setAuthor((*it)->returnFullName());
				

				newPost->setPost(tempA);

				newWall->addPost(newPost);

				//cout << authorID << endl;
				//cout << tempA << endl;
			}
			//wall is made, set it
			(*it)->setWall(newWall);
		}

		int thing = 1;

		//cout << "Done with posts" << endl;
		//set friends for user
		for (LLIterator<user*> it = beginIt; it != endIt; ++it)
		{

			int friendNum = (*it)->returnNumOfFriends();
			if (friendNum == 0)
			{
				string dump;
				fin >> dump;
			}
			else
			{
				(*it)->setFriendNum(0);
				int friendID;
				for (int i = 0; i < friendNum; ++i)
				{
					fin >> friendID;
					//go through the userList an find the right friend
					for (LLIterator<user*> friendIt = beginIt; friendIt != endIt; ++friendIt)
					{
						if ((*friendIt)->returnID() == friendID)
						{
							(*it)->addFriend((*friendIt), true);
							break;
						}
					}

				}
			}



		}

		//cout << "Done with network" << endl;

		//set pending requests
		for (LLIterator<user*> it = beginIt; it != endIt; ++it)
		{
			int requestNum = (*it)->returnNumOfRequests();
			if (requestNum == 0)
			{
				string dump;
				fin >> dump;
			}
			else
			{
				(*it)->setRequestNum(0);
				int requestID;
				for(int i = 0; i < requestNum; ++i)
				{
					fin >> requestID;
					for (LLIterator<user*> requestIt = beginIt; requestIt != endIt; ++requestIt)
					{
						if ((*requestIt)->returnID() == requestID)
						{
							(*it)->addRequest((*requestIt),true);
							break;
						}
					}
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

	//this is the first line
	//fout<<"<<<NEWUSER>>>"<<endl;

	//goes through all the users
	//user iterators

	int tempCounter = 0; //keeps track of how many users have been written

	LLIterator<user*> beginIt = userListPtr->begin();
	LLIterator<user*> endIt = userListPtr->end();

	for (LLIterator<user*> it = beginIt; it != endIt; ++it, tempCounter++)
	{

		//test if this is last user
		if ((tempCounter+1) == totalUsers)
		{	
			isLast = true;
		}

		//write user information first
		//get the current user the iterator is on
		user *outUser = (*it);

		for (int i = 0; i < 4; i++)
		{
			fout<<outUser->returnUserInfoInt(i)<<" ";
		}

		fout << outUser->returnNumOfPosts() << " ";
		fout << outUser->returnNumOfFriends() << " ";
		fout << outUser->returnNumOfRequests() << " ";
		fout << outUser->returnID() << " ";

		fout<<endl;
		
		if(isLast)
		{
			fout<<"<<<END>>>";
			fout << endl;
			//fout.close();
			break;
		}
		
	}

	for (LLIterator<user*> it = beginIt; it != endIt; ++it)
	{
		wall* outWall = (*it)->returnWall();
		fout.close();
		delete outWall;		
	}

	fout.open("user_info_file.txt", ios::app);

	//write friends
	for (LLIterator<user*> it = beginIt; it != endIt; ++it)
	{
		int friendNum = (*it)->returnNumOfFriends();
		if (friendNum == 0)
		{
			fout << "NONE" << endl;
		}
		else
		{
			for (int i = 0; i < friendNum; ++i)
			{
				fout << (*it)->network()->get(i)->returnID() << " ";
			}
			fout << endl;
		}
	}

	//write requests
	for (LLIterator<user*> it = beginIt; it != endIt; ++it)
	{
		int requestNum = (*it)->returnNumOfRequests();
		if (requestNum == 0)
		{
			fout << "NONE" << endl;
		}
		else
		{
			for (int i = 0; i < requestNum; ++i)
			{
				fout << (*it)->requests()->get(i)->returnID() << " ";
			}
			fout << endl;
		}
	}	

}

void userList::addUser(user *newUser)
{
	//giver user its ID
	newUser->setID(++maxID);
	userListPtr->add(newUser);
	totalUsers++;
}

LListSet<user*>* userList::returnPtr()
{
	return userListPtr;
}


user* userList::returnUser(const string &fName, const string &lName, const string &password)
{
	//when loggin in, only have information of first name, last name, and password
	//operator == only checks for those three fields
	//therefore can put arbitrary number for age and number of posts field

	string info[6];
	info[0] = fName;
	info[1] = lName;
	info[2] = "0";		//age
	info[3] = password;
	info[4] = "0";		//numOfPosts
	info[5] = "0";		//friends

	//creats a checkUser based on the given information
	user checkUser(info);

	//iterate through list and find the corresponding user, and return it
	LLIterator<user*> beginIt = userListPtr->begin();
	LLIterator<user*> endIt = userListPtr->end();

	for (LLIterator<user*> it = beginIt; it != endIt; ++it)
	{
		//if found the old user that we want to overwrite
		if (*(*it) == checkUser)
		{
			return (*it);
		}
	}
}

void userList::removeUser(user *toDelete)
{
	userListPtr->remove(toDelete);
	totalUsers--;

	//once the user is removed, have to remove their friendships from all the networks
	LLIterator<user*> beginIt = userListPtr->begin();
	LLIterator<user*> endIt = userListPtr->end();

	//go through all the users
	for (LLIterator<user*> it = beginIt; it != endIt; ++it)
	{
		int counter = 0;

		doubleSizeArray<user*> *ptr;
		doubleIterator<user*> dBegin;
		doubleIterator<user*> dEnd;


		if ((*it)->network() == NULL)
		{
			// don't bother fixing the network
		}
		else
		{
			//get network and clear the network of toDelete
			ptr = (*it)->network();
			dBegin = ptr->begin();
			dEnd = ptr->end();

			for (doubleIterator<user*> dIt = dBegin; dIt != dEnd; ++dIt)
			{
				if ((*(*dIt)) == toDelete)
				{
					(*it)->removeFriendByIndex(counter, true);
					break;
				}
				++counter;
			}

			counter = 0;
		}
		
		//same process with pending requests
		if ((*it)->requests() == NULL)
		{
			//don't bother fixing the requests since it's empty
		}
		else
		{
			ptr = (*it)->requests();
			dBegin = ptr->begin();
			dEnd = ptr->end();
			for (doubleIterator<user*> dIt = dBegin; dIt != dEnd; ++dIt)
			{
				if ((*(*dIt)) == toDelete)
				{
					(*it)->removeRequest(counter, true);
					break;
				}
				++counter;
			}

			counter = 0;
		}
	}
	
}

void userList::printAllUsers() const
{
	int counter = 1; //outputs the user number to keep track

	LLIterator<user*> beginIt = userListPtr->begin();
	LLIterator<user*> endIt = userListPtr->end();

	for (LLIterator<user*> it = beginIt; it != endIt; ++it, ++counter)
	{
		cout << "User No. " << counter << endl;
		((*it))->printUserInfo();
		cout << endl;
	}

}


int userList::returnTotalUsers()
{
	return totalUsers;
}

bool userList::containsUser(const string &fName, const string &lName, const string &password)
{
	//only check for first name, last name, and password
	//age and number of posts and friends is arbitrary
	string info[6];
	info[0] = fName;
	info[1] = lName;
	info[2] = "0";		//age
	info[3] = password;
	info[4] = "0";		//numOfPosts
	info[5] = "0";		//numOfFriends

	//creats a checkUser based on the given information
	user checkUser(info);

	//iterate through list and find the corresponding user, and return it
	LLIterator<user*> beginIt = userListPtr->begin();
	LLIterator<user*> endIt = userListPtr->end();

	for (LLIterator<user*> it = beginIt; it != endIt; ++it)
	{
		//if found the old user that we want to overwrite
		if ((*it)->testLogIn(checkUser))
		{
			return true;
		}
	}

	return false;
}

