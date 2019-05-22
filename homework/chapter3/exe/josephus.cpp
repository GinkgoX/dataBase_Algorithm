#include<iostream>
#include<list>

using namespace std;

int main()
{
	int mPrime, numLeft;
	int N, M;
	list<int> mList;
	list<int>::iterator iter;
	cout << "Enter the N(of people) & M(of passes before elimination ) : ";
	cin >> N >> M;
	numLeft = N;
	mPrime = M % N;
	for(int i = 1; i <= N; i++){
		mList.push_back(i);
	}
	iter = mList.begin();
	for(int i = 0; i < N; i++)
	{
		mPrime %= numLeft;
		//pass forward
		if(mPrime <= numLeft/2)
		{
			for(int j = 0; j < mPrime; j++)
			{
				iter++;
				if(iter == mList.end())
				{
					iter = mList.begin();
				}
			}	
		}
		//pass backworfd
		else
		{
			for(int j = 0; j < mPrime; j++)
			{
				if(iter == mList.begin())
				{
					iter = --mList.end();
				}
				else
				{
					iter--;
				}
			}
		}
		//output the selected one
		cout << *iter << " ";
		iter = mList.erase(iter);
		if(iter == mList.end())
		{
			iter = mList.begin();
		}
	}
	cout << " done ." << endl;
	return 0;
}





