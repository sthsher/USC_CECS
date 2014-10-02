#ifndef abstractArray_H_
#define abstractArray_H_

using namespace std;

template <class dataType>
class abstractArray: public pureList<dataType>
{
	public:

		abstractArray();
		abstractArray(dataType initial);

		virtual ~abstractArray();

		virtual void insert (int pos, const dataType & item);
	
		virtual void remove (int pos);

		virtual void set (int pos, const dataType & item);

		virtual dataType const & get (int pos) const;


		virtual void printElement(int pos) const;

		virtual void printArray() const;

	protected:
		dataType* arrayPtr;
		int size;
		int numOfElements;

		virtual void extendArray() = 0;
			/* Extends the array */
 	
};

#include "abstractArray.hpp"

#endif //abstractArray_H_