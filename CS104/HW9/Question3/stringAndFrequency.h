#ifndef stringAndFrequency_H_
#define stringAndFrequency_H_

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class stringAndFrequency
{
	public:
		stringAndFrequency();
		stringAndFrequency(string s);
		stringAndFrequency(string s, int f);

		~stringAndFrequency();

		void incrementFrequency();
		void setContent(string s);
		string getContent() const;
		int getFrequency();

	private:
		string content;
		int frequency;



};

#endif //stringAndFrequency_H_