#include<iostream>
#include"heap.h"

using namespace std;

int main(){
	int arr[] = {13, 21, 16, 24, 31, 19, 68, 65, 26, 32, 5};
	vector<int> v;
	int n = sizeof(arr)/ sizeof(arr[0]);
	for(int i = 0; i < n; i++){
		v.push_back(arr[i]);
	}
	Heap<int> heap;
	cout << "********** insert **********" << endl;
	for(int i = 0; i < n; i++){
		heap.insert(v[i]);
	}
	cout << "********** print **********" << endl;
	heap.print();
	
	cout << "********** findMin **********" << endl;
	cout << "the minimum item is " << heap.findMin() << endl;
	
	cout << "********** deleteMin **********" << endl;
	heap.deleteMin();
	heap.print();
	
	cout << "********** insert(14) **********" << endl;
	heap.insert(14);
	heap.print();
	cout << "done ." << endl;
	return 0;
}

