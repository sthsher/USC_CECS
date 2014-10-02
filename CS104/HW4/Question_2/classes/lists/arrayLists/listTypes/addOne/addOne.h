#ifndef addOne_H_
#define addOne_H_


using namespace std;

template <class dataType>
class addOne : public abstractArray<dataType>
{
	public:
		addOne();
		addOne(dataType initial);
		virtual ~addOne();

		int returnSize();
		int returnNumOfElements();

	protected:
		virtual void extendArray();
			/* Extends the array */
};

#include "addOne.hpp"

#endif //addOne_H_