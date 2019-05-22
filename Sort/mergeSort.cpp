#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int> &input, int left, int mid, int right, vector<int> temp){
	int i = left;
	int j = mid + 1;
	int k = 0;
	
	while(i <= mid && j <= right){
		if(input[i] <= input[j]){
			temp[k++] = input[i++];
		}
		else{
			temp[k++] = input[j++];
		}
	}
	
	while(i <= mid){
		temp[k++] = input[i++];
	}
	
	while(j <= right){
		temp[k++] = input[j++];
	}
	
	k = 0;
	
	while(left <= right){
		input[left++] = temp[k++];
	}
}

void mergeSub(vector<int> &input, int left, int right, vector<int> temp){
	if(left < right){
	int mid = (right + left) >> 1;
	mergeSub(input, left, mid, temp);
	mergeSub(input, mid + 1, right, temp);
	merge(input, left, mid, right, temp);
	}
}

void mergeSort(vector<int> &input){
	vector<int> temp(input.size());
	//init a space for frequency calling the space;
	mergeSub(input, 0, input.size() - 1, temp);
}

int main(){
	int arr[] = {3,7,4,5,1,8,2,9,6};
	vector<int> test(arr, arr + sizeof(arr)/sizeof(arr[0]));
	cout<<"Before Sorting : ";
	for(int i = 0; i < test.size(); i++){
		cout<<test[i]<<" ";
	}
	cout<<endl;
	vector<int> result;
	result = test;
	mergeSort(result);
	cout<<"After Sorting : ";
	for(int i = 0; i < result.size(); i++){
		cout<<result[i]<<" ";
	}
	cout<<endl;
	return 0;
}



