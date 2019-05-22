#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<iomanip>

using namespace std;

const int MAXLEVEL = 8;

//define Node
struct Node{
	int key;
	int value;
	Node* forward[1];
};

//create the node
Node* createNode(int level, int key, int value){
	Node* node = (Node*)malloc(sizeof(Node) + level * sizeof(Node*));
	node -> key = key;
	node -> value = value;
	return node;
}

//define SkipList
struct SkipList{
	int level;
	Node* header;

};

//create the skiplist
SkipList* createList(){
	SkipList *skipList = (SkipList*)malloc(sizeof(SkipList));
	skipList -> level = 0;
	skipList -> header = createNode(MAXLEVEL - 1, 0, 0);
	for(int i = 0; i < MAXLEVEL; i++){
		skipList -> header -> forward[i] = NULL;
	}
	return skipList;
}

//get random level
int randomLevel(){
	int k = 1;
	while(rand() % 2){
		k++;
	}
	k = (k < MAXLEVEL) ? k : MAXLEVEL;
	return k;
}

//insert operation
bool insertSL(SkipList *skipList, int key, int value){
	Node* node[MAXLEVEL];
	Node* p = NULL;
	Node* q = NULL;
	p = skipList -> header;
	int k = skipList -> level;
	//find the node p where p -> key < k
	for(int i = k - 1; i >= 0; i--){
		while((q = p -> forward[i]) && (q -> key < key)){
			p = q;
		}
		node[i] = p;
	}
	//if the value has existed, return false
	if(q && (q -> key == key)){
		return false;
	}
	//generate random level
	k = randomLevel();
	//update skiplist level
	if(k > skipList -> level){
		for(int i = skipList -> level; i < k; i++){
			node[i] = skipList -> header;
		}
		skipList -> level = k;
	}
	q = createNode(k, key, value);
	//update the skiplist
	for(int i = 0; i < k; i++){
		q -> forward[i] = node[i] -> forward[i];
		node[i] -> forward[i] = q;
	}
	return true;
}

//delete operation
bool deleteSL(SkipList *skipList, int key){
	Node* node[MAXLEVEL];
	Node* p = NULL;
	Node* q = NULL;
	p = skipList -> header;
	int k = skipList -> level;
	//find the node p where p -> key < k
	for(int i = k -1; i >= 0; i--){
		while((q = p -> forward[i]) && (q -> key < key)){
			p = q;
		}
		node[i] = p;
	}
	//if q -> key == key, find the value
	if(q && (q -> key == key)){
		//delete the skiplist
		for(int i = 0; i < skipList -> level; i++){
			if(node[i] -> forward[i] == q){
				node[i] -> forward[i] = q -> forward[i];
			}
		}
		free(q);
		//if the delete key has the highest level, level--
		for(int i = skipList -> level - 1; i >= 0; i--){
			if(skipList -> header -> forward[i] == NULL){
				skipList -> level --;
			}
		}
		return true;
	}else{
		return false;
	}
}

//search operation
int search(SkipList *skipList, int key){
	Node *p = NULL;
	Node *q = NULL;
	p = skipList -> header;
	int k = skipList -> level;
	for(int i = k -1; i >= 0; i--){
		while((q = p -> forward[i]) && (q -> key <= key)){
			if(q -> key == key){
				return q -> value;
			}
			p = q;
		}
	}
	return (int)NULL;
}

//print the skiplist
void printSL(SkipList *skipList){
	Node *p = NULL;
	Node *q = NULL;
	int k = skipList -> level;
	string s = "  ";
	cout << "The skiplist Info as follows : " << endl;
	for(int i = k - 1; i >= 0; i--){
		p = skipList -> header;
		while(q = p -> forward[i]){
			cout << p -> value << " ";
			p = q;
		}
		cout << endl;
	}
}

int main(){
	int key, value;
	ifstream fin("input.txt");
	SkipList *skipList = createList();
	int i = 0;
	while(fin >> value){
		//insert test
		i++;
		insertSL(skipList, i, value);
	}
	/*for(int i = 1; i <= 19; i++){
		insertSL(skipList, i, i*2);
	}*/
	//print the skiplist
	cout << "************ printSL(skipList) *************" << endl;
	printSL(skipList);
	
	//search value by key
	cout << "************ search(skipList, key) *************" << endl;
	cout << "Enter the key you want to search : ";
	cin >> key;
	cout << "The value is : " << search(skipList, key) << endl;
	
	//delete value by key
	cout << "************ deleteSL(skipList, key) *************" << endl;
	cout << "Enter the key you want to delete : ";
	cin >> key;
	if(deleteSL(skipList, key)){
		cout << "delete successfully !" << endl;
		printSL(skipList);
	}
	cout << "done ." << endl;
	return 0;
}

