#include<iostream>
#include<vector>

using namespace std;

vector<int> shellSort(vector<int> list){
	vector<int> result = list;
	int n = result.size();
	for(int gap = n>>1; gap > 0;gap>>=1){
		for(int i = gap;i < n;i++){
			int temp = result[i];
			int j = i - gap;
			while(j >= 0 && result[j] > temp){
				result[j + gap] = result[j];
				j -= gap;
			}
			result[j + gap] = temp;
		}
		for(int i = 0;i < result.size();i++){
			cout<<result[i]<<" ";
		}
		cout<<endl;
	}
	return result;
}

int main(){
	int arr[] = {6,8,2,5,3,1,7,4,9,12,42,13,23,15};
	vector<int> test(arr, arr+sizeof(arr)/sizeof(arr[0]));
	cout<<"Before::"<<endl;
	for(int i = 0;i < test.size();i++){
			cout<<test[i]<<" ";
		}
		cout<<endl;
	vector<int> result;
	result = shellSort(test);
	cout<<"After::"<<endl;
	for(int i = 0;i < result.size();i++){
			cout<<result[i]<<" ";
		}
		cout<<endl;
	return 0;
}














