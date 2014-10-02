#include <fstream>

using namespace std;

int main()
{
	ofstream fout;
	fout.open("timestamps.txt");
	int k = 1384200000;
	for (int i = 0; i < 1000000; ++i)
	{
		if (i%10 == 0)
			fout << endl;
		fout << k << " ";
		k = k + 500;
	}
}