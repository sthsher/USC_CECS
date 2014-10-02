#include "classes/lists/pureList.h"
#include "classes/lists/arrayLists/abstractArray.h"
#include "classes/lists/arrayLists/listTypes/addOne/addOne.h"
#include "classes/lists/arrayLists/listTypes/doubleSize/doubleSize.h"
#include "classes/lists/arrayLists/listTypes/addTenPercent/addTenPercent.h"
#include "classes/lists/LinkedLists/LLList.h"

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	//Clock stuff
	const int ITERATE = 10;
	clock_t start, finish;
	double dur;

	//declare pointer of the pure class to use
	pureList<int> *tempList;

	cout<<"------------------------"<<endl;
	cout<<"     Add One Array"<<endl;
	cout<<"------------------------"<<endl;

	int numOInsertions = 50000;

		start = clock();
		for (int i = 0; i < ITERATE; i++)
		{
			//use addOne system
			tempList = new addOne<int>(10);

			for (int i = 0 ; i < numOInsertions; i++)
			{
				//i/2 to insert in the middle of the list
				tempList->insert(i/2, 5);
			}

			delete tempList;
		}
		finish = clock();

		dur  = (double)(finish - start);
		dur /= (CLOCKS_PER_SEC * ITERATE);
		cout << "The time elapsed in seconds for "<< numOInsertions << " insertions is:  " << dur << endl;


	//below there are the same implementation as above, just with different systems of arrays

	cout<<"------------------------"<<endl;
	cout<<"   Double Size Array"<<endl;
	cout<<"------------------------"<<endl;

	numOInsertions = 50000;

		start = clock();
		for (int i = 0; i < ITERATE; i++)
		{
			tempList = new doubleSize<int>(10);

			for (int i = 0 ; i < numOInsertions; i++)
			{
				tempList->insert(i/2, 5);
			}

			delete tempList;
		}
		finish = clock();

		dur  = (double)(finish - start);
		dur /= (CLOCKS_PER_SEC * ITERATE);
		cout << "The time elapsed in seconds for "<< numOInsertions << " insertions is:  " << dur << endl;


	cout<<"------------------------"<<endl;
	cout<<"  Add 10 Percent Array"<<endl;
	cout<<"------------------------"<<endl;

	numOInsertions = 50000;

		start = clock();
		for (int i = 0; i < ITERATE; i++)
		{
			tempList = new addTenPercent<int>(10);

			for (int i = 0 ; i < numOInsertions; i++)
			{
				tempList->insert(i/2, 5);
			}

			delete tempList;
		}
		finish = clock();

		dur  = (double)(finish - start);
		dur /= (CLOCKS_PER_SEC * ITERATE);
		cout << "The time elapsed in seconds for "<< numOInsertions << " insertions is:  " << dur << endl;


	cout<<"------------------------"<<endl;
	cout<<"    Linked List"<<endl;
	cout<<"------------------------"<<endl;

	numOInsertions = 50000;
		start = clock();
		for (int i = 0; i < ITERATE; i++)
		{
			tempList = new LLList<int>;

			for (int i = 0 ; i < numOInsertions; i++)
			{
				tempList->insert(i/2, 5);
			}

			delete tempList;
		}
		finish = clock();

		dur  = (double)(finish - start);
		dur /= (CLOCKS_PER_SEC * ITERATE);
		cout << "The time elapsed in seconds for "<< numOInsertions << " insertions is:  " << dur << endl;



	cout << endl << "---Program End---" << endl;

	return 0;


}