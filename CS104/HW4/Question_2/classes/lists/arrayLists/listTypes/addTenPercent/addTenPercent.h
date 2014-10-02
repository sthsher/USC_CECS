#ifndef addTenPercent_H_
#define addTenPercent_H_


using namespace std;

template <class dataType>
class addTenPercent : public abstractArray<dataType>
{
	public:
		addTenPercent();
		addTenPercent(int initial);
		virtual ~addTenPercent();

		int returnSize();
		int returnNumOfElements();

	protected:
		virtual void extendArray();
			/* Extends the array */
};

#include "addTenPercent.hpp"

#endif //addTenPercent_H_