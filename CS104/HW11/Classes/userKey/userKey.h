#ifndef userKey_H_
#define userKey_H_

using namespace std;

class userKey
{
	public:
		userKey();
		userKey(string s);
		~userKey();

		string content;

		int hash();

		bool operator== (userKey const & other);
		bool operator!= (userKey const & other);


};

#endif //userKey_H_