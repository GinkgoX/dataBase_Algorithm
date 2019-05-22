#include <iostream>

using namespace std;

const int MaxVal = 9999;

const int n = 5;

//pi and qi array
double p[n + 1] = {-1,0.15,0.1,0.05,0.1,0.2};
double q[n + 1] = {0.05,0.1,0.05,0.05,0.05,0.1};

int root[n + 1][n + 1];		//root array
double w[n + 2][n + 2];		//w[i][j]
double e[n + 2][n + 2];		//e[i][j]
 
void optimalBST(double *p,double *q,int n)
{
	//init w and e
	for (int i = 1;i <= n + 1;++i)
	{
		w[i][i - 1] = q[i - 1];
		e[i][i - 1] = q[i - 1];
	}
	//dynamic programming
	for (int len = 1;len <= n;++len)
	{
		for (int i = 1;i <= n - len + 1;++i)
		{
			int j = i + len - 1;
			e[i][j] = MaxVal;
			//define w[i][j]
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			//find the best BST
			for (int k = i;k <= j;++k)
			{
				double temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
				if (temp < e[i][j])
				{
					e[i][j] = temp;
					root[i][j] = k;
				}
			}
		}
	}
}

//printRoot
void printRoot()
{
	cout << "The root info  : " << endl;
	for (int i = 1;i <= n;++i)
	{
		for (int j = 1;j <= n;++j)
		{
			cout << root[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//printOptimalBST
void printOptimalBST(int i,int j,int r)
{
	//i, j is rootChild
	int rootChild = root[i][j];
	if (rootChild == root[1][n])
	{	
		//output the root
		cout << "Root is : " << rootChild << endl;
		printOptimalBST(i,rootChild - 1,rootChild);
		printOptimalBST(rootChild + 1,j,rootChild);
		return;
	}
 
	if (j < i - 1)
	{
		return;
	}
	//when j = i - 1, the leaf is qi
	else if (j == i - 1)
	{
		if (j < r){
			cout << r << " 's leftChild : " << j << endl;
		}
		else{
			cout << r << " 's rightChild : " << j << endl;
		}
		return;
	}else{
		if (rootChild < r)
		{
			cout << r << " 's leftChild : " << rootChild << endl;
		}
		else{
			cout << r << " 's rightChild : " << rootChild << endl;
		}
	}
	printOptimalBST(i,rootChild - 1,rootChild);
	printOptimalBST(rootChild + 1,j,rootChild);
}

int main()
{
	optimalBST(p,q,n);
	printRoot();
	cout << "Optimal Binary Searckh Tree : " << endl;
	printOptimalBST(1,n,-1);
}

