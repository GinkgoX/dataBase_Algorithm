#include<iostream>
#include"avl.h"

using namespace std;

int main()
{
	int arr[16] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
	AVL<int> *avl = new AVL<int>();
	cout << " *********** insert ************** " << endl;
	for(int i = 0; i < 16; i++)
	{
		cout << arr[i] << " ";
		avl -> insert(arr[i]);
	}
	cout << endl;
	
	cout << " *********** print ************** " << endl;
	avl -> print();
	cout << endl;
	
	cout << " *********** preOrder ************** " << endl;
	avl -> preOrder();
	cout << endl;
	
	cout << " *********** inOrder ************** " << endl;
	avl -> inOrder();
	cout << endl;
	
	cout << " *********** postOrder ************** " << endl;
	avl -> postOrder();
	cout << endl;
	
	cout << " *********** height ************** " << endl;
	cout << " the height is " << avl -> getHeight() << endl;
	
	cout << " *********** maximum ************** " << endl;
	cout << " the maximum value is " << avl -> max() << endl;
	
	cout << " *********** minimum ************** " << endl;
	cout << " the minimum  value is " << avl -> min() << endl;
	
	cout << " *********** remove ************** " << endl;
	avl -> remove(8);
	avl -> inOrder();
	cout << endl;
		
	return 0;
}
