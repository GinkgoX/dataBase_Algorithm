#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

const int MAX_NUM = 20;
const int INF = 9999;

//define the Node type queue
struct Node{
	int id;
	int w;
	
	//overload operator< since the defalut is max heap for priority_queue
	friend bool operator<(Node n1, Node n2){
		return (n1.w > n2.w);
	}
};

//define the dist vector to update the distance
vector<Node> dist(MAX_NUM);

//EdageNode contains adjointVertex, weight and next pointer
struct EdageNode{
	int adjointVertex;
	int weight;
	EdageNode *next;
	
	//EdageNode constructor
	EdageNode(int a = 0, int w = 0, EdageNode *n = NULL):adjointVertex(a), weight(w), next(n){
	
	};
};

//AdjointList contains data and firstEdage pointer
struct AdjointList{
	int data;
	EdageNode *firstEdage;
};

//Graph contains numVertex, numEdge and the AdjointList type vector adjointList
struct Graph{
	int numVertex;
	int numEdge;
	vector<AdjointList> adjointList;
	
	//Graph constructor
	Graph(int n = 10):adjointList(n){
	};
};

//createGraph with numEdge and numVertex
void createGraph(Graph &g, int numEdge, int numVertex);

//Dijkstra algorithm
void Dijkstra(Graph g, int start);

int main(){
	int numEdge, numVertex;
	cout << "Enter the number of Edage and vertex splited with space : ";
	cin >> numEdge >> numVertex;
	Graph g;
	createGraph(g, numEdge, numVertex);
	cout << "The adjointList info as follow " << endl;
	for(int i = 1; i <= numEdge; i++)
	{
		EdageNode *node = g.adjointList[i].firstEdage;
		cout << i;
		while(node)
		{
			cout << " -> " << node->adjointVertex;
			node = node->next;
		}
		cout << endl;
	}
	int start, end;
	cout << "Enter the start and end vertex to pass : ";
	cin >> start >> end;
	Dijkstra(g, start);
	if(dist[end].w != INF){
		cout << " the minimum distance between " << start << " and " << end << " is " << dist[end].w << endl;
	}else{
		cout << " the path dose not exist ! " << endl;
	}
	for(int i = 0; i < dist.size(); i++){
		cout << dist[i].w << " ";
	}
	cout << endl;
	return 0;
}

void createGraph(Graph &g, int numEdge, int numVertex){
	g.numEdge = numEdge;
	g.numVertex = numVertex;
	//create EdageNode
	for(int i = 0 ; i < g.numVertex; i++){
		g.adjointList[i].firstEdage = NULL;
	}
	cout << "E(v_i, v_j, w) means v_i -> v_j with weight w " << endl;
	int v_i, v_j, w;
	EdageNode *node;
	//create adjointList
	for(int i = 0; i < g.numVertex; i++){
		cout << "Enter E(V_i, v_j, w) : ";
		cin >> v_i >> v_j >> w;
		node = new EdageNode(v_j, w, g.adjointList[v_i].firstEdage);
		g.adjointList[v_i].firstEdage = node;
	}
}

void Dijkstra(Graph g, int start){
	vector<bool> visited(g.numVertex);			//mark the visited vertex
	priority_queue<Node> dijQueue;				//priority_queue container
	for(int i = 0; i < g.numVertex; i++){		//initialize the array
		dist[i].id = i;
		dist[i].w = INF;
		visited[i] = false;
	}
	dist[start].w = 0;							//update currernt vertex weight
	dijQueue.push(dist[start]);
	EdageNode *node;
	while(!dijQueue.empty()){
		Node temp = dijQueue.top();
		dijQueue.pop();
		int u = temp.id;
		if(visited[u]){
			continue;
		}
		visited[u] = true;						//update currernt vertex visited statue
		node = g.adjointList[u].firstEdage;		//get the firstEdage of currernt vertex
		while(node){
			if( (!visited[node -> adjointVertex]) && (dist[node -> adjointVertex].w > dist[u].w + node -> weight) ){	//find the minimum distance
				dist[node -> adjointVertex].w = dist[u].w + node -> weight;
				dijQueue.push(dist[node -> adjointVertex]);
			}
			node = node -> next;				//get the next Edage of currernt vertex
		}
	}
}

