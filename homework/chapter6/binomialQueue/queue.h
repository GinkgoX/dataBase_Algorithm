#ifndef QUEUE_H_
#define QUEUE_H_

#include<iostream>
using std::cout;
using std::endl;

template<class T>
struct BinomialNode{
	T key;
	BinomialNode<T>* leftChild;
	BinomialNode<T>* nextSibling;
};

template<class T>
class BinomialQueue{
public:
	//BinomialQueue constructor
	BinomialQueue(int n = 10):capacity(n){
		currentSize = 0;
		forest = new BinomialNode<T>*[capacity];
		for(int i = 0; i < capacity; i++){
			forest[i] = NULL;
		}
	};
	
	//BinomialQueue destructor
	~BinomialQueue(){
		makeEmpty();
		delete forest;
		forest = NULL;
	};
	
	//insert value into queue 
	void insert(T value){
		//construct queue with one node, than merge the queue
		BinomialQueue<T> queue(capacity);
		queue.forest[0] = new BinomialNode<T>();
		queue.forest[0] -> key = value;
		queue.forest[0] -> leftChild = queue.forest[0] -> nextSibling = NULL;
		queue.currentSize = 1;
		merge(queue); 
	};
	
	//merge queue into this
	void merge(BinomialQueue &queue){
		if( (currentSize + queue.currentSize) > 2 * (1 << capacity) - 1){
			cout << " the size is out of capacity !" << endl;
			return;
		}
		currentSize += queue.currentSize;
		BinomialNode<T>* t1;
		BinomialNode<T>* t2;
		BinomialNode<T>* carry = NULL;
		int i,j;
		for(i = 0, j = 1; j <= currentSize; i++, j *= 2){
			t1 = forest[i];
			t2 = queue.forest[i];
			//encoding carry | t2 | t1 to binary
			switch(!!t1 + 2 * !!t2 + 4 * !!carry){
				case 0: //000	all is NULL
				case 1: //001	only t1
						break;
				case 2: //010	only t2
						forest[i] = queue.forest[i];
						queue.forest[i] = NULL;
						break;
				case 3: //011	t2 and t1
						carry = combineTree(t1, t2);
						forest[i] = queue.forest[i] = NULL;
						break;
				case 4: //100	only carry
						forest[i] = carry;
						carry = NULL;
						break;
				case 5: //101	carry and t1
						carry = combineTree(t1, carry);
						forest[i] = NULL;
						break;
				case 6: //110	carry and t2
						carry = combineTree(t2, carry);
						queue.forest[i] = NULL;
						break;
				case 7: //111	all of three
						forest[i] = carry;
						carry = combineTree(t1, t2);
						queue.forest[i] = NULL;
						break;
			}	
		}
	};
	
	//delete minimum key from queue
	T deleteMin(){
		int minTree;
		T minItem = (T)100;
		//find the minTree index
		for(int i = 0; i < capacity; i++){
			if(forest[i] && forest[i] -> key < minItem){
				minTree = i;
				minItem = forest[i] -> key;
			}
		}
		//delete the minTree root
		BinomialNode<T>* deletedTree = forest[minTree];
		BinomialNode<T>* oldRoot = deletedTree;
		deletedTree = deletedTree -> leftChild;
		delete oldRoot;
		oldRoot = NULL;
		//construct new queue
		BinomialQueue<T> deletedQueue; 
		deletedQueue.currentSize = (1 << minTree) - 1;
		for(int i = minTree - 1; i>= 0; i--){
			deletedQueue.forest[i] = deletedTree;
			deletedTree = deletedTree -> nextSibling;
			deletedQueue.forest[i] -> nextSibling = NULL;
		}
		forest[minTree] = NULL;
		currentSize -= deletedQueue.currentSize + 1;
		merge(deletedQueue);
		return minItem;
	};
	
	//print the queue info
	void print(){
		for(int i = 0; i < capacity; i++){
			cout << "the " << i << " th order : " << endl;
			print(forest[i], 0);
		}
	};
	
	//make the queue empty
	void makeEmpty(){
		for(int i = 0; i < capacity; i++){
			makeEmpty(forest[i]);
		}
	};
	
private:
	
	//combine t2 to t1
	BinomialNode<T>* combineTree(BinomialNode<T>* t1, BinomialNode<T>* t2){
		//combine the lager root to smaller root
		if(t2 -> key < t1 -> key){
			return combineTree(t2, t1);
		}
		//update the tree
		t2 -> nextSibling = t1 -> leftChild;
		t1 -> leftChild = t2;
		return t1;
	};
	
	//makeEmpty overload
	void makeEmpty(BinomialNode<T>* node){
		if(node == NULL){
			return;
		}
		//iterator clean node's children
		makeEmpty(node -> leftChild);
		makeEmpty(node -> nextSibling);
		delete node;
		node = NULL;
	};
	
	//print overload
	void print(BinomialNode<T>* node, int index){
		if(node == NULL){
			return;
		}
		if(index == 1){
			cout << " child ";
		}
		if(index == 2){
			cout << " sibling ";
		}
		cout << node -> key << endl;
		print(node -> leftChild, 1);
		print(node -> nextSibling, 2);
	};
private:
	int capacity;
	int currentSize;
	BinomialNode<T>* *forest;
};

#endif
