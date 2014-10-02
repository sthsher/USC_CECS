#ifndef student_H_
#define student_H_

#include <string>

using namespace std;

class student
{
	public:
		
		student();
		student(string c);
		~student();

		int const hash() const;
		string content;

		bool operator==(const student & other);

};

#endif //student_H_