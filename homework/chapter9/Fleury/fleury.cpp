#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

const int N = 20;

//define the Stack container
struct Stack{
	int top;
	int vertex[N];
}s;

int graph[N][N];
//dfs algorithm to traverse connection path
void dfs(int start, int numVertex);
//fleury algorithm to output the Eular loop
void fleury(int start, int numVertex);

int main(){
	int numVertex, numEdge;
	int u, v, degree;
	int start, num, i;
	
	ifstream fin("input.txt");
	fin >> numVertex >> numEdge;
	
	memset(graph, 0, sizeof(graph));
	//update the graph by file input
	for(i = 0; i < numEdge; i++){
		fin >> u >> v;
		graph[u-1][v-1] = graph[v-1][u-1] = 1;
	}
	//claculate the degree of vertex
	for(i = 0; i < numVertex; i++){
		degree = 0;
		for(int j = 0; j < numVertex; j++){
			degree += graph[i][j];
		}
		//odd number degree case
		if(degree & 1){
			start = i;
			num++;
		}
	}
	//only the degree of vertex is even, than there will exist the Eular loop
	if(num == 0 || num == 2){
		fleury(start, numVertex);
	}else{
		cout << "The graph has no Eular Loop !" << endl;
	}
	cout << " done ." << endl;
	return 0;
}

void dfs(int start, int numVertex){
	//push the start vertex into stack;
	s.vertex[++s.top] = start;
	for(int i = 0; i < numVertex; i++){
		//update the visited vertex
		if(graph[i][start] > 0){
			graph[i][start] = graph[start][i] = 0;
			//iterative call the dfs algorithm to find the connection path
			dfs(i, numVertex);
			break;
		}
	}
}

void fleury(int start, int numVertex){
	s.top = 0;
	s.vertex[s.top] = start;
	bool flag;
	while(s.top >= 0){
		flag = false;
		//find the connection vertex and set flag
		for(int i = 0; i < numVertex; i++){
			if(graph[s.vertex[s.top]][i] > 0){
				flag = true;
				break;
			}
		}
		//the vertex has only one connection vertex
		if(!flag){
			cout << (s.vertex[s.top--] + 1) << " -> ";
		//the vertex has more than one connection vertex
		}else{
			dfs(s.vertex[s.top--], numVertex);
		}
	}
}
