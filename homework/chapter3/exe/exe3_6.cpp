#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::cin;
using std::list;

int josephus(int N, int M);

int main()
{
	int N, M;
	cout << "Enter the N(of people) & M(of passes before elimination ) : ";
	cin >> N >> M;
	cout << "the last one is : " << ( 1 + josephus(N, M)) << endl;
    return 0;
}

int josephus(int N, int M)
{
	if(N == 1)
	{
		return 0;
	}
	else
	{
		return (josephus(N - 1, M) + M) % N;
	}
}

