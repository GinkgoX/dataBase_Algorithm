#include<iostream>
#include<vector>

using namespace std;
vector<int> insertSort(vector<int> list){
	vector<int> result;
	if(list.empty()){
		return result;
	}
	result = list;
	for(int i = 1;i < result.size();i++){
		int temp = result[i];
		int j = i-1;
		for(j;j >= 0 && result[j]> temp;j--){
			result[j+1] = result[j];
		}
		result[j+1] = temp;
	}
	return result;
}

int main(){
	int arr[] = {6,4,8,9,2,3,1};
	vector<int> test(arr,arr+sizeof(arr)/sizeof(arr[0]));
	cout<<"Before Sorting"<<endl;
	for(int i = 0;i < test.size();i++){
		cout<<test[i]<<" ";
	}
	cout<<endl;
	vector<int> result;
	result = insertSort(test);
	cout<<"After Sorting"<<endl;
	for(int i = 0; i < result.size();i++){
		cout<<result[i]<<" ";
	}
	cout<<endl;
	return 0;
}









