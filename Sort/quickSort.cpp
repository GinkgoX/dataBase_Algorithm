#include<iostream>
#include<vector>

using namespace std;

int division(vector <int>&list, int left,int right){
	int base = list[left]; //set the left as base;
	while(left < right){
		// right turns to left operation:
		while(left < right && list[right] >= base){
			right--;
		}
		// find the element which is smaller then base, place it to left;
			list[left] = list[right];
		// left turns to right operation:
		while(left < right && list[left] <= base){
			left ++;
		}
		// find the elemnet which is greater than base, place it to right;
			list[right] = list[left];
	}
	// update the base value;
	list[left] = base;
	return left;
}

void quickSort(vector<int>&list, int left, int right){
	if(left < right){
		// obtain the updated base;
		int base = division(list, left, right);
		// sort the left part;
		quickSort(list,left, base -1);
		// sort the right part;
		quickSort(list,base+1, right); 
	}
}

int main(){
	int arr[] = {2,4,5,3,7,9,8,1,6};
	vector<int> test(arr,arr+sizeof(arr)/sizeof(arr[0]));
	cout<<"Before"<<endl;
	for(int i = 0;i < test.size(); i++){
		cout<<test[i]<<" ";
	}
	cout<<endl;
	vector<int> result =test;
	quickSort(result,0,result.size()-1);
	cout<<"After"<<endl;
	for(int i = 0; i < result.size(); i++){
		cout<<result[i]<<" ";
	}
	cout<<endl;
	return 0;
}























