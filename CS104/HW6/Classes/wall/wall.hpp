#include <iostream>
#include <fstream>
#include <string>
using namespace std;

wall::wall()
{
	//call constructor: make an array of size 10 of wallPosts.
	//empty for now
	arrayPtr = new doubleSizeArray<wallPost>;
	numOfPosts = 0;
}

//destructor: writes on the file
wall::~wall()
{
	//Makes a temp post to write with
	wallPost tempPost;
	int counter = 0;

	int size = arrayPtr->returnNumOfElements();

	ofstream fout;

	fout.open("user_info_file.txt", ios::app);

	for (counter = 0; counter < size; ++counter)
	{
		tempPost = arrayPtr->get(counter);
		fout << tempPost.returnAuthor() << endl;
		fout << tempPost.returnPost() << endl;
	}

	fout.close();


}

void wall::addPost(wallPost newPost)
{
	//cout<<"Adding post"<<endl;

	arrayPtr->insert(numOfPosts, newPost);
	numOfPosts++;
}

wallPost wall::returnPostByIndex(int index)
{
	wallPost temp = arrayPtr->get(index);
	return temp;
}



void wall::removePostByIndex(int index)
{
	arrayPtr->remove(index);
}



void wall::printAllPosts() const
{
	int tempCounter = 1;

	doubleIterator<wallPost> beginIt = arrayPtr->begin();
	doubleIterator<wallPost> endIt = arrayPtr->end();

	for (doubleIterator<wallPost> it = beginIt; it != endIt; ++it)
	{
		(*it)->printPost(tempCounter++);
	}

}


