#include <iostream>

using namespace std;

//Constructor: reads the file and initializes all data
userList::userList()
{

	ifstream fin;
	bool isEnd = false;					//check if it is at the end of file

	userListPtr = new LListSet<user*>;	//makes new list
	
	totalUsers = 0;						//Keeps track of total users

	string userInfo[6];					//Stores user information
	string tempA;						//used for dump or checking markers
	string tempB;
	fin.open("user_info_file.txt");

	//gets the first line <<<NEWUSER>>, get rid of it
	fin>>tempA;
	tempA = "";


	if(fin == NULL)
	{
		cout<<"Error: File not found, please check directory for info file"<<endl<<endl;
		cout<<"---Program End---"<<endl;
		exit(1);
	}

	while (isEnd == false)
	{
		if(fin.eof())
		{
			fin.close();
			break;
		}
		else
		{
			//gets the user info line
			for (int i = 0; i < 5; i++)
			{
				fin>>userInfo[i];
			}

			//When initializing the network, it will update the number of friends from 0
			userInfo[5] = "0";

			//Make a new user and initialize with the information
			user *newUser = new user(userInfo);

			//Make a new wall for the user
			wall *newWall = new wall;

			//Debuging statement
			//newUser.printUserInfo();

			//get the next line
			getline(fin,tempA);

			//loops until all posts have been added to the user's wall
			while (true)
			{
				//make new wallpost
				wallPost newPost;

				//get the author's information
				getline(fin,tempA);
				//cout<<"tempA: "<<tempA<<endl;
				if(tempA == "<<<NEWUSER>>>") 
				{
					//getline(fin,tempA);
					break;
				}
				if(tempA == "<<<END>>>")
				{
					isEnd = true;
					break;
				}

				//set the author, get the post, and set the post
				newPost.setAuthor(tempA);
				getline(fin,tempA);
				newPost.setPost(tempA);

				//debugging statement
				//newPost.printPost(1);

				//Add the new post to the wall
				newWall->addPost(newPost);

			}

			//Wall created, add to user
			newUser->setWall(newWall);

			//user ready, add to list

			//debugging
			//newUser->printUserInfo();

			userListPtr->add(newUser);
			totalUsers++;

			if (isEnd == true)
			{
				break;
			}

		}
	}

	//MORE FILE IO!!!!!!! GET THE NETWORKS SET UP


	//iterators keeps track of which user to initialize
	LLIterator<user*> beginIt = userListPtr->begin();
	LLIterator<user*> endIt = userListPtr->end();

	//for friend network
	for (LLIterator<user*> userIt = beginIt; userIt != endIt; ++userIt)
	{
		//get line after <<<END>>>
		fin >> tempA;

		while (true)
		{
			//End cases:

			if (tempA == "NONE")
			{
				//no friends yet, just skip
			}

			if (tempA == "<<<MARKER>>>")
			{
				//move on to next user, therefore break from while loop
				break;
			}


			else
			{
				//tempA now holds the first name of the first user, get last name
				fin >> tempB;

				//make a temp user to compare
				//user == operator only compares first and last name, so the rest of the fields is unneccisary
				string tempInfo[6];
				tempInfo[0] = tempA;
				tempInfo[1] = tempB;

				//make the user
				user compareUser(tempInfo);

				//now find the corresponding user and add it to the user's network
				for (LLIterator<user*> it = beginIt; it != endIt; ++it)
				{
					//*(*it) will give you the user
					//user found. add the iterator as a friend
					if ( (*(*it)) == compareUser)
					{
						(*userIt)->addFriend(*it);
					}
				}

				//user successfully added! move on to next
			}

			//gets the next string to check
			fin >> tempA;

		}

	}

	//tempA is now at last marker. get the next one!

	//Now for pending requests
	//same process as above, but store it in the friend request array
	for (LLIterator<user*> userIt = beginIt; userIt != endIt; ++userIt)
	{
		fin >> tempA;

		while (true)
		{

			//end cases
			if (tempA == "NONE")
			{
				//no friends yet, just skip
				//get rid of the next <<<MARKER>>>
			}

			else if (tempA == "<<<MARKER>>>")
			{
				break;
			}

			else if (tempA == "<<<END>>>")
			{
				//end of file, return
				return;
			}

			else
			{
				//tempA now holds the first name of the first user, get last name
				fin >> tempB;

				//make a temp user to compare
				//user == operator only compares first and last name, so the rest of the field is unneccisary
				string tempInfo[6];
				tempInfo[0] = tempA;
				tempInfo[1] = tempB;

				user compareUser(tempInfo);

				//now find the corresponding user and add it to the user's network
				for (LLIterator<user*> it = beginIt; it != endIt; ++it)
				{
					//*(*it) will give you the user
					if ( (*(*it)) == compareUser)
					{
						(*userIt)->addRequest(*it);
						break;
					}
				}

				//user successfully added! move on to next
			}

			//gets the next string to check
			fin >> tempA;

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
	fout<<"<<<NEWUSER>>>"<<endl;

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

		for (int i = 0; i < 6; i++)
		{
			fout<<outUser->returnUserInfoInt(i)<<" ";
		}
		fout<<endl;
		

		//Now output posts
		//Make a wall for the user
		wall *outWall = outUser->returnWall();

		//close the file so the wall destructor can write on it
		fout.close();


		//destructor of wall will write in the file
		delete outWall;

		//open the file again
		fout.open("user_info_file.txt", ios::app);

		//Last user reached, output the end marker, if not put new user marker
		if(isLast)
		{
			fout<<"<<<END>>>";
			//fout.close();
			break;
		}
		
		else
			fout<<"<<<NEWUSER>>>"<<endl;


	}

	//Now print the friend network
	//make new line after the <<<END>>> marker
	fout << endl;

	//print network

	for (LLIterator<user*> userIt = beginIt; userIt != endIt; ++userIt)
	{
		//print current iterator's user's network
		//'d' in the names of the iterator denotes the iterator type
		//d = doubleArray

		if ((*userIt)->network() == NULL)
		{
			//it is empty. No friends write NONE
			fout << "NONE" << endl;
			fout << "MARKER" << endl;
		}
		else
		{
			//go through entire friend array and print it
			doubleIterator<user*> dBeginIt = (*userIt)->network()->begin();
			doubleIterator<user*> dEndIt   = (*userIt)->network()->end();
			for (doubleIterator<user*> dIt = dBeginIt; dIt != dEndIt; ++dIt)
			{
				fout << (*(*dIt))->returnFullName() << " ";
			}

			//done printing. print MARKER on the next line
			fout << endl;
			fout << "<<<MARKER>>>" << endl;
		}
	}

	//print pending requests

	//same process as above but need to check for the very last user to print in order
	//to print the <<<END>>> marker
	//done by making a new iterator called checkEndIt, which will always be one position ahead
	//of the current iterator. If that is the end, it means that we are at the last user
	LLIterator<user*> checkEndIt = beginIt;
	++checkEndIt;
	for (LLIterator<user*> userIt = beginIt; userIt != endIt; ++userIt, ++checkEndIt)
	{
		//print curretn iterator's user's network
		//'d' in the names of the iterator denotes the iterator type
		//d = doubleArray
		if (checkEndIt != endIt)
		{

			if ((*userIt)->requests() == NULL)
			{
				//it is empty. write NONE
				fout << "NONE" << endl;
				fout << "<<<MARKER>>>" << endl;
			}
			else
			{

				doubleIterator<user*> dBeginIt = (*userIt)->requests()->begin();
				doubleIterator<user*> dEndIt   = (*userIt)->requests()->end();
				for (doubleIterator<user*> dIt = dBeginIt; dIt != dEndIt; ++dIt)
				{
					fout << (*(*dIt))->returnFullName() << " ";
				}

				fout << endl;
				fout << "<<<MARKER>>>" << endl;
			}
		}
		//Last user. Instead of <<<MARKER>>> and a new line, simply <<<END>>> and close the file
		else
		{
			//last one! do the same thing except output <<<END>>>
			if ((*userIt)->requests() == NULL)
			{
				//it is empty. write NONE
				fout << "NONE" << endl;
				fout << "<<<END>>>";
				break;

			}
			else
			{
				doubleIterator<user*> dBeginIt = (*userIt)->requests()->begin();
				doubleIterator<user*> dEndIt   = (*userIt)->requests()->end();
				for (doubleIterator<user*> dIt = dBeginIt; dIt != dEndIt; ++dIt)
				{
					fout << (*(*dIt))->returnFullName() << " ";
				}

				fout << endl;
				fout << "<<<END>>>";
				break;
			}
		}


	}

	fout.close();

	//deallocate memeory
	delete userListPtr;

}

void userList::addUser(user *newUser)
{
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
					(*it)->removeFriend(counter);
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
					(*it)->removeRequest(counter);
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

