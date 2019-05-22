#ifndef TREE_H_
#define TREE_H_

#include <iomanip>
#include<iostream>

using namespace std;

template<class dataType>
struct Node{
	dataType data;
	Node<dataType> *left;
	Node<dataType> *right;
	Node<dataType> *parent;
	Node(dataType &d, Node<dataType> *l, Node<dataType> *r, Node<dataType> *p):data(d), left(l), right(r), parent(p){};
};

template<class dataType>
class Tree{
private:
	Node<dataType> *root;
public:
	Tree():root(NULL){};
	~Tree()
	{
		destroy();
	};
	void preOrder()
	{	
		preOrder(root);
	};
	void inOrder()
	{
		inOrder(root);
	};
	void postOrder()
	{
		postOrder(root);
	};
	Node<dataType>* search(dataType d)
	{
		search(root, d);
	};
	Node<dataType>* iterativeSearch(dataType d)
	{
		iterativeSearch(root, d);
	}
	dataType min()
	{
		Node<dataType> *node = min(root);
		if(node != NULL)
		{
			return node -> data;
		}
		return (dataType)NULL;
	};
	
	dataType max()
	{
		Node<dataType> *node = max(root);
		if(node != NULL)
		{
			return node -> data;
		}
		return (dataType)NULL;
	};
	
	//successor : min node bigger than the given node
	Node<dataType>* successor(Node<dataType> *node)
	{
		//if node has right child, successor is the min node bigger than given node itself
		if(node -> right != NULL)
		{
			return min(node -> right);
		}
		//if not, case 1 node is left child, successor is the parent node
		Node<dataType> *temp = node -> parent;
		//case 2 : node is right child, successor is the lowest parent node
		while(temp != NULL && node == temp -> right)
		{
			node = temp;
			temp = temp -> parent;
		}
		return temp;
	};
	
	//presuccessor : max node less than the given node
	Node<dataType>* presuccessor(Node<dataType> *node)
	{
		//if node has left child, presuccessor is the max node in given node
		if(node -> left != NULL)
		{
			return max(node -> left);
		}
		//if not, #1 node is right child, presuccessor is the parent node, #2 presuccessor the lowest parent node
		Node<dataType> *temp = node -> parent;
		while(temp != NULL && node == temp -> left)
		{
			node = temp;
			temp = temp -> parent;
		} 
		return temp;
	};
	
	void insert(dataType d)
	{
		Node<dataType> *temp = NULL;
		if((temp = new Node<dataType>(d, NULL, NULL, NULL)) == NULL)
		{
			return;
		}
		insert(root, temp);
	};
	void remove(dataType d)
	{
		Node<dataType> *temp, *node;
		//judge whether d is in the Tree
		if(((temp = search(root, d))) != NULL)
		{
			if((node = remove(root, temp)) != NULL)
			{
				delete node;
			}
		}
		
	};
	void destroy()
	{
		destroy(root);
	};
	void print()
	{
		if(root != NULL)
		{
			print(root, root -> data, 0);
		}
	};
private:
	void preOrder(Node<dataType> *node) const;
	void inOrder(Node<dataType> *node) const;
	void postOrder(Node<dataType> *node) const;
	Node<dataType>* search(Node<dataType> *node, dataType d) const;
	Node<dataType>* iterativeSearch(Node<dataType> *node, dataType d) const;
	Node<dataType>* min(Node<dataType> *node);
	Node<dataType>* max(Node<dataType> *node);
	void insert(Node<dataType>* &node, Node<dataType> *d);
	Node<dataType>* remove(Node<dataType>* &node, Node<dataType> *d);
	void destroy(Node<dataType>* &node);
	void print(Node<dataType> *node, dataType d, int direction);
};

//preOrder : root -> left -> right
template<class dataType>
void Tree<dataType>::preOrder(Node<dataType> *node) const
{
	if(node != NULL)
	{
		cout << node -> data << " ";
		preOrder(node -> left);
		preOrder(node -> right);
	}
}

//inOrder : left -> root -> right
template<class dataType>
void Tree<dataType>::inOrder(Node<dataType> *node) const
{
	if(node != NULL)
	{
		inOrder(node -> left);
		cout << node -> data << " ";
		inOrder(node -> right);
	}
}

//postOrder : left -> right -> root
template<class dataType>
void Tree<dataType>::postOrder(Node<dataType> *node) const
{
	if(node != NULL)
	{
		postOrder(node -> left);
		postOrder(node -> right);
		cout << node -> data << " ";
	}
}

//binary search without iteration
template<class dataType>
Node<dataType>* Tree<dataType>::search(Node<dataType> *node, dataType d) const
{
	if(node == NULL || node -> data == d)
	{
		return node;
	}
	if(d < node -> data)
	{
		search(node -> left, d);
	}
	else
	{
		search(node -> right, d);
	}
}


//binary search with iteration
template<class dataType>
Node<dataType>* Tree<dataType>::iterativeSearch(Node<dataType> *node, dataType d) const
{
	while((node != NULL) && (node -> data != d))
	{
		if(d < node -> data)
		{
			iterativeSearch(node -> left, d);
		}
		else
		{
			iterativeSearch(node -> right, d);
		}
	}
	return node;
}

//find the minimum node in Tree (left -> .. -> left)
template<class dataType>
Node<dataType>* Tree<dataType>::min(Node<dataType> *node)
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

//find the maxmium node in Tree (right -> ... -> right)
template<class dataType>
Node<dataType>* Tree<dataType>::max(Node<dataType> *node)
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

//insert data into Tree
template<class dataType>
void Tree<dataType>::insert(Node<dataType>* &node, Node<dataType> *d)
{
	Node<dataType> *temp = NULL;
	Node<dataType> *n = node;
	//judge the position of d
	while(n != NULL)
	{
		temp = n;
		//update left part if d < temp
		if(d -> data < temp -> data)
		{
			n = n -> left;
		}
		//update right part if d > temp
		else
		{
			n = n -> right;
		}
	}
	//insert node		
	d -> parent = temp;
	if(temp == NULL)
	{
		node = d;
	}
	else if(d -> data < temp -> data)
	{
		temp -> left = d;
	}
	else
	{
		temp -> right = d;
	}
}

//remove node d from node
template<class dataType>
Node<dataType>* Tree<dataType>::remove(Node<dataType>* &node, Node<dataType> *d)
{
	Node<dataType> *temp1 = NULL;
	Node<dataType> *temp2 = NULL;
	if((d -> left == NULL) || (d -> right == NULL))
	{
		temp2 = d;
	}
	else
	{
		temp2 = successor(d);
	}
	if(temp2 -> left != NULL)
	{
		temp1 = temp2 -> left;
	}
	else
	{
		temp1 = temp2 -> right;
	}
	if(temp1 != NULL)
	{
		temp1 -> parent = temp2 -> parent;
	}
	if(temp2 -> parent == NULL)
	{
		node = temp1;
	}
	else if(temp2 == temp2 -> parent -> left)
	{
		temp2 -> parent -> left = temp1;
	}
	else
	{
		temp2 -> parent -> right = temp1;
	}
	if(temp2 != d)
	{
		d -> data = temp2 -> data;
	}
	return temp2;
}

//destroy the Tree
template<class dataType>
void Tree<dataType>::destroy(Node<dataType>* &node)
{
	if(node == NULL)
	{
		return;
	}
	if(node -> left != NULL)
	{
		destroy(node -> left);
	}
	if(node -> right != NULL)
	{
		destroy(node -> right);
	}
	delete node;
	node = NULL;
}

//print the Tree structure
template<class dataType>
void Tree<dataType>::print(Node<dataType> *node, dataType d, int direction)
{
	if(node != NULL)
	{
		//root : direction = 0
		if(direction == 0)
		{
			cout << setw(2) << node -> data << " is root " << endl;	
		}
		else
		{
			cout << setw(2) << node -> data << " is " << d << " 's " << setw(12) << (direction == 1 ? " right child " : " left child ") << endl;
		}
		// left : direction = -1
		print(node -> left, node -> data, -1);
		//right : direction = 1
		print(node -> right, node -> data, 1);
	}
}

#endif

