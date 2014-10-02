#ifndef postComment_H_
#define postComment_H_

using namespace std;

class postComment
{
	public:
		postComment();
		~postComment();

		void setAuthor(const string &a);			//sets the author
		void setComment(const string &p);				//sets the comment
		void setAuthorID(const int &n);

		string returnAuthor();
		string returnComment();
		int returnAuthorID();

		void printComment(int commentNum) const;		//commentNum is just a temporary integer to show the progression of comments.

		//time functions
		void setCreationTime(int n);
		time_t returnCreationTime();


	private:
		string author;
		int authorID;
		string comment;

		//Timestamp
		time_t creationTime_raw;
		string creationTime_string;


};

#endif //postComment_H_