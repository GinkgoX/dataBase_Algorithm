#include<iostream>
#include<vector>

using namespace std;

void heapAdjust(vector<int>&list, int parent, int length){
	int temp = list[parent];
	int child = 2*parent + 1;
	while(child < length){
		//judege if there is right child and right is bigger than left child, then choise the right child as the root node.
		if(child + 1 < length && list[child] < list[child + 1]){
			child ++;
		}
		//judege if the parent node is bigger than right child, if not change them.
		if(temp >= list[child]){
			break;
		}
		//swap the parent node and child node, meanwhile refresh the parent and child node
		list[parent] = list[child];
		
		parent = child;
		
		child = 2*parent + 1; 
	}
	list[parent] = temp;
}

vector<int> heapSort(vector<int> list){
	int length = list.size();
	//adjust the parent and child node
	for(int i = length/2;i >= 0; i--){
		heapAdjust(list, i, length);
	}
	//place the bigest one at the end
	for(int i = length - 1; i > 0; i--){
		int temp = list[i];
		list[i] = list[0];
		list[0] = temp;
		//refresh the rest heap 
		heapAdjust(list, 0, i);
		
		cout<<length - i<<"th sort result : "<<endl;
		for(int i = 0; i < list.size(); i++){
			cout<<list[i]<<" ";
		}
		cout<<endl;
	}
	return list;
}

int main(){
	int arr[] = {2,4,3,6,1,9,8,7,5};
	vector<int> test(arr, arr + sizeof(arr)/sizeof(arr[0]));
	cout<<"Before Sorting : ";
	for(int i = 0; i < test.size(); i++){
		cout<<test[i]<<" ";
	}
	cout<<endl;
	vector<int> result;
	result = heapSort(test);
	cout<<"After Sorting : "<<endl;
	for(int i = 0; i < result.size(); i++){
		cout<<result[i]<<" ";
	}
	cout<<endl;
	return 0;
}








