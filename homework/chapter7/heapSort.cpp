#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int leftChild(int i){
	return 2*i + 1;
}

template<class Compareable>
void percDown(vector<Compareable> &v, int i, int n){
	int child;
	Compareable temp;
	for(temp = v[i]; leftChild(i) < n; i = child){
		child = leftChild(i);
		//find the larger child
		if( (child != n -1) && (v[child] < v[child + 1]) ){
			child++;
		}
		//percolate down node
		if(temp < v[child]){
			v[i] = v[child];
		}else{
			break;
		}
	}
	v[i] = temp;
}

template<class Compareable>
void heapSort(vector<Compareable> &v){
	//stage 1 : setup the heap
	for(int i = v.size() / 2 ; i >= 0; i--){
		percDown(v, i, v.size());
		/*cout << i << " th result : " ;
		for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
		}
		cout << endl;*/
	}
	//stage 2 : swap and percolate down
	for(int j = v.size() - 1; j > 0; j--){
		swap(v[0], v[j]);
		percDown(v, 0, j);
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
	heapSort(v);
	for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
	}
	cout << endl;
	
	cout << " done ." << endl;
	return 0;
}

