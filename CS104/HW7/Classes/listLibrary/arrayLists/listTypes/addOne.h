#ifndef addOne_H_
#define addOne_H_


using namespace std;

template <class T>
class addOne : public abstractArray<T>
{
	public:
		addOne();
		addOne(T initial);
		virtual ~addOne();

		int returnSize();
		int returnNumOfElements();

	protected:
		virtual void extendArray();
			/* Extends the array */
};

#include "addOne.hpp"

#endif //addOne_H_