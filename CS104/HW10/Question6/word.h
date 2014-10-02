#ifndef word_H_
#define word_H_

#include <string>

using namespace std;

class word
{
	public:
		
		word();
		word(string c);
		~word();

		int const hash() const;
		string content;

		bool operator==(const word & other);

};

#endif //word_H_