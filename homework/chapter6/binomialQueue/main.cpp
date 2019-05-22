#include<iostream>
#include"queue.h"

using namespace std;

int main(){
	int arr1[6] = {16, 18, 12, 21, 24, 65};
	int arr2[7] = {13, 14, 26, 23, 51, 24, 65};
	BinomialQueue<int> bqueue1(10);
	BinomialQueue<int> bqueue2(10);
	
	cout << "******* insert ********" << endl;
	for(int i = 0; i < 6; i++){
		bqueue1.insert(arr1[i]);
		bqueue2.insert(arr2[i]);
	}
	bqueue2.insert(arr2[6]);
	
	cout << "******* Display ********" << endl;
	cout << " bqueue1 info " << endl;
	bqueue1.print();
	cout << " bqueue2 info " << endl;
	bqueue2.print();
	
	cout << "******* merge ********" << endl;
	bqueue1.merge(bqueue2);
	cout << " bqueue1 info " << endl;
	bqueue1.print();
	
	cout << "******* DeleteMin ********" << endl;
	cout << "the minItem in queue is " << bqueue1.deleteMin() << endl;
	bqueue1.print();
	cout << "the second minItem in queue is " << bqueue1.deleteMin() << endl;
	cout << "the thrid minItem in queue is " << bqueue1.deleteMin() << endl;
	
	cout << "******* MakeEmpty ********" << endl;
	bqueue1.makeEmpty();
	
	cout << " done . " << endl;
	return 0;
}
