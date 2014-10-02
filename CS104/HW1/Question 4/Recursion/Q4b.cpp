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

		if (fin.eof())				//if it is at the end of file, close and return
		{

			fin.close();
			return size;
		}

		fin>>temp;					//number not needed, just move cursor to next number
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

		fin >> *a;					//insert value in the file into the array, and move the pointer to the next slot
		a++;

	}

}

int findMax(int *a, int n)
{
	if (n == 0)
	{
		return *a;
	}

	int temp = findMax(a++,n-1);

  	if (*a > findMax(a++,n-1))
  	{
  		return *a;
  	}
  	else
  	{
  		return temp;
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
    int m = 0; 						// this will hold the max value in the array
  	string fileName;

    //Clock stuff
	const int ITERATE = 1000;
	clock_t start, finish;
	double  dur;


//******************************************************************************************************
//								Getting size, creating array, filling array
//								-------------------------------------------

    n = getArrSize(fileName);		//n now holds the number of elements in the file

	a = new int[n];					//a is now pointing at the array of size n
	originalAdd=a;					//originalAdd now holds the address of the beginning of the array

	fillArray(a, fileName);			//This function will fill the array with elements

	a = originalAdd;				//a point back to beginning



//******************************************************************************************************
//								Recursion: finding max value
//								----------------------------

	//m = findMax(a, n, m);

	//Clock Function

	start  = clock();
	for (int i = 0; i < ITERATE; i++)
	{
    	m = findMax(a, n);
	}
	finish = clock();

	dur   = (double)(finish - start);
	dur  /= (CLOCKS_PER_SEC * ITERATE);
	cout << "Elapsed seconds: "<< scientific << dur << endl;



	delete []a;
	
	cout<<"The max value is: "<< m <<endl;

//******************************************************************************************************

	cout<<endl<<"--- Ending Program ---"<<endl<<endl;

	return 0; 

}