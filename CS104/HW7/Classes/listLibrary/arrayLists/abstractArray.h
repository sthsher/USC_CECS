#ifndef abstractArray_H_
#define abstractArray_H_

using namespace std;

template <class T>
class abstractArray: public pureList<T>
{
	public:

		abstractArray();
		abstractArray(T initial);

		virtual ~abstractArray();

		virtual void insert (int pos, const T & item);
	
		virtual void remove (int pos);

		virtual void set (int pos, const T & item);

		virtual T const & get (int pos) const;


		//virtual void printElement(int pos) const;

		//virtual void printArray() const;

	protected:
		T* arrayPtr;
		int size;
		int numOfElements;

		virtual void extendArray() = 0;
			/* Extends the array */
 	
};

#include "abstractArray.hpp"

#endif //abstractArray_H_