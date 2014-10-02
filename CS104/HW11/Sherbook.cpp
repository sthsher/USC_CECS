//Consol input/ouput functions
#include <iostream>
#include <iomanip>

//String functions
#include <string>
#include <string.h>
#include <sstream>

//File input/output functions
#include <fstream>

//For MD5
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Standard Library
#include <vector>
#include <cctype>
#include <stdexcept>
#include <ctime>
#include <functional>
#include <deque>

//Classes
#include "Classes/hash/hashTable.h"
#include "Classes/listLibrary/linkedList/LListSet.h"
#include "Classes/listLibrary/arrayLists/doubleSizeArray.h"
#include "Classes/userList/userList.h"
#include "Classes/user/user.h"
#include "Classes/wall/wall.h"
#include "Classes/wallPost/wallPost.h"
#include "Classes/postComment/postComment.h"

using namespace std;

//******************** MD5 Encryption *************************
//	Taken directly from wikipedia. Refer to the README for more information

// Constants are the integer part of the sines of integers (in radians) * 2^32.
const uint32_t k[64] = {
0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
 
// r specifies the per-round shift amounts
const uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                      5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
 
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
 
void to_bytes(uint32_t val, uint8_t *bytes)
{
    bytes[0] = (uint8_t) val;
    bytes[1] = (uint8_t) (val >> 8);
    bytes[2] = (uint8_t) (val >> 16);
    bytes[3] = (uint8_t) (val >> 24);
}
 
uint32_t to_int32(const uint8_t *bytes)
{
    return (uint32_t) bytes[0]
        | ((uint32_t) bytes[1] << 8)
        | ((uint32_t) bytes[2] << 16)
        | ((uint32_t) bytes[3] << 24);
}
 
void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {
 
    // These vars will contain the hash
    uint32_t h0, h1, h2, h3;
 
    // Message (to prepare)
    uint8_t *msg = NULL;
 
    size_t new_len, offset;
    uint32_t w[16];
    uint32_t a, b, c, d, i, f, g, temp;
 
    // Initialize variables - simple count in nibbles:
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
 
    //Pre-processing:
    //append "1" bit to message    
    //append "0" bits until message length in bits ≡ 448 (mod 512)
    //append length mod (2^64) to message
 
    for (new_len = initial_len + 1; new_len % (512/8) != 448/8; new_len++)
        ;
 
    msg = (uint8_t*)malloc(new_len + 8);
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 0x80; // append the "1" bit; most significant bit is "first"
    for (offset = initial_len + 1; offset < new_len; offset++)
        msg[offset] = 0; // append "0" bits
 
    // append the len in bits at the end of the buffer.
    to_bytes(initial_len*8, msg + new_len);
    // initial_len>>29 == initial_len*8>>32, but avoids overflow.
    to_bytes(initial_len>>29, msg + new_len + 4);
 
    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    for(offset=0; offset<new_len; offset += (512/8)) {
 
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        for (i = 0; i < 16; i++)
            w[i] = to_int32(msg + offset + i*4);
 
        // Initialize hash value for this chunk:
        a = h0;
        b = h1;
        c = h2;
        d = h3;
 
        // Main loop:
        for(i = 0; i<64; i++) {
 
            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }
 
            temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;
 
        }
 
        // Add this chunk's hash to result so far:
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
 
    }
 
    // cleanup
    free(msg);
 
    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    to_bytes(h0, digest);
    to_bytes(h1, digest + 4);
    to_bytes(h2, digest + 8);
    to_bytes(h3, digest + 12);
}

//*******************************************************************************************

//takes a string and returns a string that is encrypted by MD5
string encrypt(string password)
{
	//md5 the password
	//preparation
	size_t pLength = password.size();
	uint8_t result[16];

	char* msg = &password[0];

	md5((uint8_t*)msg, pLength, result);

	//result now holds the encrypted password. fprintf it and get it back from the file
	FILE * pfile = fopen("temp.txt", "w");

	for (int i = 0; i < 16; ++i)
		fprintf(pfile, "%2.2x", result[i]);

	fclose(pfile);

	ifstream fin;
	fin.open("temp.txt");
	fin >> password;

	fin.close();

	remove("temp.txt");

	return password;
}

//returns the degree of separation between two users
int degreeOfSeparation(user* currentUser, user* targetUser, userList* list)
{

	cout << endl;
	cout << "From " << currentUser->returnFullName() << " to " << targetUser->returnFullName() << endl;

	//standard breadth first search process
	//userFlags determins whether a user has been visited or not
	//separation keeps track of the degrees of separation as integers
	bool* userFlags = new bool[list->returnTotalUsers()];
	for (int i = 0; i < list->returnTotalUsers(); ++i)
	{
		userFlags[i] = false;
	}

	deque<user*> queue;
	deque<int> separation;

	//add the currentuser to the queue

	queue.push_front(currentUser);
	separation.push_front(1);


	while (!queue.empty())
	{
		//get the network from the queue
		user* u = queue.back();
		doubleSizeArray<user*>* net = u->network();
		
		//go through the network
		doubleIterator<user*> begin = net->begin();
		doubleIterator<user*> end = net->end();
		for (doubleIterator<user*> it = begin; it != end; ++it)
		{
			//only look at it if it hasn't been looked at before
			if (userFlags[(*(*it))->returnID()] == false)
			{
				if (*(*it) == targetUser)
				{
					return (separation.back());
				}
				else
				{
					//mark as seen
					userFlags[(*(*it))->returnID()] = true;
					//add to queue
					queue.push_front(*(*it));
					separation.push_front(separation.back()+1);
				}
			}
		}

		queue.pop_back();
		separation.pop_back();

	}

	throw logic_error("No path found to desired user");
}

bool compareByCreation_Greater(wallPost* postA, wallPost* postB)
{
	if (postA->returnCreationTime() > postB->returnCreationTime())
		return true;
	return false;
}

bool compareByActivity_Greater(wallPost* postA, wallPost* postB)
{
	if (postA->returnLatestTime() > postB->returnLatestTime())
		return true;
	return false;
}

//finds a string in a larger string. Used for name comparison
bool stringCompare(string content, string full)
{
	//default value: not found
	bool skip = false;

	if (content == full)
		return true;

	for (int i = 0; i < (full.size() - content.size())+1; ++i)
	{
		if (tolower(full[i]) == tolower(content[0]))
		{
			for (int j = 0; j < content.size(); ++j)
			{
				//case break: doesn't match
				if (tolower(full[i+j]) != tolower(content[j]))
				{
					skip = true;
					break;
				}

				//mismatch - break;
				if (skip)
					break;

			}
			//case break never reached, meaning the string matches
			if (!skip)
				return true;

			//reset skip boolean
			skip = false;
		}
		//no matching first char, continue
	}
	return false;
}

//takes first name and last name and makes the entire full name in one string
string constructName(string firstName, string lastName)
{
		string fullName;

		stringstream ss;
		ss.str(firstName + " " + lastName);
		fullName = ss.str();

		return fullName;
}

//Checking for any of the key words. If so, return true
bool checkCancel(string s)
{
		if (s == "RESTART" || s == "restart" || s == "Restart" ||
				s == "EXIT" || s == "Exit" || s == "exit" ||
				s == "Back" || s == "BACK" || s == "back" ||
				s == "Logout" || s == "LOGOUT" || s == "logout" || s == "LogOut")
		{
				return true;
		}

		return false;
}

//Creates new account
void createAccount(userList *list)
{
		cout<<endl<<"Enter \"RESTART\" in any field to start over if you make a mistake"<<endl;

		//Stores new user information
		string newFName, newLName, newDOB, newPassword, confirmPassword, newUsername, newSecurityQ, newSecurityA;

		bool repeat = true;
		bool requestRepeat = false;
		bool passwordIsGood = false;

		while (repeat == true)  //Keeps looping until user finishes. Allows user to redo fields
		{
				while (true)
				{
						requestRepeat = false;
						passwordIsGood = false;
						cout<<"-----------------------------------------------------------------"<<endl;
																																										//These lines check if user requested to restart their data entry
						cout<<"                    Please enter your username: ";cin>>newUsername;							requestRepeat = checkCancel(newUsername); if (requestRepeat) break;
						cout<<"                  Please enter your first name: ";cin>>newFName;                              requestRepeat = checkCancel(newFName); if (requestRepeat) break;
						cout<<"                   Please enter your last name: ";cin>>newLName;                              requestRepeat = checkCancel(newLName); if (requestRepeat) break;
						cout<<"               Please enter your date of birth " << endl;
						cout<<"   format: \"MM/DD/YYYY\" including parentheses: ";cin>>newDOB;                                requestRepeat = checkCancel(newDOB); if (requestRepeat) break;

						while(passwordIsGood == false) //Makes sure passwords are the same
						{
						cout<<"                    Please enter your password: ";cin>>newPassword;           requestRepeat = checkCancel(newPassword); if (requestRepeat) break;     
						cout<<"                  Please confirm your password: ";cin>>confirmPassword;       requestRepeat = checkCancel(confirmPassword); if (requestRepeat) break; 

								if (newPassword == confirmPassword)     passwordIsGood = true;
								else cout<<endl<<"Error: Passwords don't match."<<endl<<endl;
						}

						cout<<"Please enter a security question:" << endl;
						getline(cin, newSecurityQ);		//getline bugs: need to get rid of first line
						getline(cin, newSecurityQ);
							if (checkCancel(newSecurityQ)) break;

						cout<<"Please enter the answer to the security quesiton: \"" << newSecurityQ << "\"" << endl;
						getline(cin, newSecurityA);
							if (checkCancel(newSecurityA)) break;

						if (requestRepeat == true) break;

						cout<<"-----------------------------------------------------------------"<<endl<<endl;

						repeat = false;
						break;
				}
		}

		//The user has inputted information

		//Check if user already exists: If they exist, output an error and return
		bool isUser = list->containsUser(newUsername);
		char dump;

		//go through the list and
		//compare if name exists
		
		// LLIterator<user*> beginIt = list->returnPtr()->begin();
		// LLIterator<user*> endIt = list->returnPtr() ->end();
		// for (LLIterator<user*> it = beginIt; it != endIt; ++it)
		// {
		// 	if ((*it)->returnUsername() == newUsername)
		// 	{
		// 		//user already exists;
		// 		isUser = true;
		// 	}
		// }

		if (isUser == true)     
		{
				cout<<"Error: User already exists!"<<endl;
				cout<<"Enter any key to return to menu: ";cin>>dump;cout<<endl;
				return; 
		}
		//New user does not exist. Make a new user

		//cout<<"creating new user"<<endl;

		//create the new user
		user *newUser = new user;

		//Fill in the user's information
		newUser->setUserInfo(newFName,0);
		newUser->setUserInfo(newLName,1);
		newUser->setUserInfo(newDOB,2);

		newUser->setUsername(newUsername);

		//md5 the password
		newPassword = encrypt(newPassword);

		newUser->setUserInfo(newPassword,3);

		//Make a new wall for the user
		wall *newWall = new wall;

		//Wall is empty, so just add the wall to the user
		newUser->setWall(newWall);

		//Show the new user's info
		newUser->printUserInfo();

		//Add the user the the list
		list->addUser(newUser);

		//Pause before proceeding
		char proceed;
		cout<<"Congratulations! You have created your account!"<<endl;
		cout<<"Enter any key to return to the main menu: ";cin>>proceed;cin.ignore(256,'\n');cout<<endl<<endl;
}

//Takes in the cin of the first word of the post and the getline of the rest of the post and combines them together
//Solves the problem of messy getline bugs from only using getline by using stringstream
string constructString(string dump, string post)
{
		string fullPost;

		stringstream ss;
		ss.str(dump + post);
		fullPost = ss.str();

		return fullPost;
}

//Allows user to create a post
wallPost* createPost(user *currentUser)
{
		//Get the wall of the user
		wall *userWall = currentUser->returnWall();

		//Make a new wallpost
		wallPost* newPost = new wallPost;

		//Used to store the post
		string dump;
		string post;

		//User input the post
		cout<<"*Remember, posts can only be 1 line long*"<<endl<<endl;
		cout<<"------------------"<<endl;
		cout<<"|Write a new post|"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl<<endl;
		cout<<"New post: ";cin>>dump;getline(cin,post);
		cout<<endl;
		cout<<"-----------------------------------------------------------------"<<endl<<endl;

		//Construct the post from dump and post
		post = constructString(dump, post);

		//Set post author as current user author and set the post
		newPost->setAuthor(currentUser->returnFullName());
		newPost->setPost(post);
		newPost->setAuthorID(currentUser->returnID());

		cout<<"--Post Successfully Created--"<<endl;
		cout << "Enter any key to continue"; cin >> dump; cin.ignore(256,'\n');		

		return newPost;
}

//Allows user to create a comment
postComment* createComment(user *currentUser)
{
		//Make a new postComment
		postComment* newComment = new postComment;

		//Used to store the comment
		string dump;
		string comment;

		//User input the comment
		cout<<"*Remember, comments can only be 1 line long*"<<endl<<endl;
		cout<<"------------------"<<endl;
		cout<<"|Write a new comment|"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl<<endl;
		cout<<"New comment: ";cin>>dump;getline(cin,comment);
		cout<<endl;
		cout<<"-----------------------------------------------------------------"<<endl<<endl;

		//Construct the comment from dump and comment
		comment = constructString(dump, comment);

		//Set post author as current user author and set the comment
		newComment->setAuthor(currentUser->returnFullName());
		newComment->setComment(comment);
		newComment->setAuthorID(currentUser->returnID());

		cout<<"--Comment Successfully Created--"<<endl;
		cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');		

		return newComment;
}

void deleteComment(user* currentUser, user* postOwner, bool bypass, wallPost* post)
{
	cout<<endl;

	int toDelete;

	//Get max number of posts to verify validity of user's input
	
	int totalComments = post->returnNumOfComments();

	while (true)
	{
		post->printPost();
		post->printAllComments();
		cout<<endl<<"Please select which comment to delete"<<endl;
		cout<<endl<<"Or enter '0' to go back to the menu: "<<endl;
		cout<<"Delete post ";cin>>toDelete;cout<<endl;

		if (toDelete == 0)
		{
				return;
		}
		else if (toDelete > totalComments) //requested number does not exist
		{
				cout<<"Error: Post "<<toDelete<<" does not exist"<<endl;
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
		}
		else
		{
			break;
		}
	}

	//remove post and update wall
	//check if the author of the post is the current user
	if (post->returnCommentByIndex(toDelete-1)->returnAuthorID() == currentUser->returnID() || bypass)
	{
		post->removeCommentByIndex(toDelete-1);

		cout<<"---Comment Successfully Deleted---"<<endl;
		char dump;
		cout << "Enter any key to continue"; cin >> dump; cin.ignore(256,'\n');

		return;
	}
	else
	{
		cout << "Error: This comment does not belong to you" << endl;
		char dump;
		cout << "Enter any key to continue"; cin >> dump; cin.ignore(256,'\n');

		return;
	}
}

//Allows user to delete post
void deletePost(user *currentUser, user *wallOwner, bool bypass)
{
	cout<<endl;

	//get the user's wall
	wall *userWall = wallOwner->returnWall();

	//Get necessary information.
	int toDelete;

	//Get max number of posts to verify validity of user's input
	
	int totalPosts = wallOwner->returnNumOfPosts();

	while (true)
	{
		userWall->printAllPosts(currentUser->sortingMethod, currentUser->isMax);
		cout<<endl<<"Please select which post to delete"<<endl;
		cout<<endl<<"Or enter '0' to go back to the menu: "<<endl;
		cout<<"Delete post ";cin>>toDelete;cout<<endl;

		if (toDelete == 0)
		{
				return;
		}
		else if (toDelete > totalPosts) //requested number does not exist
		{
				cout<<"Error: Post "<<toDelete<<" does not exist"<<endl;
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
		}
		else
		{
			break;
		}
	}

	//remove post and update wall
	//check if the author of the post is the current user
	if (wallOwner->returnWall()->returnPostByIndex(toDelete-1)->returnAuthorID() == currentUser->returnID() || bypass)
	{
		wallOwner->removePostByIndex(toDelete-1, true);
		//wallOwner->setWall(userWall,4,1);

		cout<<"---Post Successfully Deleted---"<<endl;
		char dump;
		cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');

		return;
	}
	else
	{
		cout << "Error: This post does not belong to you" << endl;
		char dump;
		cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');

		return;
	}
}

void postDetailedView(user* currentUser, user* postOwner, userList* list, bool bypass, wallPost* toView)
{
	while (true)
	{
		cout << "-------------------------" << endl;
		cout << "| Viewing Post Details: |" << endl;
		toView->printPost();
		toView->printAllComments();

		cout << endl;
		cout << "1) Post a comment" << endl;
		cout << "2) Delete a comment" << endl;
		cout << "0) Return" << endl;

		char choice;
		cout << "Action: "; cin >> choice; cout << endl;
		

		if (choice == '1')
		{
			postComment* newComment = createComment(currentUser);
			toView->addComment(newComment, true);
		}
		else if (choice == '2')
		{
			deleteComment(currentUser, postOwner, bypass, toView);

		}
		else if (choice == '0')
		{
			return;
		}
		else
		{
			cin.ignore(256, '\n');
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> choice; cout << endl; cin.ignore(256, '\n');
		}
	}
}

//Edit requested field's information of user
//Name can always change (marriage, or when you get a passport you get the chance to change your name)
//Age can also change.
//Password can be changed to user's desired new password
//Number of posts is set, so that cannot change
void editField(user *currentUser, string field, int fieldToEdit)
{
		//int fieldToEdit already stores the array position of the field that needs to be changed

		//Stores new information
		string newInfo;
		
		cout<<field<<" Edit: "<<endl;
		cout<<"-----------------------------------------------------------------"<<endl<<endl;
		cout<<"Please enter the new information for this field:"<<endl;
		cout<<"New "<<field;cout<<": ";cin>>newInfo;cout<<endl;
		cout<<"-----------------------------------------------------------------"<<endl<<endl;

		if (fieldToEdit == 3)
		{
			//encrypt the new password
			newInfo = encrypt(newInfo);
		}

		//Update user information
		currentUser->setUserInfo(newInfo, fieldToEdit);

		cout<<"---Changes Saved---"<<endl;

		return;
}

//Displays menu to edit user's information
void editInformation(user *currentUser)
{
		cout<<endl;
		//Show user's information
		currentUser->printUserInfo();

		string choice;

		cout<<"----------------"<<endl;
		cout<<"| Edit Account |"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl;
		cout<<"Type \"EXIT\" or \"BACK\" anytime to return to the menu"<<endl<<endl;
		cout<<"Select which field you want to edit:"<<endl;
		cout<<"1) First Name"<<endl;
		cout<<"2) Last Name"<<endl;
		cout<<"3) Date of birth"<<endl;
		cout<<"4) Password"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl<<endl;

		while (true)
		{
				cout<<"Input: ";cin>>choice;cout<<endl;

				if(choice == "1")
				{
						editField(currentUser, "First Name", 0);
						cout << "---Information Successfully Updated---" << endl;
						char dump;
						cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');
						break;
				}
				else if (choice == "2")
				{
						editField(currentUser, "Last Name", 1);
						cout << "---Information Successfully Updated---" << endl;
						char dump;
						cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');
						break;
				}
				else if (choice == "3")
				{
						editField(currentUser, "Date of birth", 2);
						cout << "---Information Successfully Updated---" << endl;
						char dump;
						cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');
						break;
				}
				else if (choice == "4")
				{
						editField(currentUser, "Password", 3);
						cout << "---Information Successfully Updated---" << endl;
						char dump;
						cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');
						break;
				}
				else if (choice == "EXIT" || choice == "exit" || choice == "Exit" ||
								 choice == "BACK" || choice == "back" || choice == "Back")
				{
						return;
				}
				else
				{
						cout<<"Error: invalid input"<<endl<<endl;
						cin.ignore(256, '\n');
				}

		}

		return;
}

//sned a request to the selected user
void sendRequest(user *currentUser, doubleSizeArray<user*> *searchResults, userList *list, bool displayUsername)
{
	while(!searchResults->isEmpty())
	{
		doubleIterator<user*> beginIt = searchResults->begin();
		doubleIterator<user*> endIt   = searchResults->end();
		int counter = 0;

		cout<<"-----------------------------------------------------------------"<<endl;
		cout<<"Search Results:" << endl;
		
		for (doubleIterator<user*> it = beginIt; it != endIt; ++it)
		{
			if (displayUsername)
				cout << "User " << ++counter << ": " << (*(*it))->returnUsername() << endl;
			else
				cout << "User " << ++counter << ": " << (*(*it))->returnFullName() << endl;
		}
		cout<<"-----------------------------------------------------------------"<<endl<<endl;
		
		int choice;

		cout << "Please select a user to send a friend request to: " << endl;
		cout << "Enter 0 to return" << endl << endl;

		while (true)
		{
			try
			{
				cout<<"Please enter a choice:";	cin >> choice;

				if (counter >= choice && choice > 0)
				{
					//Get the user to add, and remove it from the results
					user *addUser = searchResults->get(choice-1);
					searchResults->remove(choice-1);
					
					//check if the user to send request to is already in the pending request area
					bool existInRequest = false;
					int counter = 0;
					if (currentUser->requests() != NULL)
					{
						doubleIterator<user*> beginItA = currentUser->requests()->begin();
						doubleIterator<user*> endItA = currentUser->requests()->end();
						for (doubleIterator<user*> itA = beginItA; itA != endItA; ++itA, ++counter)
						{
							if (*(*itA) == addUser)
							{
								//addUser is found in the requests, remove from the requests and set boolean to true
								currentUser->removeRequest(counter, true);
								existInRequest = true;
								break;
							}
						}
					}

					if (existInRequest == true)
					{
						//add friend both ways
						currentUser->addFriend(addUser, true);
						addUser->addFriend(currentUser, true);

						char dump;
						cout << endl << "---Request Successfully Sent---" << endl;
						cout << "Note: User has already sent a request to you. You are now friends with the user" << endl;
						cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl;
						return;


					}
					else if (existInRequest == false)
					{
						//send the request
						//Find addUser in the list

						user* u = list->getUserPtr(addUser->returnUsername());
						u->addRequest(currentUser, true);

						char dump;
						cout << endl << "---Request Successfully Sent---" << endl << endl;
						cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl;
						return;
					}
		 
				}
				else if (choice == 0)
				{
					return;
				}
				else
				{
					cin.ignore(256, '\n');
					throw logic_error("Error: Invalid input. Expecting an int");
				}
			}
			catch(logic_error const &e)
			{
				cout << e.what() << endl;
				cin.ignore(256, '\n');
				char dump;
				cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			}

		}
	}
}

//search for user
void searchUserByName(user *currentUser, userList *list)
{
	string firstPart;
	string searchName;

	doubleSizeArray<user*> *searchResults = new doubleSizeArray<user*>;

	cout<<"---------------------"<<endl;
	cout<<"| Search for a User |"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
	cout<<"Type \"EXIT\" or \"BACK\" anytime to return to the menu"<<endl;
	cout<<"Enter the name you wish to search for (part of a name also works)"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl<<endl;
	cout<<"Search: "; cin >> firstPart;

	if (checkCancel(firstPart))
		return;

	getline(cin, searchName);

	//constructs the search query
	searchName = constructString(firstPart, searchName);

	vector<user*>* vec = list->returnVector();
	//go through all the contents of the table
	for (int i = 0; i < vec->size(); ++i)
	{
		if (vec->at(i) == NULL)
			{	}	//do nothing
		else
		{
			string userName = (vec->at(i))->returnFullName();

			if (stringCompare(searchName, userName))
			{
				if (vec->at(i) == currentUser)
				{
					//the current user, dont' add it to the results
				}
				else
				{
					//add to results
					searchResults->insert(0, vec->at(i));
				}
			}
		}
	}

	while (!searchResults->isEmpty())
	{

		doubleIterator<user*> beginItB = searchResults->begin();
		doubleIterator<user*> endItB   = searchResults->end();

		int counter = 1;

		//display results
		cout<<"-----------------------------------------------------------------"<<endl;
		cout<<"Search Results:" << endl;
		
		for (doubleIterator<user*> it = beginItB; it != endItB; ++it)
		{
			cout << "User " << counter++ << ": " << (*(*it))->returnFullName() << endl;
		}
		cout<<"-----------------------------------------------------------------"<<endl<<endl;

	
		string choice;
		cout << "Please select an action for the results: " << endl;
		cout << "1) Send a friend request" << endl;
		cout << "2) Go back to main menu" << endl;

		cout << endl;
		cout << "Please enter a choice:"; cin >> choice;

		if (choice == "1")
		{
			sendRequest(currentUser, searchResults, list, false);
		}
		else if (choice == "2" || checkCancel(choice))
		{
			delete searchResults;
			return;
		}
		else
		{
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl;
			cin.ignore(256,'\n');
		}
	}		

	cout << "---No More Results---" << endl;
	char dump;
	cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');	
}

//same as searchUserByName except only displaying usernames and no partial comparisons
void searchUserByUsername(user* currentUser, userList* list)
{
	string searchName;

	doubleSizeArray<user*> *searchResults = new doubleSizeArray<user*>;

	cout<<"---------------------"<<endl;
	cout<<"| Search for a User |"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
	cout<<"Type \"EXIT\" or \"BACK\" anytime to return to the menu"<<endl;
	cout<<"Enter the searchName you wish to search for (please enter full username, case sensitive)"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl<<endl;
	cout<<"Search: "; cin >> searchName;

	if (checkCancel(searchName))
		return;

	user* resultUser = list->returnUser(searchName);

	//display results
	cout<<"-----------------------------------------------------------------"<<endl;
	cout<<"User found:" << endl;

	cout << resultUser->returnFullName() << endl;
	
	cout<<"-----------------------------------------------------------------"<<endl<<endl;

	
	string choice;
	cout << "Please select an action for the results: " << endl;
	cout << "1) Send a friend request" << endl;
	cout << "2) Go back to main menu" << endl;

	cout << endl;
	cout << "Please enter a choice:"; cin >> choice;

	if (choice == "1")
	{


					//Get the user to add, and remove it from the results
					user *addUser = resultUser;
					
					//check if the user to send request to is already in the pending request area
					bool existInRequest = false;
					int counter = 0;
					if (currentUser->requests() != NULL)
					{
						doubleIterator<user*> beginItA = currentUser->requests()->begin();
						doubleIterator<user*> endItA = currentUser->requests()->end();
						for (doubleIterator<user*> itA = beginItA; itA != endItA; ++itA, ++counter)
						{
							if (*(*itA) == addUser)
							{
								//addUser is found in the requests, remove from the requests and set boolean to true
								currentUser->removeRequest(counter, true);
								existInRequest = true;
								break;
							}
						}
					}

					if (existInRequest == true)
					{
						//add friend both ways
						currentUser->addFriend(addUser, true);
						addUser->addFriend(currentUser, true);

						char dump;
						cout << endl << "---Request Successfully Sent---" << endl;
						cout << "Note: User has already sent a request to you. You are now friends with the user" << endl;
						cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl;
						return;


					}
					else if (existInRequest == false)
					{
						//send the request
						//Find addUser in the list

						user* u = list->getUserPtr(addUser->returnUsername());
						u->addRequest(currentUser, true);

						char dump;
						cout << endl << "---Request Successfully Sent---" << endl << endl;
						cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl;
						return;
					}





	}
	else if (choice == "2" || checkCancel(choice))
	{
		delete searchResults;
		return;
	}
	else
	{
		char dump;
		cout << "Error: Invalid input" << endl;
		cout << "Enter any key to continue: "; cin >> dump; cout << endl;
		cin.ignore(256,'\n');
	}	

	char dump;
	cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');	
}

void deleteAFriend(user *currentUser, userList *list)
{
	int counter = 0;

	while (currentUser->network() != NULL)
	{
		//display the network
		cout<<"-------------------"<<endl;
		cout<<"| Delete a Friend |"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl;

		if (currentUser->network() == NULL)
		{
			cout << "Your network is currently empty" << endl;
			cout<<"-----------------------------------------------------------------"<<endl;

			char dump;
			cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl << endl;

			return;
		}

		doubleIterator<user*> beginIt = (currentUser->network())->begin();
		doubleIterator<user*> endIt   = (currentUser->network())->end();
		doubleIterator<user*> it;

		//*it gives a pointer to a pointer of a user
		for (it = beginIt; it != endIt; ++it)
		{
			cout << "User " << ++counter << ": " << (*(*it))->returnFullName() << endl;
		}

		cout<<"-----------------------------------------------------------------"<<endl;
			
		int choice;

		cout << "Please select a friend to delete: " << endl;
		cout << "Enter 0 to return" << endl;
		cout << "Delete: "; cin >> choice; cout << endl;

		if (choice == 0)
		{
			return;
		}
		else if (choice <= counter)
		{
			//remove the friend both ways
			it = beginIt;
			for (int i = 0; i < choice-1; ++i)
			{	++it;	}

			//it is now at the user to delete
			(*(*it))->removeFriendByPtr(currentUser, true);

			currentUser->removeFriendByIndex(choice-1, true);
			cout << "---Friend Successfully Deleted---" << endl;
			char dump;
			cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');
		}
		else
		{
			cin.ignore(256,'\n');
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump;
			cin.ignore(256, '\n');
			cout << endl << endl;
		}

		counter = 0;
	}

	cout << "---Your network is empty---" << endl << endl;
	char dump;
	cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl << endl;
	return;
}

void viewPosts(user* currentUser, user* postOwner, userList* list, bool bypass)
{
	while (true)
	{
		if (postOwner->returnNumOfPosts() == 0)
		{
			cout << "This current user has no posts" << endl;
			char dump;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
			return;
		}

		cout << "--------------------------------------------------" << endl;
		cout << "|               Viewing All Posts                |" << endl;

		wall *userWall = postOwner->returnWall();
		userWall->printAllPosts(currentUser->sortingMethod, currentUser->isMax);
		int totalPosts = userWall->returnNumOfPosts();

		int choice;

		cout << endl;
		cout << "To view a post in detail, please enter the post ID" << endl;
		cout << "Or enter \"0\" to return" << endl;
		cout << "Action: "; cin >> choice; cout << endl;

		if (choice == 0)
		{
			return;
		}
		else if (choice > 0 && choice <= totalPosts)
		{
			wallPost* toView = userWall->returnPostByIndex(choice-1);
			postDetailedView(currentUser, postOwner, list, bypass, toView);
		}
		else
		{
			cout << "Error: Invalid input entered" << endl;
			char dump;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
		}

	}
}

void visitFriend(user *currentUser, user *friendUser, userList *list)
{
	while (true)
	{
		cout << "---------------------------" << endl;
		cout << "| Currently viewing user: |" << endl;
		friendUser->printUserInfo();

		string choice;
		cout << "Please select an action for the results: " << endl;
		cout << "1) View " << friendUser->returnFullName() << "'s wall" << endl;
		cout << "2) Write on " << friendUser->returnFullName() << "'s wall" << endl;
		cout << "3) Delete a post by you on " << friendUser->returnFullName() << "'s wall" << endl;
		cout << "0) Return to main menu" 	<< endl;

		cout << endl;
		cout << "Please enter an action:"; cin >> choice;

		if (choice == "0")
		{
			return;
		}
		else if (choice == "1")
		{
			viewPosts(currentUser, friendUser, list, false);
		}
		else if (choice == "2")
		{
			wallPost* newPost = createPost(currentUser);
			friendUser->addPost(newPost, true);
		}
		else if (choice == "3")
		{
			deletePost(currentUser, friendUser, false);
		}
		else
		{
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl;
			cin.ignore(256,'\n');
		}
	}
}

void viewFriend(user *currentUser, userList *list)
{
	int counter = 0;

	while (true)
	{
		//display the network
		cout<<"-----------------"<<endl;
		cout<<"| View a Friend |"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl;

		doubleIterator<user*> beginIt = (currentUser->network())->begin();
		doubleIterator<user*> endIt   = (currentUser->network())->end();
		doubleIterator<user*> it;

		//*it gives a pointer to a pointer of a user
		for (it = beginIt; it != endIt; ++it)
		{
			cout << "User " << ++counter << ": " << (*(*it))->returnFullName() << endl;
		}

		cout<<"-----------------------------------------------------------------"<<endl;
			
		int choice;

		cout << "Please select a friend to view: " << endl;
		cout << "Enter 0 to return" << endl;
		cout << "View: "; cin >> choice; cout << endl;

		if (choice == 0)
		{
			return;
		}
		else if (choice <= counter)
		{
			//find the right user
			user* toVisit = (currentUser->network()->get(choice-1));

			//toVisit->printUserInfo();
			visitFriend(currentUser, toVisit, list);
			return;

		}
		else
		{
			cin.ignore(256,'\n');
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump;
			cin.ignore(256, '\n');
			cout << endl << endl;
		}

		counter = 0;
	}

	cout << "---Your network is empty---" << endl << endl;
	char dump;
	cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl << endl;
	return;
}

void viewNetwork(user *currentUser, userList *list)
{
	cout<<"-----------------------"<<endl;
	cout<<"| Your Friend Network |"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;

	if (currentUser->network() == NULL)
	{
		cout << "Your network is currently empty" << endl;
		cout<<"-----------------------------------------------------------------"<<endl;
		char dump;
		cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');

		return;
	}

	doubleIterator<user*> beginIt = (currentUser->network())->begin();
	doubleIterator<user*> endIt   = (currentUser->network())->end();

	//*it gives a pointer to a pointer of a user
	for (doubleIterator<user*> it = beginIt; it != endIt; ++it)
	{
		cout << (*(*it))->returnFullName() << endl;
	}

	cout<<"-----------------------------------------------------------------"<<endl;
	
	while (true)
	{
		string choice;
		cout << "Please select an action for the results: " << endl;
		cout << "1) View a friend's information" << endl;
		cout << "2) Search and add a friend" 		<< endl;
		cout << "3) Delete a friend" 			<< endl;
		cout << "0) Return to main menu" 	<< endl;

		cout << endl;
		cout << "Please enter an action:"; cin >> choice;

		if (choice == "0")
		{
			return;
		}
		if (choice == "1")
		{
			viewFriend(currentUser, list);
			return;
		}
		if (choice == "2")
		{
			searchUserByName(currentUser, list);
			return;
			//make a new friendNetwork userList
		}
		else if (choice == "3")
		{
			deleteAFriend(currentUser, list);
			return;
		}
		else
		{
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl;
			cin.ignore(256,'\n');
		}
	}	
	return;
}

//menu to accept requests
void acceptRequest(user *currentUser, userList *list)
{
	int counter = 0;

	while (!(currentUser->requests()->isEmpty()))
	{
		doubleIterator<user*> beginIt = (currentUser->requests())->begin();
		doubleIterator<user*> endIt   = (currentUser->requests())->end();
		doubleIterator<user*> it;

		cout<<"-------------------"<<endl;
		cout<<"| Accept Requests |"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl;
		for (it = beginIt; it != endIt; ++it)
		{
			cout << "User " << ++counter << ": "<< (*(*it))->returnFullName() << endl;
		}
		cout<<"-----------------------------------------------------------------"<<endl;

		int choice;

		cout << "Please select a request to accept: " << endl;
		cout << "Enter 0 to return" << endl;
		cout << "Accept: "; cin >> choice; cout << endl << endl;

		if (choice == 0)
		{
			return;
		}
		else if (choice <= counter)
		{
			//move iterator to beginning and to the right user
			it = beginIt;
			for (int i = 0; i < (choice-1); ++i)
			{	++it;	};
			
			//iterator is at right position. *it will return a pointer to a pointer to a user
			//add the user to the network
			currentUser->addFriend((*(*it)), true);

			//add friend both ways
			(*(*it))->addFriend(currentUser, true);

			currentUser->requests()->remove(choice-1);

		}
		else
		{
			cin.ignore(256,'\n');
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump;
			cin.ignore(256, '\n');
			cout << endl << endl;
		}

		counter = 0;
	}

	cout << "--- No more requests ---" << endl;
}

void denyRequest(user *currentUser, userList *list)
{
	int counter = 0;

	while (!(currentUser->requests()->isEmpty()))
	{
		doubleIterator<user*> beginIt = (currentUser->requests())->begin();
		doubleIterator<user*> endIt   = (currentUser->requests())->end();
		doubleIterator<user*> it;

		cout<<"-----------------"<<endl;
		cout<<"| Deny Requests |"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl;
		for (it = beginIt; it != endIt; ++it)
		{
			cout << "User " << ++counter << ": "<< (*(*it))->returnFullName() << endl;
		}
		cout<<"-----------------------------------------------------------------"<<endl;

		int choice;

		cout << "Please select a request to deny: " << endl;
		cout << "Enter 0 to return" << endl;
		cout << "Deny: "; cin >> choice; cout << endl << endl;

		if (choice == 0)
		{
			return;
		}
		else if (choice <= counter)
		{
			//remove the request
			currentUser->requests()->remove(choice-1);
			//(currentUser->network())->insert(0, (*(*it)));

		}
		else
		{
			cin.ignore(256,'\n');
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump;
			cin.ignore(256, '\n');
			cout << endl << endl;
		}

		counter = 0;
	}

	cout << "--- No more requests ---" << endl;
}

void pendingRequests(user *currentUser, userList *list)
{
	//output pending requests
	cout<<"--------------------------------"<<endl;
	cout<<"| Your Pending Friend Requests |"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;

	if (currentUser->requests() == NULL)
	{
		cout << "You currently have no friend requests" << endl;
		cout<<"-----------------------------------------------------------------"<<endl;

		char dump;
		cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');

		return;
	}

	doubleIterator<user*> beginIt = (currentUser->requests())->begin();
	doubleIterator<user*> endIt   = (currentUser->requests())->end();

	for (doubleIterator<user*> it = beginIt; it != endIt; ++it)
	{
		cout << (*(*it))->returnFullName() << endl;
	}
	cout<<"-----------------------------------------------------------------"<<endl;


	while (true)
	{
		string choice;
		cout << "Please select an action for the results: " << endl;
		cout << "0) Return to main menu" 	<< endl;
		cout << "1) Accept request" 		<< endl;
		cout << "2) Deny request" 			<< endl;

		cout << endl;
		cout << "Please enter an action:"; cin >> choice;

		if (choice == "0")
		{
			return;
		}
		if (choice == "1")
		{
			acceptRequest(currentUser, list);
			return;
		}
		else if (choice == "2")
		{
			denyRequest(currentUser, list);
			return;
		}
		else
		{
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl;
			cin.ignore(256,'\n');
		}
	}	
}
void changeSortingMethod(user* currentUser)
{
	while (true)
	{
		cout << "------------------------" << endl;
		cout << "| Post Viewing Options |" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Please select your preferred method of viewing wall posts" << endl;
		cout << "Please note that \"first\" refers to being at the top of the list" << endl;
		cout << "Enter 0 to return" << endl;
		cout << " " << endl;
		cout << "Sort by post's creation time" << endl;
		cout << "1) Newest first" << endl;
		cout << "2) Oldest first" << endl;
		cout << " " << endl;
		cout << "Sort by post's most recent activity" << endl;
		cout << "3) Newest first" << endl;
		cout << "4) Oldest first" << endl;
		cout << "-----------------------------------------------------------------" << endl;

		char choice;
		cout << "Choice: "; cin >> choice; cout << endl;
		if (choice == '0')
		{
			return;
		}
		else if (choice == '1')
		{
			currentUser->sortingMethod = compareByCreation_Greater;
			currentUser->isMax = true;
			cout << "---Preference Successfully Updated---" << endl;
			cout << "Enter any key to continue: "; cin >> choice; cout << endl; cin.ignore(256,'\n');
			return;
		}
		else if (choice == '2')
		{
			currentUser->sortingMethod = compareByCreation_Greater;
			currentUser->isMax = false;
			cout << "---Preference Successfully Updated---" << endl;
			cout << "Enter any key to continue: "; cin >> choice; cout << endl; cin.ignore(256,'\n');			
			return;
		}
		else if (choice == '3')
		{
			currentUser->sortingMethod = compareByActivity_Greater;
			currentUser->isMax = true;
			cout << "---Preference Successfully Updated---" << endl;
			cout << "Enter any key to continue: "; cin >> choice; cout << endl; cin.ignore(256,'\n');			
			return;
		}
		else if (choice == '4')
		{
			currentUser->sortingMethod = compareByActivity_Greater;
			currentUser->isMax = false;
			cout << "---Preference Successfully Updated---" << endl;
			cout << "Enter any key to continue: "; cin >> choice; cout << endl; cin.ignore(256,'\n');			
			return;
		}
		else
		{
			cin.ignore(256, '\n');
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> choice; cout << endl; cin.ignore(256,'\n');
		}
	}
}

//First part is the same as searching a user. second parts simply uses the breadth first search
void findDegree(user* currentUser, userList* list)
{

	string firstPart;
	string searchName;

	doubleSizeArray<user*> *searchResults = new doubleSizeArray<user*>;

	cout<<"------------------------"<<endl;
	cout<<"| Degree of Separation |"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
	cout<<"Type \"EXIT\" or \"BACK\" anytime to return to the menu"<<endl;
	cout<<"Enter the name you wish to search for (part of a name also works)"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl<<endl;
	cout<<"Search: "; cin >> firstPart;

	if (checkCancel(firstPart))
		return;

	getline(cin, searchName);

	//constructs the search query
	searchName = constructString(firstPart, searchName);

	vector<user*>* vec = list->returnVector();
	//go through all the contents of the table
	for (int i = 0; i < vec->size(); ++i)
	{
		if (vec->at(i) == NULL)
			{	}	//do nothing
		else
		{
			string userName = (vec->at(i))->returnFullName();

			if (stringCompare(searchName, userName))
			{
				if (vec->at(i) == currentUser)
				{
					//the current user, dont' add it to the results
				}
				else
				{
					//add to results
					searchResults->insert(0, vec->at(i));
				}
			}
		}
	}

	if (searchResults->isEmpty())
	{
		cout << "No results" << endl;
		char dump;
		cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');	
		return;
	}

	while (!searchResults->isEmpty())
	{

		doubleIterator<user*> beginItB = searchResults->begin();
		doubleIterator<user*> endItB   = searchResults->end();

		int counter = 1;

		//display results
		cout<<"-----------------------------------------------------------------"<<endl;
		cout<<"Search Results:" << endl;
		
		for (doubleIterator<user*> it = beginItB; it != endItB; ++it)
		{
			cout << "User " << counter++ << ": " << (*(*it))->returnFullName() << endl;
		}
		cout<<"-----------------------------------------------------------------"<<endl<<endl;

	
		int choice;
		cout << "Please select a user to view the degree of separation: " << endl;
		cout << "Please enter a user, or 0 to return:"; cin >> choice;

		if (choice == 0)
		{
			delete searchResults;
			return;
		}
		if (choice <= counter)
		{
			try
			{
				cout << "The degree of separation is: " << degreeOfSeparation(currentUser, searchResults->get(choice-1), list) << endl << endl;
			}
			catch(logic_error const & e)
			{	cout << e.what() << endl << endl;	}

			char dump;
			cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');	
			return;
		}

		else
		{
			char dump;
			cout << "Error: Invalid input" << endl;
			cout << "Enter any key to continue: "; cin >> dump; cout << endl;
			cin.ignore(256,'\n');
		}
	}		

	cout << "---No More Results---" << endl;
	char dump;
	cout << "Enter any key to return to the main menu"; cin >> dump; cin.ignore(256,'\n');	
}

//Account menu for when the user logs in
void accountMenu(userList *list, string userName)
{
		//Get current user
		user *currentUser = list->returnUser(userName);

		string name = currentUser->returnFullName();

		//Default sorting method: By latest creation time;
		currentUser->sortingMethod = compareByActivity_Greater;
		currentUser->isMax = true;
		//store old user's data for overwriting when logging out
		//user oldUserData = list->returnUser(fName, lName, password);

		char dump;

		string choice;
		bool menuLoop = true;

		while (menuLoop == true)
		{
				cout<<left;
				cout<<"Current User: "<<name<<endl;
				cout<<"*---------------------------------------------------------*"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|               Welcome to your Account!                  |"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Please select an action to perform:"                                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" YOUR ACCOUNT"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" ------------"                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 1) View your account information"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 1) Edit your account information"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" YOUR WALL"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" ---------"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 3) View your wall"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 4) Create a new post"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 5) Delete a post"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" FRIEND NETWORK"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" --------------"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 6) Search for a user by name"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 7) Search for a user by account username"                                                                                               <<"|"<<endl;				
				cout<<"|"<<setw(57)<<" 8) View your friend network"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 9) View pending friend requests"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 10) Seach degree of separation"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                <<"|"<<endl;            
				cout<<"|"<<setw(57)<<" OPTIONS"                                                                                                <<"|"<<endl;            
				cout<<"|"<<setw(57)<<" -------"                                                                                                <<"|"<<endl;            
				cout<<"|"<<setw(57)<<" 11) Change post viewing options"                                                                                                <<"|"<<endl;            
				cout<<"|"<<setw(57)<<" "                                                                                                <<"|"<<endl;            
				cout<<"|"<<setw(57)<<" Enter \"Logout\" to return to the menu"                                                  <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Please make sure that all your actions follow"                                   <<"|"<<endl;
				cout<<"|"<<setw(57)<<" the terms and conditions of Sherbook"                                                    <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;
				
				while (true)
				{
					try
					{

						cout<<"Input: ";cin>>choice;

						if (choice == "3")
						{
							viewPosts(currentUser, currentUser, list, true);
							//cout<<endl<<"Enter any key to return to the account menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;

							break;
						}
						else if (choice == "1")
						{
							cout<<endl;
							currentUser->printUserInfo();
							cout<<endl<<"Enter any key to return to the account menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
								break;
						}
						else if (choice == "2")
						{
							editInformation(currentUser);
							break;
						}       
						else if (choice == "4")
						{
							wallPost* newPost = createPost(currentUser);
							//Add the post to the user's wall
							currentUser->addPost(newPost, true);
							break;
						}       
						else if (choice == "5")
						{
							deletePost(currentUser, currentUser, true);
							break;
						}
						else if (choice == "6")
						{
							searchUserByName(currentUser, list);
							break;
						}               
						else if (choice == "7")
						{
							try
							{
								searchUserByUsername(currentUser, list);
							}
							catch(logic_error const & e)
							{	
								cout << e.what() << endl;	
								cout << endl << "---Request Successfully Sent---" << endl << endl;
								cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256,'\n'); cout << endl;
							}
							break;
						}         
						else if (choice == "8")
						{
							viewNetwork(currentUser, list);
							break;
						}                        
						else if (choice == "9")
						{
							pendingRequests(currentUser, list);
							break;
						}
						else if (choice == "11")
						{
							changeSortingMethod(currentUser);
							break;
						}
						else if (choice == "10")
						{
							findDegree(currentUser, list);
							break;
						}
						else if (checkCancel(choice))
						{
							menuLoop = false;
							break;
						}
						else
						{
							cout<<endl<<"Error: invalid input"<<endl<<endl;
							cin.ignore(256,'\n');
						}
					}
					catch(logic_error const &e)
					{
						cout << e.what() << endl;
						char dump;
						cout << "Enter any key to continue: "; cin >> dump; cout << endl; cin.ignore(256, '\n');
					}

				}

		}

		cout<<"---Logout Successful---"<<endl<<endl;
}

void displayAllUsers(userList *list)
{
		list->printAllUsers();
}

void deleteUser(userList *list)
{
		string toDelete;

		displayAllUsers(list);

		cout<<"Please enter the username of the user to delete"<<endl;
		cout<<"Or enter 'Q' to go back to the menu: "<<endl;
		cout<<"Delete user ";cin>>toDelete;cout<<endl;

		if (toDelete == "Q" || toDelete == "q")
		{
				return;
		}

		bool exist = list->containsUser(toDelete);

		if (exist)
		{
			list->removeUser(list->getUserPtr(toDelete));
		}
		else
		{
			cout << "Error: Username does not exist" << endl;
			return;
		}

		cout<<"---User "<<toDelete<<" Sucessfully Deleted---"<<endl;

		return;
}

//For fun only
void cookies()
{

						cout<<"   ___  _____  _____  _  _  ____  ____  ___  /  "<<endl;
						cout<<"  / __)(  _  )(  _  )( )/ )(_  _)( ___)/ __) )( "<<endl;
						cout<<" ( (__  )(_)(  )(_)(  )  (  _)(_  )__)  __    / "<<endl;
						cout<<"   ___)(_____)(_____)(_) _)(____)(____)(___/ () "<<endl;
						cout<<"                                        .-'''''-.        "<<endl;
						cout<<"                                |'-----'|        "<<endl;
						cout<<"                                |-.....-|        "<<endl;
						cout<<"                                |       |        "<<endl;
						cout<<"                                |       |        "<<endl;
						cout<<"               _,._             |       |        "<<endl;
						cout<<"          __.o`   o`.-.         |       |        "<<endl;
						cout<<"       .-O o `.-.o   O )_,._    |       |        "<<endl;
						cout<<"      ( o   O  o )--.-`O   o.-. `'-----'`        "<<endl;
						cout<<"      '--------'  (   o  O    o)                         "<<endl;
						cout<<"                    `----------`                         "<<endl;

						cout<<"Enjoy some cookies and milk!"<<endl;
						char dump;
						cout<<"Enter any key to finish your break";cin>>dump;cout<<endl;
						cin.ignore(256,'\n');
}

//Menu for admin
void adminMenu(userList *list)
{

		bool menuLoop = true;
		string choice;
		char dump;


		while (menuLoop)
		{

				cout<<left;
				cout<<"*---------------------------------------------------------*"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|                 Administration Menu                     |"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" This is the administration menu"                                                                 <<"|"<<endl;
				cout<<"|"<<setw(57)<<" You can access and modify information for the "                                  <<"|"<<endl;
				cout<<"|"<<setw(57)<<" entire Sherbook"                                                                                                 <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Please don't abuse this power"                                                                   <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Please select an action to perform:"                                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 1) View all users"                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 2) Delete a user"                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 3) Cookies...?"                                                                                                  <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Enter \"Q\" to Quit and return to main menu"                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;

				while (true)
				{
						cout<<"Input: ";cin>>choice;

						if (choice == "1")
						{
								cout<<endl;
								displayAllUsers(list); cout<<endl<<"Enter any key to return to the admin menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
								break;
						}
						else if (choice == "2")
						{
								cout<<endl;
								deleteUser(list); cout<<endl<<"Enter any key to return to the admin menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
								break;
						}
						else if (choice == "3")
						{
								cookies();
								break;
						}       

						else if (choice == "Q" || choice == "q" ||
										 choice == "Quit" || choice == "QUIT" || choice == "quit")
						{
								menuLoop = false;
								return;
						}

						else
						{
								cout<<endl<<"Error: invalid input"<<endl<<endl;
								cin.ignore(256,'\n');
						}

				}
		}
}

void recoverUsername(userList* list)
{
	bool isUser = false;

	string fName, lName, password, DOB, securityA;

	cout << "-----------------------------------------------------------------" << endl << endl;
	cout << "Enter \"Back\" anytime to return to the main menu" << endl;
	cout << "Please confirm the following information: " << endl;
	cout << "First name: "; cin >> fName; if (checkCancel(fName)) return;
	cout << "Last name:  "; cin >> lName; if (checkCancel(lName)) return;

	string name = constructName(fName, lName);

	//search for the user with the corresponding name:
	user* u;
	vector<user*>* vec = list->returnVector();
	for (int i = 0; i < vec->size(); ++i)
	{
		if (vec->at(i) == NULL)
			{	}	//do nothing
		else if ((vec->at(i))->returnFullName() == name)
		{
			u = vec->at(i);
			isUser = true;
			break;
		}
	}

	if (!isUser)
	{
		cout << "Sorry, there is no user that goes by the name \"" << fName << "\"" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	cout << "Date of birth: " << endl;
	cout << "Format: \"MM/DD/YYYY\" parenthesis included: "; cin >> DOB;
	if (u->returnUserInfoInt(2) != DOB)
	{
		cout << "Sorry, the information you provided does not match the records" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	cout << endl << "---Correct!---" << endl << endl;

	cout << "Please answer your security question: " << endl;
	cout << u->getSecurityQ() << endl;
	cout << "Answer: ";
	getline(cin, securityA);
	getline(cin, securityA);

	if (u->getSecurityA() != securityA)
	{
		cout << "Sorry, the information you provided does not match the records" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	cout << endl << "---Correct!---" << endl << endl;

	cout << "Finally, please confirm your password" << endl;
	cout << "Make sure that no one around you can spy or peek at your screen" << endl;
	cout << "Password: "; cin >> password; cout << endl;

	password = encrypt(password);

	if (u->returnUserInfoInt(3) != password)
	{
		cout << "Sorry, the information you provided does not match the records" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	//passed all the test!
	cout << "-----------------------------------------------------------------" << endl << endl;

	cout << "Recovery successful!" << endl;
	cout << "Your username is: " << u->returnUsername() << endl;

	char dump;
	cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
	return;	

}

void recoverPassword(userList* list)
{
	bool isUser = false;

	string fName, lName, uName, DOB, securityA;

	cout << "-----------------------------------------------------------------" << endl << endl;
	cout << "Enter \"Back\" anytime to return to the main menu" << endl;
	cout << "Please confirm the following information: " << endl;
	cout << "First name: "; cin >> fName; if (checkCancel(fName)) return;
	cout << "Last name:  "; cin >> lName; if (checkCancel(lName)) return;

	string name = constructName(fName, lName);

	//search for the user with the corresponding name:
	user* u;
	vector<user*>* vec = list->returnVector();
	for (int i = 0; i < vec->size(); ++i)
	{
		if (vec->at(i) == NULL)
			{	}	//do nothing
		else if ((vec->at(i))->returnFullName() == name)
		{
			cout << "marker" << endl;
			u = vec->at(i);
			isUser = true;
			break;
		}
	}

	if (!isUser)
	{
		cout << "Sorry, there is no user that goes by the name \"" << fName << "\"" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	cout << "Date of birth: " << endl;
	cout << "Format: \"MM/DD/YYYY\" parenthesis included: "; cin >> DOB;
	if (u->returnUserInfoInt(2) != DOB)
	{
		cout << "Sorry, the information you provided does not match the records" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	cout << endl << "---Correct!---" << endl << endl;	

	cout << "Please answer your security question: " << endl;
	cout << u->getSecurityQ() << endl;
	cout << "Answer: ";
	getline(cin, securityA);
	getline(cin, securityA);

	if (u->getSecurityA() != securityA)
	{
		cout << "Sorry, the information you provided does not match the records" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	cout << endl << "---Correct!---" << endl << endl;

	cout << "Finally, please enter your username" << endl;
	cout << "Make sure that no one around you can spy or peek at your screen" << endl;
	cout << "Username: "; cin >> uName; cout << endl;

	if (u->returnUsername() != uName)
	{
		cout << "Sorry, the information you provided does not match the records" << endl;
		cout << "Please check the name you entered, or if you're new, make an account!" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		char dump;
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		return;
	}

	//passed all the test!
	cout << "-----------------------------------------------------------------" << endl << endl;

	cout << "Recovery successful!" << endl;

	cout << "Please make sure that no one is around to peek or spy at your new password" << endl;
	
	char dump;
	cout << "Enter any key to begin: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;

	string password1;
	string password2;

	while (true)
	{
		cout << "  Please enter your new password: "; cin >> password1; cout << endl;
		cout << "Please confirm your new password: "; cin >> password2; cout << endl;

		if (password1 == password2)
			break;
		else
		{
			cout << "Error: Passwords don't match. Please try again" << endl;
		}
		cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;

	}

	password1 = encrypt(password1);

	u->setUserInfo(password1, 3);

	cout << "---Password Successfully Reset---" << endl;

	cout << "Enter any key to begin: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;


	return;	
}

void remind(userList *list)
{
	while (true)
	{
		cout << "-------------------" << endl;
		cout << "| Remind Password |" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;
		cout << "Forgot your password? No worries, eveyone does that every now and then" << endl;
		cout << "Just follow these easy steps to recover your forgotten information:" << endl;
		cout << "Please select an option: " << endl;
		cout << "1) I forgot my username" << endl;
		cout << "2) I forgot my password (reset password)" << endl;
		cout << "Q) Quit" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		string choice;
		cout << "Selection: "; cin >> choice; cout << endl;
		if (choice == "q" || choice == "Q" || choice == "Quit" || choice == "QUIT" || choice == "quit")
			return;

		if (choice == "1")
		{
			recoverUsername(list);
			return;
		}
		else if (choice == "2")
		{
			recoverPassword(list);
			return;
		}
		else
		{
			cout << "Error: Invalid input" << endl;
			char dump;
			cout << "Enter any key to continue: "; cin >> dump; cin.ignore(256, '\n'); cout << endl;
		}
	}
	

	return;
}

//Login function
void logIn(userList *list)
{

		bool isBack = false;

		bool isAdmin = false;

		bool isUser = false;

		string uName;
		string password;

		char dump;

		while (true) //loop allows user to have multiple attempts to login
		{
				cout<<"----------"<<endl;
				cout<<"| Log In |"<<endl;
				cout<<"-----------------------------------------------------------------"<<endl<<endl;
				cout<<"Type \"EXIT\" or \"BACK\" anytime to return to the menu"<<endl;
				cout<<"Forgot your username or password? No worries, type \"Reminder\" to begin the reminder process" << endl;
				cout<<" "<<endl;                                                                           //Checks if user wants to return back to menu or start reminder process
				cout<<"Username: ";cin>>uName;                                                              
					if (checkCancel(uName))
						return;
					if (uName == "Reminder" || uName == "reminder" || uName == "REMINDER")
					{
						remind(list);
						return;
					}

				cout<<"Password: ";cin>>password;
					if (checkCancel(password))
						return;
					if (password == "Reminder" || password == "reminder" || password == "REMINDER")
					{
						remind(list);
						return;
					}

				//check if user exists
				isUser = list->containsUser(uName);

				//checks for admin login
				if (uName == "admin" || uName == "Admin" || uName == "ADMIN" ||
						password == "admin" || password == "Admin" || password == "ADMIN")
				{
						adminMenu(list);

						return;
				}

				if (isUser == true)
				{

					//get the user
					user* loginUser = list->returnUser(uName);

					//now check for password

					//md5 the password
					password = encrypt(password);

					//password now holds the encrypted password
					if (password == loginUser->returnUserInfoInt(3))
					{
						//If user exists and password is correct, break from loop
						break;
					}


				}



				cout<<"-----------------------------------------------------------------"<<endl<<endl;

				cout<<"Error: Username and password do not match or user not found"<<endl;
				cout<<"       Please check you spelled the information correctly"<<endl;
				cout<<"       or return to the main menu and create a new account"<<endl<<endl;

				cout<<"Enter any key to continue: ";cin>>dump;cin.ignore(256,'\n');cout<<endl<<endl;

		}


		//If user wants to go back, return
		if (isBack == true) return;

		//If user is admin, go to admin menu
		cout<<endl<<"---Login Successful---"<<endl<<endl;
		cout<<"Enter any key to continue: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
		accountMenu(list, uName);

}

//For fun only
void termsAndConditions()
{
				cout<<"*---------------------------------------------------------*"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|                Terms and Conditions!                    |"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Profanities, assult, or other forms of"                                                  <<"|"<<endl;
				cout<<"|"<<setw(57)<<" harrassment are forbidden through post interactions"                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" No explicit material that may be offensive to others"                    <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" You will not user Sherbook to buy or sell animals"                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Mythical creatures such as dragons are also animals"                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Selling mythical creatures are also forbidden"                                   <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" By using Sherbook, you will be in constant pursuit"                              <<"|"<<endl;
				cout<<"|"<<setw(57)<<" for cookies"                                                                                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Most importantly: Have fun!"                                                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;

				char dump;
				cout<<"Enter any key to return to the menu: ";cin>>dump;cout<<endl;
				cin.ignore(256,'\n');
				return;
}


int main()
{
		//Make a user list. Constructor will initialize the list
		userList *list = new userList;
		//doubleSizeArray<string> userNames();

		char choice;
		bool choiceLoop;
		bool menuLoop = true;

		while (menuLoop == true)
		{
				choiceLoop = true;

				cout<<left;
				cout<<"*---------------------------------------------------------*"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|              Welcome to Sherbook v.1.2!                 |"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" This is a social network program created by"                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Stephen Tsung-Han Sher for CS104"                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" If you have already created an account, simply choose"                   <<"|"<<endl;
				cout<<"|"<<setw(57)<<" the login option and log in with your username"                                  <<"|"<<endl;
				cout<<"|"<<setw(57)<<" and password"                                                                                                    <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" If you are new, feel free to create an account!"                                 <<"|"<<endl;
				cout<<"|"<<setw(57)<<" It is completely free!"                                                                                  <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Donations in the form of good grades"                                                    <<"|"<<endl;
				cout<<"|"<<setw(57)<<" are always welcomed"                                                                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Please select an action to perform:"                                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 1) Log in"                                                                                                               <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 2) Create new account (FREE!)"                                                                   <<"|"<<endl;
				cout<<"|"<<setw(57)<<" 3) Read terms and conditions"                                                                    <<"|"<<endl;
				cout<<"|"<<setw(57)<<" Enter \"Q\" to Quit"                                                                                             <<"|"<<endl;
				cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
				cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;

				choiceLoop = true;
				while (choiceLoop == true)
				{
						cout<<"Input: ";cin>>choice;

						if (choice == '1')
						{
								logIn(list);
								choiceLoop = false;
						}
						else if (choice == '2')
						{
								createAccount(list);
								choiceLoop = false;
						}
						else if (choice == '3')
						{
								termsAndConditions();
								choiceLoop = false;
						}
						else if (choice == 'q' || choice == 'Q')
						{
								choiceLoop = false;
								menuLoop = false;
						}
						else
						{
								cin.ignore(256,'\n');
								cout<<endl<<"Error: Invalid input"<<endl<<endl;
						}
				}

		}

		//Destructor will output userlist into a text file
		delete list;

		cout<<"---Program End---"<<endl;
		return 0;
}