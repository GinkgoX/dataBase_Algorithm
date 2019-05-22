#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<class T>
void bucketSort(vector<T> &v){
	typename vector<T>::iterator itr = max_element(v.begin(), v.end());
	//cout << " max value : " << *itr << endl;
	vector<T> bucket((int)*itr + 1);
	//count the v[i] times and locate the position
	for(int i = 0; i < v.size(); i++){
		bucket[v[i]]++;
	}
	//rewrite v in order
	for(int i = 0, j = 0; i < bucket.size(); i++){
		while( (bucket[i]--) > 0){
			v[j++] = i;
		}
	}
	bucket.clear();
}

int main(){
	//int arr[] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15};
	int arr[] = {2, 3, 3, 4, 2, 5, 6, 7, 4, 5, 8};
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
	bucketSort(v);
	for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
	}
	cout << endl;
	
	cout << " done ." << endl;
	return 0;
}

