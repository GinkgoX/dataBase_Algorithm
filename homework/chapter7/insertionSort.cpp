#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<class Compareable>
void inserationSort(vector<Compareable> &v){
	int j;
	//traverse the vector
	for(int p  = 1; p < v.size(); p++){
		Compareable temp = v[p];
		//find the proper location
		for(j = p; j > 0 && temp < v[j - 1]; j--){
			v[j] = v[j - 1];
		}
		//insert into proper location
		v[j] = temp;
	}
}

int main(){
	int arr[] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15};
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> v;
	for(int i = 0 ; i < len; i++){
		v.push_back(arr[i]);
	}
	
	cout << "******* the original data ***********" << endl;
	for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
	}
	cout << endl;
	
	cout << "******* the sorted data ***********" << endl;
	inserationSort(v);
	for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
	}
	cout << endl;
	
	cout << " done ." << endl;
	return 0;
}


