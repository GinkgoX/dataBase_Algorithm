#include<iostream>
#include<assert.h>
#include "list.h"

using namespace std;

int main(){
	int array[7] = {3, 4, 2, 6, 5, 1, 7};
	List<int> list;
	for(int i = 0; i < 7; i++){
		list.pushBack(array[i]);
	}
	cout << "The List result : ***************" << endl;
	list.print();
	cout << "The List reverse : **************" << endl;
	list.reverse();
	list.print();
	cout << "the List copy : *****************" << endl;
	List<int> temp = list;
	temp.print();
	cout << "the List popFront : *************" << endl;
	temp.popFront();
	temp.print();
	cout << "the List popBack: ***************" << endl;
	temp.popBack();
	temp.print();
	cout << "the List insert : ***************" << endl;
	list.insert(list.find(2), 4);
	list.print();
	cout << "the List erase : ****************" << endl;
	list.erase(list.find(1));
	list.print();
	cout << "The list remove : ***************" << endl;
	list.remove(2);
	list.print();
	cout << "the List count : ****************" << endl;
	cout << "the list contains " << list.count() << " elements" << endl;
	cout << "done " << endl;
	return 0;
}










