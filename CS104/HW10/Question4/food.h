#ifndef food_H_
#define food_H_

#include <string>

using namespace std;

class food
{
	public:
		
		food();
		food(string c);
		~food();

		int const hash() const;
		string content;

		bool operator==(const food & other);

};

#endif //food_H_