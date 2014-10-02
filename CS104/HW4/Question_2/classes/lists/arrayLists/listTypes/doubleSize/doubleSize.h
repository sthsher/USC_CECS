#ifndef doubleSize_H_
#define doubleSize_H_


using namespace std;

template <class dataType>
class doubleSize : public abstractArray<dataType>
{
	public:
		doubleSize();
		doubleSize(int initial);
		virtual ~doubleSize();

		int returnSize();
		int returnNumOfElements();

	protected:
		virtual void extendArray();
			/* Extends the array */
};

#include "doubleSize.hpp"

#endif //doubleSize_H_