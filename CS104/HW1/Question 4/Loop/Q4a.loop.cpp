#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int getArrSize(string &fileName)
{

	int size = 0;
	int temp;

	cout<<endl;
	cout<<"Please enter the name of the file containing the array"<<endl;
	cout<<"Be sure to include \".txt\" in the file name"<<endl<<endl;
	cout<<"File Name: "; cin>>fileName;

												//fileName = "test.txt";

	ifstream fin;

	fin.open(fileName.c_str());

	while (true)					//as long as the file is open
	{

		if (fin.eof())
		{

			fin.close();
			return size;
		}

		fin>>temp;					//temp not needed, just move cursor along
		size++;						//update size

	}

}

void fillArray(int *a, string fileName)
{
	ifstream fin;

	fin.open(fileName.c_str());

	while (true)
	{
		if (fin.eof())
		{
			fin.close();
			return;
		}

		fin >> *a;					//put number from file in the array, then move pointer to next slot
		a++;

	}

}





int main()
{

//******************************************************************************************************
//												Declarations
//												------------
	int *a;
	int *originalAdd;
	int n;  						// number of elements in the array a
    int sum = 0; 					// we’ll use this for adding numbers

    //Clock stuff
	const int ITERATE = 1000;
	clock_t start, finish;
	double  dur;

  	string fileName;



//******************************************************************************************************
//								Getting size, creating array, filling array
//								-------------------------------------------

    n = getArrSize(fileName);		//n now holds the number of elements in the file

	a = new int[n];					//a is now pointing at the array of size n
	originalAdd=a;					//originalAdd now holds the address of the beginning of the array

	fillArray(a, fileName);			//This function will fill the array with elements

	a = originalAdd;				//a point back to beginning

//******************************************************************************************************
//								Loop: summing the array
//								-----------------------

/*
	sum = 0;
	for (int i = 0; i < n; i ++)
	{
		sum += a[i];
	}
*/

	//Clock function

	start  = clock();
	for (int i = 0; i < ITERATE; i++)
	{
    	sum = 0;
    	for (int i = 0; i < n; i ++)
    	{
    	sum += a[i];
    	}	
	}
	finish = clock();

	dur   = (double)(finish - start);
	dur  /= (CLOCKS_PER_SEC * ITERATE);
	cout << "Elapsed seconds: "<< scientific << dur << endl;



	delete []a;

	cout<<"The sum is: "<<sum<<endl;

//******************************************************************************************************

	cout<<endl<<"--- Ending Program ---"<<endl<<endl;

	return 0; 

}

