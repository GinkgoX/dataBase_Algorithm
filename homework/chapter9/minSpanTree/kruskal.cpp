#include <iostream>
#include<fstream>
#include<algorithm>

using namespace std;

const int N = 20;
int parent[N];

struct Edge{
	int u,v,w;
}edges[N];

//initialize the parent
void initParent(int numEdage){
	for(int i = 1; i <= numEdage; i++){
		parent[i] = -1;
	}
}

//find the vertex's parent and squeeze the path
int findParent(int i){
	int temp;
	for(temp = i; parent[temp] >= 0; temp = parent[temp]);
	while(temp != i){
		int t = parent[i];
		parent[i] = temp;
		i = t;
	}
	return temp;
}

//merge the two vertex into a tree
void mergeVertex(int u,int v){
	int r1 = findParent(u);
	int r2 = findParent(v);
	int tmp = parent[r1] + parent[r2];
	if(parent[r1] > parent[r2]){
		parent[r1] = r2;
		parent[r2] = tmp;
	}else{
		parent[r2] = r1;
		parent[r1] = tmp;
	}
}

//kruskal algorithm
int kruskal(int numVertex, int numEdage){
	int sum = 0;
	int u,v;
	initParent(numEdage);
	for(int i = 0; i < numVertex; i++)
	{
		u = edges[i].u;
		v = edges[i].v;
		//judege whether the two vertex in same union
		if(findParent(u) != findParent(v)){
			cout << "Edage info : (" << u << ", " << v << ", " << edges[i].w << " )" << endl;
			sum += edges[i].w;
			mergeVertex(u, v);
		}
	}
	return sum;
}

//the compar function
int largerThan(const void * a, const void * b){
	//convert Edge* into const void Edge*
	Edge * e1 = (Edge *)a;
	Edge * e2 = (Edge *)b;
	return e1->w - e2->w;
}

int main() {
	int numEdage, numVertex;
	//read data from file
	ifstream fin("test.txt");
	fin >> numEdage >> numVertex;
	//update the edges
	for(int i = 0; i < numVertex; i++){
		fin >> edges[i].u >> edges[i].v >> edges[i].w;
	}
	//qsort parameters: void qsort (void* base, size_t num, size_t size,int (*compar)(const void*,const void*));
	qsort(edges, numVertex, sizeof(Edge), largerThan);
	cout << "The MST is : " << kruskal( numVertex, numEdage) << endl;
	return 0;
}
