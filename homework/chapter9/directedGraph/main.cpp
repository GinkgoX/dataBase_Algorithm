#include<iostream>
#include<vector>
#include<queue>
#include<string>

using namespace std;
const int N = 10;
vector<bool> visited(N);

struct EdageNode{
	int adjointVertex;
	EdageNode *next;
	
	//EdageNode constructor
	EdageNode(int a = 0, EdageNode *n = NULL):adjointVertex(a), next(n){
	
	};
};

struct AdjointList{
	string data;
	EdageNode *firstEdage;
};

struct Graph{
	int numVertex;
	int numEdge;
	vector<AdjointList> adjointList;
	
	//Graph constructor
	Graph(int n = 10):adjointList(n){
	};
};

//create Graph g
void createGraph(Graph &g);

//get value's position in g
int getPosition(Graph g, string value);

//print the graph
void print(Graph g);

//Depth First Search for Graph g with index i
void DFS(Graph g, int index);

//Depth First Search Traverse
void DFSTraverse(Graph g);

//Breadth First Search Traverse
void BFSTraverse(Graph g);

//destroy Graph g
void destroyGraph(Graph &g);

int main(){
	Graph g;
	cout << "*********** createGraph *************" << endl;
	createGraph(g);
	cout << "*********** printGraph *************" << endl;
	print(g);
	cout << "*********** DFSTraverse *************" << endl;
	DFSTraverse(g);
	cout << "*********** BFSTraverse *************" << endl;
	BFSTraverse(g);
	cout << "*********** destroyGraph *************" << endl;
	destroyGraph(g);
	cout << " done ." << endl;
	return 0;
}

void createGraph(Graph &g){
	cout << "Enter the num of vertex and edage splited with space : " << endl;
	cin >> g.numVertex >> g.numEdge;
	cout << "Please enter the vertex info : " << endl;
	for(int i = 0; i < g.numVertex; i++){
		cout << i + 1 << "th vertex is : ";
		cin >> g.adjointList[i].data;
		g.adjointList[i].firstEdage = NULL;
	}
	int pos1, pos2;
	string data1, data2;
	EdageNode *node;
	EdageNode *temp;
	cout << "In directed graph, edage(v, w) means v -> w" << endl;
	for(int i = 0; i < g.numEdge; i++){
		cout << "Please enter the edage (v_i, v_j) info : ";
		cin >> data1 >> data2;
		pos1 = getPosition(g, data1);
		pos2 = getPosition(g, data2);
		//data1's firstEdage is NULL or not
		if(g.adjointList[pos1].firstEdage == NULL){		//yes, connect data2 to data1 rear
			node = new EdageNode(pos2, NULL);
			g.adjointList[pos1].firstEdage = node;		
		}else{											//no, connect data2 to data1 until data1's next is NULL
			temp = g.adjointList[pos1].firstEdage;
			while(temp -> next != NULL){
				temp = temp -> next;
			}
			node = new EdageNode(pos2, NULL);
			temp -> next = node;
		}
	}
}

int getPosition(Graph g, string value){
	for(int i = 0; i < g.numVertex; i++){
		if(g.adjointList[i].data == value){
			return i;
		}
	}
	return -1;
}

void print(Graph g){
	cout << " The Graph constructed by adjointList as follows : " << endl;
	for(int i = 0; i < g.numVertex; i++){
		cout << g.adjointList[i].data;
		//access each data and find its next data
		EdageNode *node = g.adjointList[i].firstEdage;
		while(node){
			cout << " --> " << node -> adjointVertex;
			node = node -> next; 
		}
		cout << endl;
	}
}

void DFS(Graph g, int index){
	EdageNode *node;
	visited[index] = true;
	cout << g.adjointList[index].data << " ";
	node = g.adjointList[index].firstEdage;
	//access data until the node is NULL
	while(node){
		if(!visited[node -> adjointVertex]){
			DFS(g, node -> adjointVertex);
		}
		node = node -> next;
	}
}

void DFSTraverse(Graph g){
	for(int i = 0; i < g.numVertex; i++){
		visited[i] = false;
	}
	for(int i = 0; i < g.numVertex; i++){
		if(!visited[i]){
			DFS(g, i);
		}
	}
	cout << endl;
}

void BFSTraverse(Graph g){
	EdageNode *node;
	queue<int> bfsQueue;
	vector<bool> visited(g.numVertex);
	for(int i = 0; i < g.numVertex; i++){
		visited[i] = false;
	}
	for(int i = 0; i < g.numVertex; i++){
		if(!visited[i]){
			visited[i] = true;
			cout << g.adjointList[i].data << " ";
			bfsQueue.push(i);
			while(!bfsQueue.empty()){
				int count = bfsQueue.front();
				bfsQueue.pop();
				node = g.adjointList[i].firstEdage;
				//access firstEdage until node is NULL
				while(node){
					if(!visited[node -> adjointVertex]){
						visited[node -> adjointVertex] = true;
						cout << g.adjointList[node -> adjointVertex].data << " ";
						bfsQueue.push(node -> adjointVertex);
					}
					node = node -> next;
				}
			}
		}
	}
	cout << endl;
}

void destroyGraph(Graph &g){
	EdageNode *temp = NULL;
	for(int i = 0; i < g.numVertex; i++){
		temp = g.adjointList[i].firstEdage;
		while(temp){
			EdageNode *node = temp;
			temp = temp -> next;
			delete node;
		}
		g.adjointList[i].firstEdage = NULL;
	}
}

