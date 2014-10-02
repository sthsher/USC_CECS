#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>

#include "Classes/heap.h"

using namespace std;

int main()
{
	cout << "---Program Start---" << endl;

	//Clock stuff
	const int ITERATE = 10;
	clock_t start, finish;
	double dur;

	//Random number generator
	int randomNum;
	srand(time(NULL));                          //automatically                     *
	randomNum = rand()%10000;                 	//Random number from 0 to 9          *

// ************************************************************
				//Insertion Test
// ************************************************************

	//start the clock
	start = clock();
	for (int i = 0; i < ITERATE; ++i)
	{
		//for 2-ary
		heap<int> priorityQTwo(2, true);

		//repeat process for 10000 numbers
		for (int j = 0; j < 10000; ++j)
		{
			//generate a random number
			randomNum = rand()%10000;
			//add it
			try
			{
				priorityQTwo.add(randomNum);
			}
			catch (logic_error const &e)
			{
				cout << e.what() << endl;
			}

		}
	}
	finish = clock();

	dur = (double)(finish - start);
	dur /= (CLOCKS_PER_SEC * ITERATE);
	cout << "Time elapsed in seconds for 10,000 insertions for a  2-ary tree is: " << dur << endl;

	//exact same process as above but for 10 to 90 in increments of 10
	for (int j = 10; j < 100; j = j+10)
	{
		//start the clock
		start = clock();
		for (int i = 0; i < ITERATE; ++i)
		{
			//for 2-ary
			heap<int> priorityQ(j, true);

			for (int j = 0; j < 10000; ++j)
			{
				//generate a random number
				randomNum = rand()%10000;
				//add it
				try
				{
					priorityQ.add(randomNum);
				}
				catch (logic_error const &e)
				{
					cout << e.what() << endl;
				}

			}
		}
		finish = clock();

		dur = (double)(finish - start);
		dur /= (CLOCKS_PER_SEC * ITERATE);
		cout << "Time elapsed in seconds for 10,000 insertions for a " << j << "-ary tree is: " << dur << endl;

	}


// ************************************************************
				//Removal Test
// ************************************************************

	dur = 0;

	//start the clock
	for (int i = 0; i < ITERATE; ++i)
	{
		//for 2-ary
		heap<int> priorityQTwo(2, true);

		for (int j = 0; j < 10000; ++j)
		{
			//generate a random number
			randomNum = rand()%10000;
			//add it
			try
			{
				priorityQTwo.add(randomNum);
			}
			catch (logic_error const &e)
			{
				cout << e.what() << endl;
			}

		}

		start = clock();
		for (int j = 0; j < 10000; ++j)
		{
			try
			{
				priorityQTwo.remove();
			}
			catch (logic_error const &e)
			{
				cout << e.what() << endl;
			}

		}
		finish = clock();

		double durOne = (finish - start);
		durOne /= (CLOCKS_PER_SEC);
		dur = (dur + durOne)/2;

	}

	cout << "Time elapsed in seconds for 10,000 deletions for a  2-ary tree is: " << dur << endl;

	for (int j = 10; j < 100; j = j+10)
	{
		for (int i = 0; i < ITERATE; ++i)
		{
			heap<int> priorityQ(j, true);

			for (int k = 0; k < 10000; ++k)
			{
				//generate a random number
				randomNum = rand()%10000;
				//add it
				try
				{
					priorityQ.add(randomNum);
				}
				catch (logic_error const &e)
				{
					cout << e.what() << endl;
				}
			}

			start = clock();
			for (int k = 0; k < 10000; ++k)
			{
				try
				{
					priorityQ.remove();
				}
				catch (logic_error const &e)
				{
					cout << e.what() << endl;
				}

			}
			finish = clock();

			double durOne = (finish - start);
			durOne /= (CLOCKS_PER_SEC);
			dur = (dur + durOne)/2;

			
			}
			cout << "Time elapsed in seconds for 10,000 deletions for a " << j << "-ary tree is: " << dur << endl;

	}


	cout << "--- Program End ---" << endl;
	return 0;
}