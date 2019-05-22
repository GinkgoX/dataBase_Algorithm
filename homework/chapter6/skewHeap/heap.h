#ifndef HEAP_H_
#define HEAP_H_

#include<iostream>
#include<vector>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;

template<class T>
struct SkewNode{
	T element;
	SkewNode<T> *left;
	SkewNode<T> *right;
	
	SkewNode(const T &e, SkewNode<T> *l = NULL, SkewNode<T> *r = NULL):element(e), left(l), right(r){
	};
};

template<class T>
class SkewHeap{
public:
	//LeftistHeap constuctor
	SkewHeap():root(NULL){
	
	};
	
	//LeftistHeap constuctor
	SkewHeap(const SkewHeap &heap){
		root = clone(heap -> root);
	};
	
	//LeftistHeap destructor
	~SkewHeap(){
		makeEmpty();
	};
	
	//judge whether the heap is empty
	bool isEmpty() const{
		return root == NULL;
	};
	
	//find the minmum element in heap
	const T &findMin() const{
		if(root != NULL){
			return root -> element;
		}
		return (T)NULL;
	};
	
	//insert value
	void insert(const T &value){
		SkewNode<T>* temp;
		temp = new SkewNode<T>(value, NULL, NULL);
		root = merge(root, temp);
	};
	
	//delete the minmum
	void deleteMin(){
		if(isEmpty()){
			cout << " the heap is already empty !" << endl;
		}
		SkewNode<T> *node = root;
		root = merge(root -> left, root -> right);
		delete node;
	};
	
	//delete the minItem
	void deleteMin(T &minItem){
		minItem = findMin();
		deleteMin();
	}
	
	//make empty of the heap
	void makeEmpty(){
		reclaimMemory(root);
		root = NULL;
	};
	
	//excute merge operation
	void merge(SkewHeap<T> *heap){
		root = merge(root, heap -> root);
	};
	
	const SkewHeap<T> & operator=(const SkewHeap<T> &heap){
		if(this != &heap){
			makeEmpty();
			root = clone(heap.root);
		}
		return *this;
	};
	
	//print the heap
	void print(){
		SkewHeap heap;
		vector<T> v;
		while(this -> root){
			v.push_back(this -> findMin());
			heap.insert(this -> findMin());
			this -> deleteMin();
		}
		for(int i = 0; i < v.size(); i++){
			cout << v[i] << " ";
		}
		cout << endl;
		*this = heap;
		
	};
	
private:
	SkewNode<T>* merge(SkewNode<T>* &h1, SkewNode<T>* &h2);
	void swapChildren(SkewNode<T>* &h1, SkewNode<T>* &h2);
	void reclaimMemory(SkewNode<T> *heap);
	SkewNode<T>* clone(const SkewNode<T> *heap);
private:
	SkewNode<T>* root;
};

//merge root
template<class T>
SkewNode<T>* SkewHeap<T>::merge(SkewNode<T>* &h1, SkewNode<T>* &h2){
	if(h1 == NULL){
		return h2;
	}
	if(h2 == NULL){
		return h1;
	}
	if(h1 -> element > h2 -> element){
		swapChildren(h1, h2);
	}
	SkewNode<T>* temp = merge(h1 -> right, h2);
	h1 -> right = h1 -> left;
	h1 -> left = temp;
	return h1;
}

template<class T>
void SkewHeap<T>::swapChildren(SkewNode<T>* &h1, SkewNode<T>* &h2){
	SkewNode<T>* temp = h1; 
	h1 = h2;
	h2 = temp;
}

template<class T>
void SkewHeap<T>::reclaimMemory(SkewNode<T> *heap){
	if(heap != NULL){
		reclaimMemory(heap -> left);
		reclaimMemory(heap -> right);
		delete heap;
	}
}

template<class T>
SkewNode<T>* SkewHeap<T>::clone(const SkewNode<T> *heap){
	if(heap == NULL){
		return NULL;
	}
	return new SkewNode<T>(heap -> element, clone(heap -> left), clone(heap -> right));
}

#endif
