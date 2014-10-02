#include <iostream>
#include "postComment.h"
using namespace std;

postComment::postComment()
{
	author = "";
	comment = "";
	creationTime_raw = time(0);
	creationTime_string = ctime(&creationTime_raw);
}

postComment::~postComment()
{

}

void postComment::setAuthor(const string &a)
{
	author = a;
}

void postComment::setComment(const string &p)
{
	comment = p;
}

void postComment::setAuthorID(const int &n)
{
	authorID = n;
}

string postComment::returnAuthor()
{
	return author;
}

string postComment::returnComment()
{
	return comment;
}

int postComment::returnAuthorID()
{
	return authorID;
}

void postComment::printComment(int postNum) const
{

	cout<<"--------------------------------------------------"<<endl;
	cout<<"Comment "<<postNum<<endl;
	cout<<"Comment Created By:  "<<author<<endl;
	cout<<"Created on:          " << creationTime_string << endl;
	cout<<comment<<endl;
	cout<<"--------------------------------------------------"<<endl;

	return;
}

//time functions

void postComment::setCreationTime(int n)
{
	creationTime_raw = n;
	creationTime_string = ctime(&creationTime_raw);
}
time_t postComment::returnCreationTime()
{
	return creationTime_raw;
}
