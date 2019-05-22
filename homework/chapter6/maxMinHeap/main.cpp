#include<iostream>
#include"heap.h"

using namespace std;

int main(){
	int arr[] = {13, 21, 16, 24, 31, 19, 68, 65, 26, 32};
	int n = sizeof(arr)/ sizeof(arr[0]);
	Heap<int> *heap = new Heap<int>();
	
	cout << "********** insert **********" << endl;
	for(int i = 0; i < n; i++){
		heap -> insert(arr[i]);
	}
	
	cout << "********** print **********" << endl;
	heap -> print();
	
	cout << "********** insert(14) **********" << endl;
	heap -> insert(14);
	heap -> print();
	
	cout << "********** remove(13) **********" << endl;
	heap -> remove(13);
	heap -> print();
	cout << "done ." << endl;
	return 0;
}

