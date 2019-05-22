#include<iostream>
#include<vector>

using namespace std;

vector<int>selectSort(vector<int>list){
	vector<int> result = list;
	for(int i = 0; i < result.size(); i++){
		int index = i;
		for(int j = i + 1;j < result.size(); j++){
			if(result[index] > result[j]){
				index = j;
			}
		}
		swap(result[i],result[index]);
		cout<<i+1<<"th result : ";
		for(int i = 0; i < result.size(); i++){
			cout<<result[i]<<" ";
		}
		cout<<endl;
	}
	return result;
}

int main(){
	int arr[] = {2,4,5,3,1,8,7,9,6};
	vector<int> test(arr,arr+sizeof(arr)/sizeof(arr[0]));
	cout<<"Before Sorting : ";
	for(int i = 0; i < test.size(); i++){
		cout<<test[i]<<" ";
	}
	cout<<endl;
	vector<int> result;
	result = selectSort(test);
	cout<<"After Sorting : ";
	for(int i = 0; i < result.size(); i++){
		cout<<result[i]<<" ";
	}
	cout<<endl;

	return 0;
}
















