#include<iostream>
#include"rbtree.h"

using namespace std;

int main(){
	RBTree<int> *rbtree = new RBTree<int>();
	int arr[18] = {20, 30, 40, 10, 50, 60, 1, 5, 6, 4, 3, 2, 22, 44, 11, 66, 55, 33};
	cout << " ********* insert ********** " << endl;
	for(int i = 0; i < 18; i++){
		rbtree -> insert(arr[i]);
	}
	
	cout << " ********* print ********** " << endl;
	rbtree -> print();
	cout << endl;
	
	cout << " ********* preOrder ********** " << endl;
	rbtree -> preOrder();
	cout << endl;
	
	cout << " ********* inOrder ********** " << endl;
	rbtree -> inOrder();
	cout << endl;
	
	cout << " ********* postOrder ********** " << endl;
	rbtree -> postOrder();
	cout << endl;
	
	cout << " the maxmium value in RBTree is " << rbtree -> max() << endl;
	cout << " the minimum value in RBTree is " << rbtree -> min() << endl;
	
	cout << " ********* remove (66) ********** " << endl;
	rbtree -> remove(66);
	rbtree -> print();
	rbtree -> inOrder();
	cout << endl;
	
	cout << " ********* remove (11) ********** " << endl;
	rbtree -> remove(11);
	rbtree -> print();
	rbtree -> inOrder();
	cout << endl;
	
	cout << " ********* destroy ********** " << endl;
	rbtree -> destroy();
	cout << " RBTree -- has been destroyed !" << endl;
	
	cout << " done ." << endl;
	return 0;
}
