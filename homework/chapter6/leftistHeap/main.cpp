#include<iostream>
#include"heap.h"

using namespace std;

int main(){
	int arr1[8] = {3, 10, 8, 21, 14, 17, 23, 26};
	int arr2[8] = {6, 12, 7, 18, 24, 37, 18, 33};
	LeftistHeap<int> *h1 = new LeftistHeap<int>();
	LeftistHeap<int> *h2 = new LeftistHeap<int>();
	
	cout << "********* insert ************" << endl;
	for(int i = 0; i < 8; i++){
		h1 -> insert(arr1[i]);
		h2 -> insert(arr2[i]);
	}
	
	cout << "********* print ************" << endl;
	cout << " the info in h1 as follows : " << endl;
	h1 -> print();
	cout << " the info in h2 as follows : " << endl;
	h2 -> print();
	
	cout << "********* merge ************" << endl;
	h1 -> merge(*h2);
	h1 -> print();
	
	cout << "********* deleteMin ************" << endl;
	int minItem;
	h1 -> deleteMin(minItem);
	cout << " the minmum value in h1 is " << minItem << endl;
	
	cout << " done ." << endl;
	return 0;
}

