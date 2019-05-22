#include<iostream>
#include<cstring>
#include<vector>

/**
//generic findMax, with a function object, Version #1
//Prediction: a.seze() > 0
*/

using namespace std;

//class with public function only
class CaseInsensitiveCompare
{
public:
	bool isLessThan(const string &s1, const string &s2)const
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}


};

template<typename Object, typename Comparator>
const Object & findMax(const vector<Object> &arr, Comparator cmp)
{
	int maxIndex = 0;
	for(int i = 1; i < arr.size(); i++)
	{
		if(cmp.isLessThan(arr[maxIndex], arr[i]))
		{
			maxIndex = i;
		}
	}
	return arr[maxIndex];
}

int main()
{
	vector<string> arr(3);
	arr[0] = "ZEBAR";
	arr[1] = "zEbar";
	arr[2] = "zebaR";
	cout << findMax(arr, CaseInsensitiveCompare()) << endl;
	return 0;
}


