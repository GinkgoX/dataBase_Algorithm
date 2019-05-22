#ifndef HEAP_H_
#define HEAP_H_

#include<iostream>
#include<vector>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;

template<class T>
struct LeftistNode{
	T element;
	LeftistNode *left;
	LeftistNode *right;
	int npl;
	
	LeftistNode(const T &e, LeftistNode<T> *l = NULL, LeftistNode<T> *r = NULL, int n = 0):element(e), left(l), right(r), npl(n){
	};
};

template<class T>
class LeftistHeap{
public:
	//LeftistHeap constuctor
	LeftistHeap():root(NULL){
	
	};
	
	//LeftistHeap constuctor
	LeftistHeap(const LeftistHeap &heap){
		root = clone(heap -> root);
	};
	
	//LeftistHeap destructor
	~LeftistHeap(){
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
		root = merge(new LeftistNode<T>(value), root);
	};
	
	//delete the minmum
	void deleteMin(){
		if(isEmpty()){
			cout << " the heap is already empty !" << endl;
		}
		LeftistNode<T> *node = root;
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
	void merge(LeftistHeap<T> &heap){
		if(this == &heap){
			return;
		}
		root = merge(root, heap.root);
		heap.root = NULL;
	};
	
	const LeftistHeap<T> & operator=(const LeftistHeap<T> &heap){
		if(this != &heap){
			makeEmpty();
			root = clone(heap.root);
		}
		return *this;
	};
	
	//print the heap
	void print(){
		LeftistHeap heap;
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
	LeftistNode<T>* merge(LeftistNode<T> *h1, LeftistNode<T> *h2);
	LeftistNode<T>* merge1(LeftistNode<T> *h1, LeftistNode<T> *h2);
	void swapChildren(LeftistNode<T> *heap);
	void reclaimMemory(LeftistNode<T> *heap);
	LeftistNode<T>* clone(const LeftistNode<T> *heap);
private:
	LeftistNode<T>* root;
};

//merge root
template<class T>
LeftistNode<T>* LeftistHeap<T>::merge(LeftistNode<T> *h1, LeftistNode<T> *h2){
	if(h1 == NULL){
		return h2;
	}
	if(h2 == NULL){
		return h1;
	}
	if(h1 -> element < h2 -> element){
		return merge1(h1, h2);
	}else{
		return merge1(h2, h1);
	}
}

template<class T>
LeftistNode<T>* LeftistHeap<T>::merge1(LeftistNode<T> *h1, LeftistNode<T> *h2){
	if(h1 -> left == NULL){
		h1 -> left = h2;
	}else{
		h1 -> right = merge(h1 -> right, h2);
		if(h1 -> left -> npl < h1 -> right -> npl){
			swapChildren(h1);
		}
		h1 -> npl = h1 -> right -> npl + 1;
	}
	return h1;
}

template<class T>
void LeftistHeap<T>::swapChildren(LeftistNode<T> *heap){
	if(heap != NULL){
		LeftistNode<T> *temp = heap -> left;
		heap -> left = heap -> right;
		heap -> right = temp;
	}
}

template<class T>
void LeftistHeap<T>::reclaimMemory(LeftistNode<T> *heap){
	if(heap != NULL){
		reclaimMemory(heap -> left);
		reclaimMemory(heap -> right);
		delete heap;
	}
}

template<class T>
LeftistNode<T>* LeftistHeap<T>::clone(const LeftistNode<T> *heap){
	if(heap == NULL){
		return NULL;
	}
	return new LeftistNode<T>(heap -> element, clone(heap -> left), clone(heap -> right), heap -> npl);
}

#endif
