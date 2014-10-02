#ifndef pureList_H_
#define pureList_H_

using namespace std;

template <class dataType>
class pureList
{
	public:

		//list();
		virtual ~pureList();

		virtual void insert (int pos, const dataType & item) = 0;
			/* Inserts the item right before position pos, growing the list by 1.
			pos must be between 0 and the current length of the list.
			(The textbook returns a bool - feel free to do that.) */
		virtual void remove (int pos) = 0;
			/* Removes the element at position pos, shrinking the list by 1.
			pos must be between 0 and the current length of the list minus 1. */
		virtual void set (int pos, const dataType & item) = 0;
			/* overwrites position pos in the list with item.
			Does not change the length of the list.
			pos must be between 0 and the current length of the list minus 1. */
		virtual dataType const & get (int pos) const = 0;
			/* returns the item at position pos, not changing the list.
			pos must be between 0 and the current length of the list minus 1. */

		virtual void printElement(int pos) const = 0;

		virtual void printArray() const = 0;


		//For Debugging purposes
		/*
		int pureSize;
		int pureNumOfElements;
		int returnSize();
		int returnNumOfElements();
		*/
};

#include "pureList.hpp"

#endif //pureList_H_