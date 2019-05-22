#include<iostream>
#include<vector>

using namespace std;

template<class Compareable>
void shellSort(vector<Compareable> &v){
	//update gap
	for(int gap = v.size() / 2; gap > 0; gap /= 2){
		//traverse vector
		for(int i = gap; i < v.size(); i++){
			Compareable temp = v[i];
			int j = i;
			//find the proper location
			for(; j >= gap && temp < v[j - gap]; j -= gap){
				v[j] = v[j - gap];
			}
			//insert into the proper location;
			v[j] = temp;
		}
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
	shellSort(v);
	for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
	}
	cout << endl;
	
	cout << " done ." << endl;
	return 0;
}


