#ifndef wall_H_
#define wall_H_

#include "../listLibrary/arrayLists/doubleSizeArray.h"
#include "../wallPost/wallPost.h"
#include "../heap/heap.h"

using namespace std;


class wall
{
	public:
		wall();
		~wall();

		void addPost(wallPost* newPost);				//adds a new post with class wallPost
		wallPost* returnPostByIndex(int index);		//returns post by index
		void removePostByIndex(int index);			//removes post by index

		int returnNumOfPosts();

		void printAllPosts(bool(*compareFunction)(wallPost*, wallPost*), bool isMax) const;

	private:
		doubleSizeArray<wallPost*> *arrayPtr;
		int numOfPosts;

		//Iterator stuff
		//wallPost* returnStartPtr();

};

#endif //wall_H_