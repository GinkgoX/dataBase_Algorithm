#ifndef RBTREE_H_
#define RBTREE_H_

#include<iostream>
#include<iomanip>

using std::cout;
using std::endl;
using std::setw;

enum Color{RED, BLACK};

template<class T>
struct Node{
	T key;
	Color color;
	Node<T> *parent;
	Node<T> *left;
	Node<T> *right;
	
	//Node constructor
	Node(T value, Color c, Node<T> *p, Node<T> *l, Node<T> *r)
		:key(value), color(c), parent(p), left(l), right(r){	
	};	
};

//get parent
template<class T>
Node<T>* getParent(Node<T> *node){
	return node -> parent;
}

//set parent
template<class T>
void setParent(Node<T> *node, Node<T> *p){
	node -> parent = p;
}

//get color
template<class T>
Color getColor(Node<T> *node){
	return node -> color;
}

//set color
template<class T>
void setColor(Node<T> *node, Color c){
	node -> color = c;
}

template<class T>
class RBTree{
private:
	Node<T> *root;
public:
	//RBTree constructor
	RBTree():root(NULL){
	};
	
	//RBTree destructor
	~RBTree(){
		destroy(root);
	};
	
	//preOrder the RBTree
	void preOrder(){
		preOrder(root);
	};
	
	//inOrder the RBTree
	void inOrder(){
		inOrder(root);
	};
	
	//postOrder the RBTree
	void postOrder(){
		postOrder(root);
	};
	
	//get the maxmium value
	T max(){
		Node<T> *temp = max(root);
		if(temp != NULL)
		{
			return temp -> key;
		}
		return (T)NULL;
	};
	
	//get the minimum value
	T min(){
		Node<T> *temp = min(root);
		if(temp != NULL)
		{
			return temp -> key;
		}
		return (T)NULL;
	};
	
	//search the value
	void search(T value){
		search(root, value);
	};
	
	//iterative search the value
	void iterativeSearch(T value){
		iterativeSearch(root, value);
	}
	
	//get the presuccessor
	Node<T>* presuccessor(Node<T> *node){
		if(node -> left != NULL){
			return max(node -> left);
		}
		Node<T> *temp = node -> parent;
		while((temp != NULL) && (node == temp -> left) ){
			node = temp;
			temp = temp -> parent;
		}
		return temp;
	};
	
	//get the successor
	Node<T>* successor(Node<T> *node){
		if(node -> right != NULL){
			return min(node -> right);
		}
		Node<T> *temp = node -> parent;
		while( (temp != NULL)&&(node == temp -> right) ){
			node = temp;
			temp = temp -> parent;
		}
		return temp;
	};
	
	//insert the value
	void insert(T value){
		Node<T> *temp = NULL;
		if((temp = new Node<T>(value, BLACK, NULL, NULL, NULL)) == NULL){
			return;
		}
		insert(root, temp);
	}
	
	//remove the value
	void remove(T value){
		Node<T> *temp;
		if((temp = search(root, value)) != NULL){
			remove(root, temp);
		}
	}
	
	//print the RBTree
	void print(){
		if(root != NULL){
			print(root, root -> key, 0);
		}
	};
	
	//destroy the RBTree
	void destroy(){
		destroy(root);
	};
	
private:
	//preOrder overload
	void preOrder(Node<T> *node) const;
	
	//inOrder overload
	void inOrder(Node<T> *node) const;
	
	//postOrder overload
	void postOrder(Node<T> *node) const;
	
	//search overload
	Node<T>* search(Node<T> *node, T value) const;
	
	//iterativeSearch overload
	Node<T>* iterativeSearch(Node<T> *node, T value) const;
	
	//max overload
	Node<T>* max(Node<T> *node);
	
	//min overload
	Node<T>* min(Node<T> *node);
	
	//left rotation
	void leftRotate(Node<T>* &tree, Node<T> *node);
	
	//right rotation
	void rightRotate(Node<T>* &tree, Node<T> *node);
	
	//insert overload
	void insert(Node<T>* &tree, Node<T> *node);
	
	//insert fix up
	void insertFixUp(Node<T>* &tree, Node<T> *node);
	
	//remove overload
	void remove(Node<T>* &tree, Node<T> *node);
	
	//remove fix up
	void removeFixUp(Node<T>* &tree, Node<T> *node, Node<T> *p);
	
	//destroy overload
	void destroy(Node<T>* &tree);
	
	//print overload
	void print(Node<T> *node, T value, int direction);
};

template<class T>
void RBTree<T>::preOrder(Node<T> *node) const{
	if(node != NULL){
		cout << node -> key << " ";
		preOrder(node -> left);
		preOrder(node -> right);
	}
}

template<class T>
void RBTree<T>::inOrder(Node<T> *node) const{
	if(node != NULL){
		inOrder(node -> left);
		cout << node -> key << " ";
		inOrder(node -> right);
	}
}

template<class T>
void RBTree<T>::postOrder(Node<T> *node) const{
	if(node != NULL){
		postOrder(node -> left);
		postOrder(node -> right);
		cout << node -> key << " ";
	}
}

template<class T>
Node<T>* RBTree<T>::search(Node<T> *node, T value) const{
	if((node == NULL) || (value == node -> key)){
		return node;
	}
	if(value < node -> key){
		return search(node -> left, value);
	}
	if(value > node -> key){
		return search(node -> right, value);
	}
}

template<class T>
Node<T>* RBTree<T>::iterativeSearch(Node<T> *node, T value) const{
	while((node != NULL) && (value != node -> key)){
		if(value < node -> key){
			node = node -> left;
		}else{
			node = node -> right;	
		}
	}
	return node;
}

template<class T>
Node<T>* RBTree<T>::max(Node<T> *node){
	if(node == NULL){
		return node; 
	}
	while(node -> right != NULL){
		node = node -> right;
	}
	return node;
}

template<class T>
Node<T>* RBTree<T>::min(Node<T> *node){
	if(node == NULL){
		return node;
	}
	while(node -> left != NULL){
		node = node -> left;
	}
	return node;
}

template<class T>
void RBTree<T>::leftRotate(Node<T>* &tree, Node<T> *x){
	//set y is x right child
	Node<T> *y = x -> right;
	//set y' left child as x'right child
	x -> right = y  -> left;
	//judge whether y has left child 
	if(y -> left != NULL){
		y -> left -> parent = x;
	}
	//set x's parent as y' parent
	y -> parent = x -> parent;
	//link y and x's parent
	if(x -> parent == NULL){
		root = y;
	}else{
		if(x == x -> parent -> left){
			x -> parent -> left = y;
		}else{
			x -> parent -> right = y;
		}
		
	}
	//set x as y's left child
	y -> left = x;
	//set y as x's parent
	x -> parent = y;
}

template<class T>
void RBTree<T>::rightRotate(Node<T>* &tree, Node<T> *y){
	//set x as y's left child
	Node<T> *x = y -> left;
	//set x 's right child as x's left child
	y -> left = x -> right;
	//judge whether x has right child
	if(x -> right != NULL){
		x -> right -> parent = x;
	}
	//link y's parent as x's parent
	x -> parent = y -> parent;
	if(y -> parent == NULL){
		root = x;
	}else{
		if(y == y -> parent -> left){
			y -> parent -> left = x;
		}else{
			y -> parent -> right = x;
		}
	}
	//set y as x's right child
	x -> right = y;
	//set x as y's parent
	y -> parent = x;
}

template<class T>
void RBTree<T>::insert(Node<T>* &tree, Node<T> *node){
	Node<T> *temp1 = NULL;
	Node<T> *temp2 = tree;
	
	//step 1 : insert node as binary search tree
	while(temp2 != NULL){
		temp1 = temp2;
		if(node -> key < temp2 -> key){
			temp2 = temp2 -> left;
		}else{
			temp2 = temp2 -> right;
		}
	}
	node -> parent = temp1;
	if(temp1 != NULL){
		if(node -> key < temp1 -> key){
			temp1 -> left = node;
		}else{
			temp1 -> right = node;
		}
	}else{
		root = node;
	}
	
	//step 2 : set node color as RED
	node -> color = RED;
	
	//step 3 : fix up the RBTree
	insertFixUp(tree, node);
}

template<class T>
void RBTree<T>::insertFixUp(Node<T>* &tree, Node<T> *node){
	Node<T> *p, *g;
	while((p = getParent(node))&&(getColor(p) == RED)){
		g = getParent(p);
		if(p == g -> left){
			//case 1 : uncle is RED
			{
				Node<T> *uncle = g -> right;
				if((uncle != NULL) && (getColor(uncle) == RED)){
					setColor(g, RED);
					setColor(p, BLACK);
					setColor(uncle, BLACK);
					node = g;
					continue;
				}
			}
			
			//case 2 : uncle is right child(BLACK)
			if(p -> right == node){
				Node<T> *temp;
				leftRotate(tree, p);
				temp = p;
				p = node;
				node = temp;
			}
			//case 3 : uncle is left child(BLACK)
			setColor(g, RED);
			setColor(p, BLACK);
			rightRotate(tree, g);
			
		}
		else{
			//case 1 : uncle is RED
			{
				Node<T> *uncle = g -> left;
				if(uncle && (getColor(uncle) == RED)){
					setColor(g, RED);
					setColor(p, BLACK);
					setColor(uncle, BLACK);
					node = g;
					continue;
				}
			}
			//case 2 : uncle is left child(BLACK)
			if(p -> left == node){
				Node<T> *temp;
				rightRotate(tree, p);
				temp = p;
				p = node;
				node = temp;
			}
			//case 3 : uncle is right child(BLACK)
			setColor(g, RED);
			setColor(p, BLACK);
			leftRotate(tree, g);
		}		
	}

	//set root as black color
	setColor(root, BLACK);
}

template<class T>
void RBTree<T>::remove(Node<T>* &tree, Node<T> *node){
	Node<T> *chd, *pat;
	Color clr;
	//case 1 : the node has left and right child
	if((node -> left != NULL) && (node -> right != NULL)){
		//use successor to "replace" the node
		Node<T> *rep = node;
		rep = rep -> right;
		while(rep -> left != NULL){
			rep = rep -> left;
		}
		if(getParent(node) != NULL){
			Node<T> *temp = getParent(node);
			if(node == temp -> left){
				temp -> left = rep;
			}
			else{
				temp -> right = rep;
			}
		}else{
			root = node;
		}
		chd = rep -> right;
		pat = getParent(rep);
		clr = getColor(rep);
		if(pat == node){
			pat = rep;
		}else{
			if(chd != NULL){
				setParent(chd, pat);
			}
			rep -> right = node -> right;
			setParent(node -> right, rep);
		}
		rep -> parent = node -> parent;
		rep -> color = node -> color;
		rep -> left = node -> left;
		node -> left -> parent = rep;
		if(clr == BLACK){
			removeFixUp(tree, chd, pat);
		}
		delete node;
		return;
	}
	//case 2 : node has only one child
	if(node -> left != NULL){
		chd = node -> left;
	}else{
		chd = node -> right;
	}
	pat = node -> parent;
	clr = node -> color;
	if(chd != NULL){
		chd -> parent = pat;
	}
	if(pat != NULL){
		if(node == pat -> left){
			pat -> left = chd;
		}else{
			pat -> right = chd;
		}
	}else{
		root = chd;
	}
	if(clr == BLACK){
		removeFixUp(tree, chd, pat);
	}
	//case 3 : nod is leaf node
	delete node;
}

template<class T>
void RBTree<T>::removeFixUp(Node<T>* &tree, Node<T> *node, Node<T> *p){
	Node<T> *temp;
	while(((!node || (getColor(node) == BLACK))) && (node != tree)){
		if(p -> left == node){
			temp = p -> right;
			//case 1 : brother node is RED
			if(getColor(temp) == RED){
				setColor(p, RED);
				setColor(temp, BLACK);
				leftRotate(tree, p);
				temp = p -> right;
			}
			//case 2 : brother node is BLACK
			//case 2.1 both two children are BLACK
			if(((!temp -> left) || (getColor(temp -> left) == BLACK)) && ((!temp -> right) ||(getColor(temp -> right) == BLACK)))
			{
				setColor(temp, RED);
				node = p;
				p = getParent(node);
			}else{
				//case 2.2 left child is RED, right child is BLACK
				if((!temp -> right) || (getColor(node -> right) == BLACK)){
					setColor(temp -> left, BLACK);
					setColor(temp, RED);
					rightRotate(tree, temp);
					temp = p -> right;
				}
				//case 2.3 right child is RED
				setColor(temp, getColor(p));
				setColor(p, BLACK);
				setColor(temp -> right, BLACK);
				leftRotate(tree, p);
				node = tree;
				break;
			}
		}else{
			temp = p -> left;
			//case 1 : brother node is RED
			if(getColor(temp) == RED){
				setColor(p, RED);
				setColor(temp, BLACK);
				rightRotate(tree, p);
				temp = p -> left;
			}
			//case 2 : brother node is BLACK
			//case 2.1 both two children are BLACK
			if(((!temp -> left) || (getColor(temp -> left) == BLACK)) && ((!temp -> right) ||(getColor(temp -> right) == BLACK)))
			{
				setColor(temp, RED);
				node = p;
				p = getParent(node);
			}else{
				//case 2.2 left child is RED, right child is BLACK
				if((!temp -> left) || (getColor(node -> left) == BLACK)){
					setColor(temp -> right, BLACK);
					setColor(temp, RED);
					leftRotate(tree, temp);
					temp = p -> left;
				}
				//case 2.3 right child is RED
				setColor(temp, getColor(p));
				setColor(p, BLACK);
				setColor(temp -> left, BLACK);
				rightRotate(tree, p);
				node = tree;
				break;
			}
		}
	}
	if(node != NULL){
		setColor(node, BLACK);
	}
}

template<class T>
void RBTree<T>::destroy(Node<T>* &tree){
	if(tree == NULL){
		return;
	}
	if(tree -> left != NULL){
		return destroy(tree -> left);
	}
	if(tree -> right != NULL){
		return destroy(tree -> right);
	}
	delete tree;
	tree = NULL;
}

template<class T>
void RBTree<T>::print(Node<T> *node, T value, int direction){
	if(node != NULL){
		if(direction == 0){
			cout << setw(2) << node -> key << " (B) is root " << endl;
		}else{
			cout << setw(2) << node -> key << (getColor(node) == RED ? "(R)" : "(B)") << " is ";
			cout << setw(2) << value << " 's " << setw(12) << (direction == 1 ? " right child " : " left child ") << endl;
		}
		print(node -> left, node -> key, -1);
		print(node -> right, node -> key, 1);
	}
}

#endif
