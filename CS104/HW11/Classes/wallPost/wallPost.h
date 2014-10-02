#ifndef wallPost_H_
#define wallPost_H_

#include "../listLibrary/arrayLists/doubleSizeArray.h"
#include "../postComment/postComment.h"
#include "../heap/heap.h"

using namespace std;

class wallPost
{
	public:
		wallPost();
		~wallPost();

		void setPostID(const int &n);
		int returnPostID();

		void setAuthor(const string &a);			//sets the author
		void setPost(const string &p);				//sets the post
		void setAuthorID(const int &n);

		string returnAuthor();
		string returnPost();
		int returnAuthorID();

		void printPost() const;		

		//comment functions
		void printAllComments() const;
		void addComment(postComment* newComment, bool increment);
		postComment* returnCommentByIndex(const int & index);
		void removeCommentByIndex(const int & index);

		void setNumOfComments(const int &n);
		int returnNumOfComments();

		//time functions
		void setCreationTime(int n);
		void setLatestTime(int n);
		time_t returnCreationTime();
		time_t returnLatestTime();

	private:
		int postID;
		doubleSizeArray<postComment*> *arrayPtr;
		int numOfComments;
		
		string author;
		int authorID;
		string post;

		//Timestamp
		time_t creationTime_raw;
		string creationTime_string;

		time_t latest_raw;
		string latest_string;

};

#endif //wallPost_H_