#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct Tree{
	char key;
	int frequency;
	Tree *left;
	Tree *right;
	
	//Tree constructor
	Tree(char k = ' ', int f = 0, Tree *l = NULL, Tree *r = NULL):key(k), frequency(f), left(l), right(r){
	
	};
	
};

struct LargerThan{
	bool operator()(Tree *first, Tree *second){
		return first -> frequency > second -> frequency;
	}
};

priority_queue<Tree*, vector<Tree*>, LargerThan> priQueue;

//print the result of Huffman coding
void printCode(Tree *root, string str);

//delete the tree
void deleteTree(Tree *root);

//huffman algorithm
void huffman(vector<char> &kArray, vector<int> &fArray);

int main(){
	ifstream fin("input.txt");
	char k;
	int f;
	vector<char> kArray;
	vector<int> fArray;
	while(fin>>k){
		kArray.push_back(k);
		fin >> f;
		fArray.push_back(f);
	}
	fin.close();
	cout << "The info as follows : " << endl;
	for(int i = 0; i < kArray.size(); i++){
		cout << kArray[i] << " : " << fArray[i] << endl;
	}
	huffman(kArray, fArray);
	cout << "done ." << endl;
	return 0;
}


void huffman(vector<char> &kArray, vector<int> &fArray){
	//create sigle tree group as froest
	for(int i = 0; i < kArray.size(); i++){
		Tree *root = new Tree(kArray[i], fArray[i]);
		priQueue.push(root);
	}
	//merge the forest as sigle tree
	while(priQueue.size() > 1){
		Tree *l;
		Tree *r;
		l = priQueue.top();
		priQueue.pop();
		r = priQueue.top();
		priQueue.pop();
		Tree *root = new Tree('\0', l -> frequency + r -> frequency, l, r);
		priQueue.push(root);
	}
	string str = "";
	printCode(priQueue.top(), str);
	deleteTree(priQueue.top());
}

void deleteTree(Tree *root){
	if(root == NULL){
		return;
	}
	deleteTree(root -> left);
	deleteTree(root -> right);
	delete root;
}

void printCode(Tree *root, string str){
	if(root == NULL){
		return;
	}
	//assign the left child coding
	if(root -> left){
		str += '0';
	}
	printCode(root -> left, str);
	
	//print the leaf coding
	if(!root -> left && !root -> right){
		cout << root -> key << " 's Huffman code is : " << str << endl;
	}
	
	str.pop_back();
	//assign the right child coding
	if(root -> right){
		str += '1';
	}
	printCode(root -> right, str);
}
