#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

/**
* return the maxmum item in array a;
* assume a.size() > 0;
* Compareable objects must provide operator< and operator=
*/

template <typename Compareable>
const Compareable & findMax(const vector<Compareable> &a)
{
	int maxIndex = 0;
	for(int i = 1; i < a.size(); i++)
	{
		if(a[maxIndex] < a[i])
		{
			maxIndex = i;
		}
	}
	return a[maxIndex];
}

int main()
{
	vector<int> vi(4, 1);
	vector<double> vd(3, 0.01);
	vector<string> vs(5, "OK");
	cout << findMax(vi) << endl;
	cout << findMax(vd) << endl;
	cout << findMax(vs) << endl;
	return 0;
}
