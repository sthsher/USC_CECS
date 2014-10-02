#ifndef STRINGLL_H_
#define STRINGLL_H_

#include <iostream>
#include <string>
using namespace std;
class stringLL
{
	public:
		stringLL();
		~stringLL();

		void setData(string s);
		void setNext(stringLL *n);

		string returnData();
		stringLL *returnNext();


	private:
		string data;
		stringLL *next;

};

#endif //STRINGLL_H_