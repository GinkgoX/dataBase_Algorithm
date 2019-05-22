#include<iostream>
#include<vector>

using namespace std;

//find the max numbers with its bits 
int maxBit(vector<int> input){
	int max_data = input[0];
	for(int i = 1;i < input.size(); i++){
		if(input[i] > max_data){
			max_data = input[i];
		}
	}
	
	int bits_num = 0;
	while(max_data){
		bits_num++;
		max_data/=10;
	}
	return bits_num;
}

//To get the base with d-th bit
int digit(int num, int d){
	int pow = 1;
	while(--d > 0){
		pow*=10;
	}
	return num / pow % 10;
}

vector<int> radixSort(vector<int> input, int n){
	
	//create the temp vector to save the sub-sort data
	vector<int> bucket(n);
	
	//bit counter: to count every bit of the numbers of 0 ~ 9 
	vector<int> count(10);
	
	//circle from low to high
	for(int d = 1;d <= maxBit(input);d++){
		
		//clear the counter
		for(int i = 0; i < 10; i++){
			count[i] = 0;
		}
		
		//sum the numbers of each bucket
		for(int i = 0; i < n; i++){
			count[digit(input[i],d)]++;
		}
		for(int i = 0; i < 10; i++){
			count[i]+=count[i-1];
		}
		for(int i = n -1; i >= 0; i--){
			int k = digit(input[i],d);
			bucket[count[k] - 1] = input[i];
			count[k]--;
		}
		for(int i = 0; i < n; i++){
			input[i] = bucket[i];
		}
	}
	return input;
}

int main(){
	int arr[] = {1,3,24,45,2,66,54,780,670,320,213,543};
	vector<int> test(arr, arr + sizeof(arr)/sizeof(arr[0]));
	cout<<"Beforing Sorting: "<<endl;
	for(int i= 0; i < test.size(); i++){
		cout<<test[i]<<" ";
	}
	cout<<endl;
	
	vector<int> result;
	result = test;
	result = radixSort(result, result.size());
	cout<<"After Sorting: "<<endl;
	for(int i = 0; i < result.size(); i++){
		cout<<result[i]<<" ";
	}
	cout<<endl;
	return 0;
}



