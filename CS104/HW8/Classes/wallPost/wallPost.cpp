#include <iostream>
#include "wallPost.h"
using namespace std;

wallPost::wallPost()
{
	author = "";
	post = "";
	arrayPtr = new doubleSizeArray<postComment*>;
	numOfComments = 0;

	creationTime_raw = time(0);
	creationTime_string = ctime(&creationTime_raw);

	latest_raw = creationTime_raw;
	latest_string = creationTime_string;
}

wallPost::~wallPost()
{

}

void wallPost::setPostID(const int &n)
{
	postID = n;
}
int wallPost::returnPostID()
{
	return postID;
}

void wallPost::setAuthor(const string &a)
{
	author = a;
}

void wallPost::setPost(const string &p)
{
	post = p;
}

void wallPost::setAuthorID(const int &n)
{
	authorID = n;
}

string wallPost::returnAuthor()
{
	return author;
}

string wallPost::returnPost()
{
	return post;
}

int wallPost::returnAuthorID()
{
	return authorID;
}

void wallPost::printPost() const
{

	cout << "--------------------------------------------------" << endl;
	cout << "Post " << postID << endl;
	cout << "Post Created By: " << author << endl;
	cout << "Created On:      " << creationTime_string;
	cout << "Latest Activity: " << latest_string;
	cout << "Number of Comments: " << numOfComments << endl << endl;
	cout << post<<endl;
	cout << "--------------------------------------------------"<<endl;

	return;

}

//Comment functions

void wallPost::setNumOfComments(const int &n)
{
	numOfComments = n;
}


int wallPost::returnNumOfComments()
{
	return numOfComments;
}


void wallPost::printAllComments() const
{
	if (numOfComments == 0)
	{
		cout << "There are currently no comments" << endl;
		return;
	}
	int tempCounter = 1;

	doubleIterator<postComment*> beginIt = arrayPtr->begin();
	doubleIterator<postComment*> endIt = arrayPtr->end();

	for (doubleIterator<postComment*> it = beginIt; it != endIt; ++it)
	{
		(*(*it))->printComment(tempCounter++);
	}
}

void wallPost::addComment(postComment* newComment, bool increment)
{
	arrayPtr->insert(numOfComments, newComment);

	if (increment)
		numOfComments++;

	//update time to latest time
	if (latest_raw < newComment->returnCreationTime())
	{
		latest_raw = newComment->returnCreationTime();
		latest_string = ctime(&latest_raw);
	}
}

postComment* wallPost::returnCommentByIndex(const int & index)
{
	postComment* temp = arrayPtr->get(index);
	return temp;
}

void wallPost::removeCommentByIndex(const int & index)
{
	arrayPtr->remove(index);
}

//Time Functions

void wallPost::setCreationTime(int n)
{
	creationTime_raw = n;
	creationTime_string = ctime(&creationTime_raw);

	//at creation, the latest activity time is the same as creation

	latest_raw = n;
	latest_string = ctime(&latest_raw);
}
void wallPost::setLatestTime(int n)
{
	latest_raw = n;
	latest_string = ctime(&latest_raw);
}
time_t wallPost::returnCreationTime()
{
	return creationTime_raw;
}
time_t wallPost::returnLatestTime()
{
	return latest_raw;
}
