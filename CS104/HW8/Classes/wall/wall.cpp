#include <iostream>
#include <fstream>
#include <string>
#include "wall.h"
using namespace std;

wall::wall()
{
	//call constructor: make an array of size 10 of wallPosts.
	//empty for now
	arrayPtr = new doubleSizeArray<wallPost*>;
	numOfPosts = 0;
}

//destructor: writes on the file
wall::~wall()
{
	//Makes a temp post to write with
	wallPost* tempPost = new wallPost;
	int counter = 0;

	int size = arrayPtr->returnNumOfElements();

	ofstream fout;

	fout.open("user_info_file.txt", ios::app);

	for (counter = 0; counter < size; ++counter)
	{
		tempPost = arrayPtr->get(counter);
		fout << tempPost->returnAuthorID() << " ";
		fout << tempPost->returnNumOfComments() << " ";
		fout << tempPost->returnCreationTime() << endl;
		fout << tempPost->returnPost() << endl;

		for (int i = 0; i < tempPost->returnNumOfComments(); ++i)
		{
			//write comments
			postComment* tempComment = tempPost->returnCommentByIndex(i);
			fout << tempComment->returnAuthorID() << " ";
			fout << tempComment->returnCreationTime() << endl;
			fout << tempComment->returnComment() << endl;
		}

	}

	delete arrayPtr;

	fout.close();


}

void wall::addPost(wallPost* newPost)
{
	//cout<<"Adding post"<<endl;

	arrayPtr->insert(numOfPosts++, newPost);
	newPost->setPostID(numOfPosts);
}

wallPost* wall::returnPostByIndex(int index)
{
	wallPost* temp = arrayPtr->get(index);
	return temp;
}



void wall::removePostByIndex(int index)
{
	arrayPtr->remove(index);
}

int wall::returnNumOfPosts()
{
	return numOfPosts;
}


void wall::printAllPosts(bool(*compareFunction)(wallPost*, wallPost*), bool isMax) const
{
	heap<wallPost*> priorityQ(2, isMax);



	doubleIterator<wallPost*> beginIt = arrayPtr->begin();
	doubleIterator<wallPost*> endIt = arrayPtr->end();

	for (doubleIterator<wallPost*> it = beginIt; it != endIt; ++it)
	{
		//(*(*it))->printPost(tempCounter++);
		//Add all the wallPosts into the priorityQ
		priorityQ.add((*(*it)), compareFunction);
	}

	//output all the posts
	for (int i = 0; i < numOfPosts; ++i)
	{
		(priorityQ.peek())->printPost();
		priorityQ.remove(compareFunction);
	}
	


}


