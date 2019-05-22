#include<iostream>
#include <stack>

using namespace std;

const int MAX_NUM = 20;
const int INF = 99999;

struct Graph{
	int *edage[MAX_NUM];
	int numVertex;
	int numEdage;
};

//create Graph g
void createGraph(Graph &g);

//floyd algorithm
void floyd(Graph g);

//print the result
void print(Graph g);

int *arrayDist[MAX_NUM];
int main(){
	for(int i = 0; i < MAX_NUM; i++){
		arrayDist[i] = new int[MAX_NUM];
	}
	Graph g;
	for(int i = 0; i <= MAX_NUM; i++){
		g.edage[i] = new int[MAX_NUM];
	}
	createGraph(g);
	floyd(g);
	print(g);
	return 0;
}

void createGraph(Graph &g){
	cout << "Please enter the numVertex and numEdage splicted with space : ";
	cin >> g.numVertex >> g.numEdage;
	for(int i = 1; i <= g.numVertex; i++){
		for(int j = 1; j <= g.numVertex; j++){
			g.edage[i][j] = INF;
		}
	}
	cout << "E(v_i, v_j, w) means v_i -> v_j with weight w " << endl;
	int v_i, v_j, w;
	for(int i = 1; i <= g.numEdage; i++){
		cout << "Please enter the E(v_i, v_j, w) : ";
		cin >> v_i >> v_j >> w;
		g.edage[v_i][v_j] = w;
	}
}

void floyd(Graph g){
	for(int i = 0; i <= g.numVertex; i++){
		for(int j = 0; j <= g.numVertex; j++){
			arrayDist[i][j] = i;
		}
	}
	for(int k = 1; k <= g.numVertex; k++){
		for(int i = 1; i <= g.numVertex; i++){
			for(int j = 1; j <= g.numVertex; j++){
				if(g.edage[i][j] > g.edage[i][k] + g.edage[k][j]){
					g.edage[i][j] = g.edage[i][k] + g.edage[k][j];
					arrayDist[i][j] = arrayDist[k][j];
				}
			}
		}
	}
}

void print(Graph g){
	cout << "start -> end \t Distance \t Path" << endl;
	for(int i = 1; i <= g.numVertex; i++){
		for(int j = 1; j <= g.numVertex; j++){
			if(i != j){
				cout << i << " -> " << j << " \t \t";
				if((g.edage[i][j] >= INF/10 ) ){
					cout << "Unconnected " << " \t \t" << endl;
				}else{
					cout << g.edage[i][j] << " \t \t";
					stack<int> temp;
					int k = j;
					do{
						k = arrayDist[i][k];
						temp.push(k);
					}while(k != i);
					cout << temp.top();
					temp.pop();
					int nSize = temp.size();
					for(int index = 0; index < nSize; index++){
						cout << " -> " << temp.top();
						temp.pop();
					}
					cout << " -> " << j << endl;
				}
			}
		}
	}
}

