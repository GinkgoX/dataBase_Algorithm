#ifndef SPLAY_H_
#define SPLAY_H_

#include<iostream>
#include<iomanip>

using std::cout;
using std::endl;
using std::setw;

template<class T>
struct Node{
	T data;
	Node *left;
	Node *right;
	Node():left(NULL), right(NULL){};
	Node(T d, Node<T> *l, Node<T> *r):data(d), left(l), right(r){};
};

template<class T>
class Splay{
private:
	Node<T> *root;
public:
	//Splay constructor
	Splay():root(NULL){
	
	};
	
	//Splay destructor
	~Splay(){
		destroy();
	};
	
	//preOrder 
	void preOrder(){
		preOrder(root);
	};
	
	//inOrder
	void inOrder(){
		inOrder(root);
	};
	
	//postOrder
	void postOrder(){
		postOrder(root);
	};
	
	//Splay search without iterative
	Node<T>* search(T d){
		search(root, d);
	};
	
	//Splay search with iterative
	Node<T>* iterativeSearch(T d){
		iterativeSearch(root, d);
	};
	
	//find maximum value
	T max(){
		Node<T> *temp = max(root);
		if(temp != NULL){
			return temp -> data;
		}
		return (T)NULL;
	};
	
	//find minimum value
	T min(){
		Node<T> *temp = min(root);
		if(temp != NULL){
			return temp -> data;
		}
		return (T)NULL;
	};
	
	//splay the value
	void splay(T d){
		root = splay(root, d);
	};
	
	//Splay insert
	void insert(T d){
		Node<T> *temp = NULL;
		if((temp = new Node<T>(d, NULL, NULL)) == NULL){
			return;
		}
		//from root insert d
		root = insert(root, temp);
		//splay d as new root
		root = splay(root, d);
	};
	
	//Splay remove
	void remove(T d){
		root = remove(root, d);
	};
	
	//Splay destroy
	void destroy(){
		destroy(root);
	};
	//Splay print
	void print(){
		if(root != NULL){
			print(root, root -> data, 0);
		}
	};

private:
	void preOrder(Node<T> *node) const;
	void inOrder(Node<T> *node) const;
	void postOrder(Node<T> *node) const;
	Node<T>* search(Node<T> *node, T d) const;
	Node<T>* iterativeSearch(Node<T> *node, T d) const;
	Node<T>* min(Node<T> *node);
	Node<T>* max(Node<T> *node);
	Node<T>* splay(Node<T> *node, T d);
	Node<T>* insert(Node<T>* &node, Node<T> *d);
	Node<T>* remove(Node<T>* &node, T d);
	void destroy(Node<T>* &node);
	void print(Node<T> *node, T d, int direction);
};

template<class T>
void Splay<T>::preOrder(Node<T> *node) const{
	if(node != NULL){
		cout << node -> data << " ";
		preOrder(node -> left);
		preOrder(node -> right);
	}
}

template<class T>
void Splay<T>::inOrder(Node<T> *node) const{
	if(node != NULL){
		inOrder(node -> left);
		cout << node -> data << " ";
		inOrder(node -> right);
	}
}

template<class T>
void Splay<T>::postOrder(Node<T> *node) const{
	if(node != NULL){
		postOrder(node -> left);
		postOrder(node -> right);
		cout << node -> data << " ";
	}
}

template<class T>
Node<T>* Splay<T>::search(Node<T> *node, T d) const{
	if(node == NULL || d == node -> data){
		return node;
	}
	if(d < node -> data){
		search(node -> left, d);
	}else{
		search(node -> right, d);
	}
}

template<class T>
Node<T>* Splay<T>::iterativeSearch(Node<T> *node, T d) const{
	while( (node != NULL) && (d != node -> data)){
		if(d < node -> data){
			node = node -> left;
		}
		else{
			node = node -> right;
		}
	}
	return node;
}

template<class T>
Node<T>* Splay<T>::min(Node<T> *node){
	if(node == NULL){
		return node;
	}
	while(node -> left != NULL){
		node = node -> left;
	}
	return node;
}

template<class T>
Node<T>* Splay<T>::max(Node<T> *node){
	if(node == NULL){
		return node;
	}
	while(node -> right != NULL){
		node = node -> right;
	}
	return node;
}

template<class T>
Node<T>* Splay<T>::splay(Node<T> *node, T d){
	Node<T> temp, *l ,*r, *cur;
	if(node == NULL){
		return node;
	}
	temp.left = temp.right = NULL;
	l = r = &temp;
	
	for(;;){
		if(d < node -> data){
			//right rotation
			if(node -> left == NULL){
				break;
			}
			if(d < node -> left -> data){
				cur = node -> left;
				node -> left = cur -> right;
				cur -> right = node;
				node = cur;
				if(node -> left == NULL){
					break;
				}
			}
			//link right
			r -> left = node;
			r = node;
			node = node -> left;
		}else if(d > node -> data){
			if(node -> right == NULL){
				break;
			}
			//left rotation
			if(d > node -> right -> data){
				cur = node -> right;
				node -> right = cur -> left;
				cur -> left = node;
				node = cur;
				if(node -> right == NULL){
					break;
				}
			}
			//link left
			l -> right = node;
			l = node;
			node = node -> right;	
		}else{
			break;
		}
	}
	//assemble
	l -> right = node -> left;
	r -> left = node -> right;
	node -> left = temp.right;
	node -> right = temp.left;
	return node;
}

template<class T>
Node<T>* Splay<T>::insert(Node<T>* &node,Node<T> *d){
	Node<T> *temp1 = NULL;
	Node<T> *temp2 = node;
	while(temp2 != NULL){
		temp1 = temp2;
		if(d -> data < temp2 -> data){
			temp2 = temp2 -> left;
		}else if(d -> data > temp2 -> data){
			temp2 = temp2 -> right;
		}else{
			cout << " can't insert the existed node !" << endl;
			delete d;
			return node;
		}
	}
	if(temp1 == NULL){
		node = d;
	}else if(d -> data < temp1 -> data){
		temp1 -> left = d;
	}else{
		temp1 -> right = d;
	}
	return node;
}

template<class T>
Node<T>* Splay<T>::remove(Node<T>* &node, T d){
	Node<T> *temp;
	//judge whether the node is root
	if(node == NULL){
		return node;
	}
	
	// judge whether there existed d
	if(search(node, d) == NULL){
		return NULL;
	}
	
	//splay the node to root
	node = splay(node, d);
	if(node -> left != NULL){
		temp = splay(node -> left, d);
		temp -> right = node -> right;
	}else{
		temp = node -> right;
	}
	delete node;
	return temp;
}

template<class T>
void Splay<T>::destroy(Node<T>* &node){
	if(node == NULL){
		return;
	}
	if(node -> left != NULL){
		destroy(node -> left);
	}
	if(node -> right != NULL){
		destroy(node -> right);
	}
	delete node;
}

template<class T>
void Splay<T>::print(Node<T> *node, T d, int direction){
	if(node != NULL){	
		if(direction == 0){
			cout << setw(2) << node -> data << " is root " << endl;
		}else{
			cout << setw(2) << node -> data << " is " << setw(2) << d << " 's " << setw(12) << (direction == 1 ? " right child " : " left child ") << endl;  
		}
		print(node -> left, node -> data, -1);
		print(node -> right, node -> data, 1);
	}
}

#endif

