#ifndef sherStack_H_
#define sherStack_H_

#include "Element/LListElement.h"
#include <stdexcept>

using namespace std;

template <class T>
class sherStack
{

public:

	sherStack();

	T top() const;					//returns top item
	void pop(); 					//deletes top item
	void push(const T &item);		//adds item to stack

private:
	LListElement<T> *start, *end;


};

#include "sherStack.hpp"



#endif //sherStack_H_