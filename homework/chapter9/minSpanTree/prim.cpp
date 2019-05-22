#include<iostream>
#include<fstream>

using  namespace std; 
//define the max size of adjecent matrix
const int N = 20;
//define the INF distance
const int INF = 9999;

int prim(int graph[][N], int numVertex)
{
	int d_v[N];
	int mst[N];
	int i, j, min, minid, sum = 0;
	//get the distance betweent v1 to others
	for (i = 2; i <= numVertex; i++)
	{
		d_v[i] = graph[1][i];
		mst[i] = 1;
	}
	mst[1] = 0;
	//find the minimum distance of the vertex
	for (i = 2; i <= numVertex; i++)
	{
		min = INF;
		minid = 0;
		//find the minimum adjecent distance
		for (j = 2; j <= numVertex; j++)
		{
			if (d_v[j] < min && d_v[j] != 0)
			{
				min = d_v[j];
				minid = j;
			}
		}
		cout << "V" << mst[minid] << "- V" << minid << " = " << min << endl;
		sum += min;
		d_v[minid] = 0;
		//update the distance betweent prensent vertex and last vertex
		for (j = 2; j <= numVertex; j++)
		{
			if (graph[minid][j] < d_v[j])
			{
				d_v[j] = graph[minid][j];
				mst[j] = minid;
			}
		}
	}
	return sum;
}

int main()
{
	int i, j, numVertex, numEdage, weight;
	int graph[N][N];
	
	//read data from file
	ifstream fin("test.txt");
	fin >> numVertex >> numEdage;
	cout << "read m = " << numVertex << " and n = " << numEdage << endl;
	
	//initlize the adjecent matrix
	for (i = 1; i <= numVertex; i++)
	{
		for (j = 1; j <= numVertex; j++)
		{
			graph[i][j] = INF;
		}
		graph[i][i] = 0;
	}
	
	//update the matrix based on file
	for (int k = 1; k <= numEdage; k++)
	{
		fin >> i >> j >> weight;
		graph[i][j] = graph[j][i] = weight;
	}
	
	//find the minimum sum weight 
	cout << "The minimum sum weight of this graph is : " << prim(graph, numVertex) << endl;
	return 0;
}

