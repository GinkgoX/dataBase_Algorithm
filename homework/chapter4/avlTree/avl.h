#ifndef AVL_H_
#define AVL_H_

#include<iostream>
#include<iomanip>

using std::cout;
using std::endl;
using std::setw;
template<class T>
struct Node{
	T data;
	int height;
	Node<T> *left;
	Node<T> *right;
	Node(T d, Node<T> *l, Node<T> *r):data(d), height(0), left(l), right(r)
	{
	
	};
};

template<class T>
class AVL{
private:
	Node<T> *root;
public:
	//AVL structor
	AVL():root(NULL)
	{
		
	};
	//AVL destrctor
	~AVL()
	{
		destory(root);
	};
	
	//get height
	int getHeight()
	{
		return getHeight(root);
	};
	
	//preOrder : parent -> left -> right
	void preOrder()
	{
		preOrder(root);
	};
	
	//inOrder : left -> parent -> right
	void inOrder()
	{
		inOrder(root);
	};
	
	//postOrder : left -> right -> parent
	void postOrder()
	{
		postOrder(root);
	};
	
	//search value's node
	Node<T>* search(T value)
	{
		return search(root, value);
	};
	
	//iterative search value's node
	Node<T>* iterativeSearch(T value)
	{
		return iterativeSearch(root, value);
	};	
	
	//find minimum value
	T min()
	{
		Node<T>* temp = min(root);
		if(temp != NULL)
		{
			return temp -> data;
		}
		return (T)NULL;
	};
	
	//find maximum value
	T max()
	{
		Node<T> *temp = max(root);
		if(temp != NULL)
		{
			return temp -> data;
		}
		return (T)NULL;
	}
	
	//insert value
	void insert(T value)
	{
		insert(root, value);
	};
	
	//remove value
	void remove(T value)
	{
		Node<T> *temp;
		if((temp = search(root, value)) != NULL)
		{
			root = remove(root, temp);
		}
	};
	
	//destory AVL
	void destory()
	{
		destory(root);
	};
	
	//print AVL
	void print()
	{
		if(root != NULL)
		{
			print(root, root -> data, 0);
		}
	};
private:
	int getHeight(Node<T> *node);
	void preOrder(Node<T> *node) const;
	void inOrder(Node<T> *node) const;
	void postOrder(Node<T> *node) const;
	Node<T>* search(Node<T> *node, T value) const;
	Node<T>* iterativeSearch(Node<T> *node, T value) const;
	Node<T>* min(Node<T> *node);
	Node<T>* max(Node<T> *node);
	Node<T>* leftLeftRotation(Node<T> *k2);
	Node<T>* rightRightRotation(Node<T> *k1);
	Node<T>* leftRightRotation(Node<T> *k3);
	Node<T>* rightLeftRotation(Node<T> *k1);
	Node<T>* insert(Node<T>* &node, T value);
	Node<T>* remove(Node<T>* &node, Node<T>* n);
	void destory(Node<T>* &node);
	void print(Node<T> *node, T value, int direction);	
};

template<class T>
int AVL<T>::getHeight(Node<T> *node)
{
	if(node != NULL)
	{
		return node -> height;
	}
	return 0;
}

template<class T>
void AVL<T>::preOrder(Node<T> *node) const
{
	if(node != NULL)
	{
		cout << node -> data << " ";
		preOrder(node -> left);
		preOrder(node -> right);
	}
}

template<class T>
void AVL<T>::inOrder(Node<T> *node) const
{
	if(node != NULL)
	{
		inOrder(node -> left);
		cout << node -> data << " ";
		inOrder(node -> right);
	}
}

template<class T>
void AVL<T>::postOrder(Node<T> *node) const
{
	if(node != NULL)
	{
		postOrder(node -> left);
		postOrder(node -> right);
		cout << node -> data << " ";
	}
}

template<class T>
Node<T>* AVL<T>::search(Node<T> *node, T value) const
{
	if(node == NULL || node -> data == value)
	{
		return node;
	}
	if(value < node -> data)
	{
		search(node -> left, value);
	}
	else
	{
		search(node -> right, value);
	}
}

template<class T>
Node<T>* AVL<T>::iterativeSearch(Node<T> *node, T value) const
{
	while((node != NULL)&&(node -> data != value))
	{
		if(value < node -> data)
		{
			node = node -> left;
		}
		else
		{
			node = node -> right;
		}
	}
	return node;
}

template<class T>
Node<T>* AVL<T>::min(Node<T> *node)
{
	if(node == NULL)
	{
		return node;
	}
	while(node -> left != NULL)
	{
		node = node -> left;
	}
	return node;
}

template<class T>
Node<T>* AVL<T>::max(Node<T> *node)
{
	if(node == NULL)
	{
		return node;
	}
	while(node -> right != NULL)
	{
		node = node -> right;
	}
	return node;
}

//LL argorithm
template<class T>
Node<T>* AVL<T>::leftLeftRotation(Node<T> *k2)
{
	Node<T> *k1;
	k1 = k2 -> left;
	k2 -> left = k1 -> right;
	k1 -> right = k2;
	k2 -> height = 1 + (getHeight(k2 -> left) > getHeight(k2 -> right) ? getHeight(k2 -> left) : getHeight(k2 -> right));
	k1 -> height = 1 + (getHeight(k1 -> left) > getHeight(k1 -> right) ? getHeight(k1 -> left) : getHeight(k1 -> right));
	return k1;
}


//RR argorithm
template<class T>
Node<T>* AVL<T>::rightRightRotation(Node<T> *k1)
{
	Node<T> *k2;
	k2 = k1 -> right;
	k1 -> right = k2 -> left;
	k2 -> left = k1;
	k2 -> height = 1 + (getHeight(k2 -> left) > getHeight(k2 -> right) ? getHeight(k2 -> left) : getHeight(k2 -> right));
	k1 -> height = 1 + (getHeight(k1 -> left) > getHeight(k1 -> right) ? getHeight(k1 -> left) : getHeight(k1 -> right));
	return k2;
}

//LR argorithm
template<class T>
Node<T>* AVL<T>::leftRightRotation(Node<T> *k3)
{
	k3 -> left = rightRightRotation(k3 -> left);
	return leftLeftRotation(k3);
}

//RL argorithm
template<class T>
Node<T>* AVL<T>::rightLeftRotation(Node<T> *k1)
{
	k1 -> right = leftLeftRotation(k1 -> right);
	return rightRightRotation(k1);
}


//insert value into node
template<class T>
Node<T>* AVL<T>::insert(Node<T>* &node, T value)
{
	if(node == NULL)
	{
		//create new node
		cout << " create new node" << endl;
		node = new Node<T>(value, NULL, NULL);
		if(node == NULL)
		{
			cout << " failed to create avltree !" << endl;
			return NULL;
		}
	}
	//insert value into left part
	else if(value < node -> data)
	{
		node -> left = insert(node -> left, value);
		//judge whether it destoryes the AVL tree
		if(getHeight(node -> left) - getHeight(node -> right) == 2)
		{	
			//insert value into left left positorn
			if(value < node -> left -> data)
			{
				node = leftLeftRotation(node);
			}
			//insert value into left right positorn
			else
			{
				node = leftRightRotation(node);
			}
		}
	}
	//insert value into right part
	else if(value > node -> data)
	{
		node -> right = insert(node -> right, value);
		//judge whether it destoryes the AVL tree
		if(getHeight(node -> right) - getHeight(node -> left) == 2)
		{
			//insert value into right right positorn
			if(value > node -> right -> data)
			{
				node = rightRightRotation(node);
			}
			//insert value into right left positorn
			else
			{
				node = rightLeftRotation(node);
			}
		}
	}
	else
	{
		cout << "failed to insert the value, since it has existed !" << endl;
	}
	int deeper = getHeight(node -> left) > getHeight(node -> right) ? getHeight(node -> left) : getHeight(node -> right);
	node -> height = 1 + deeper;
	return node;
}

template<class T>
Node<T>* AVL<T>::remove(Node<T>* &node, Node<T> *n)
{
	if(node == NULL || n == NULL)
	{
		return NULL;
	}
	//remove data form the left part
	if(n -> data < node -> data)
	{
		node -> left = remove(node -> left, n);
		//judge whether it destoryes the AVL tree
		if(getHeight(node -> right) - getHeight(node -> left) == 2)
		{
			Node<T> *temp = node -> right;
			//remove data from right left positorn
			if(getHeight(temp -> left) > getHeight(temp -> right))
			{
				node = rightLeftRotation(node);
			}
			//remove data from right right positorn
			else
			{
				node = rightRightRotation(node);
			}
		}
	}
	//remove data from right part
	else if(n -> data > node -> data)
	{
		node -> right = remove(node -> right, n);
		//judge whether it destoryes the AVL tree
		if(getHeight(node -> left) - getHeight(node -> right) == 2)
		{
			Node<T> *temp = node -> left;
			//remove data from left right positorn
			if(getHeight(temp -> right) > getHeight(temp -> left))
			{
				node = leftRightRotation(node);
			}
			//remove data from left left positorn
			else
			{
				node = leftLeftRotation(node);
			}
		}
	}
	//remove the (same one) data in AVL
	else
	{
		//the node is not null
		if((node -> left != NULL) && (node -> right != NULL))
		{
			//find the successor
			if(getHeight(node -> left) > getHeight(node -> right))
			{
				Node<T>* maximum = max(node -> left);
				node -> data = maximum -> data;
				node -> left = remove(node -> left, maximum);
			}
			//find the presucessor
			else
			{
				Node<T> *minimum = min(node -> right);
				node -> data = minimum -> data;
				node -> right = remove(node -> right, minimum);
			}
		
		}
		else
		{
			Node<T> *temp = node;
			node = (node -> left != NULL) ? node -> left : node -> right;
			delete temp;
		}
	}
	return node;
}

template<class T>
void AVL<T>::destory(Node<T>* &node)
{
	if(node == NULL)
	{
		return;
	}
	while(node -> left != NULL)
	{
		destory(node -> left);
	}
	while(node -> right != NULL)
	{
		destory(node -> right);
	}
	delete node;
}

template<class T>
void AVL<T>::print(Node<T> *node, T value, int direction)
{
	if(node != NULL)
	{
		if(direction == 0)
		{
			cout << setw(2) << node -> data << " is root " << endl; 
		}
		else
		{
			cout << setw(2) << node -> data << " is " << setw(2) << value << " 's "  << setw(12) << (direction == 1 ? " right child " : " left child ") << endl;
		}
		print(node -> left, node -> data, -1);
		print(node -> right, node -> data, 1);
	}
}	

#endif

