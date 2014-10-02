#ifndef LListSet_H_
#define LListSet_H_

#include "../Element/LListElement.h"

using namespace std;

template <class dataType>
class LListSet
{
	public:
		LListSet();
		~LListSet();

		void add (const dataType &x);

		void removePtr(LListElement<dataType> *p);
		void remove (dataType x);

		bool contains (const dataType &x);
		void print() const;

		dataType* convertToArray();
		int returnSize();

	private:
		LListElement<dataType> *start, *end;

};


#include "LListSet.hpp"

#endif //LListSet_H_

