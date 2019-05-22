#include<iostream>
#include"splay.h"

using namespace std;

int main()
{
	Splay<int> *splay = new Splay<int>();
	int arr[6] = {10, 50, 40, 30, 20, 60};
	
	cout << "*********** insert **************" << endl;
	for(int i = 0; i < 6; i++){
		splay -> insert(arr[i]);
	}
	
	cout << "*********** print **************" << endl;
	splay -> print();
	cout << endl;
	
	cout << "*********** preOrder **************" << endl;
	splay -> preOrder();
	cout << endl;
	
	cout << "*********** inOrder **************" << endl;
	splay -> inOrder();
	cout << endl;
	
	cout << "*********** postOrder **************" << endl;
	splay -> postOrder();
	cout << endl;
	
	cout << " the maximum value in Splay is " << splay -> max() << endl;
	cout << " the minimum value in Splay is " << splay -> min() << endl;
	
	cout << "*********** insert **************" << endl;
	splay -> insert(35);
	splay -> inOrder();
	cout << endl;
	splay -> print();
	
	cout << "*********** remove **************" << endl;
	splay -> remove(50);
	splay -> inOrder();
	cout << endl;
	splay -> print();
	
	cout << "*********** destroy **************" << endl;
	splay -> destroy();
	
	cout << "done ." << endl;
	
	return 0;
}

