#include<iostream>
#include"tree.h"

using namespace std;

int main()
{
	int arr[8] = {5, 3, 2, 7, 4, 8, 1, 6};
	Tree<int> *tree = new Tree<int>();
	cout << "******* insert *******" << endl;
	for(int i = 0; i < 8; i++)
	{
		tree -> insert(arr[i]);
	}
	cout << "******* print *******" << endl;
	tree -> print();
	
	cout << "******* preOrder *******" << endl;
	tree -> preOrder();
	cout << endl;
	
	cout << "******* inOrder *******" << endl;
	tree -> inOrder();
	cout << endl;
	
	cout << "******* postOrder *******" << endl;
	tree -> postOrder();
	cout << endl;
	
	cout << "******* min *******" << endl;
	cout << "the min data in Tree is " << tree -> min() << endl;
	
	cout << "******* max *******" << endl;
	cout << "the max data in Tree is " << tree -> max() << endl;
	
	cout << "******* remove *******" << endl;
	tree -> remove(4);
	
	cout << "******* inOrder *******" << endl;
	tree -> inOrder();
	cout << endl;
	
	cout << "******* destroy *******" << endl;
	tree -> destroy();
	
	cout << "done " << endl;
	return 0;
}

