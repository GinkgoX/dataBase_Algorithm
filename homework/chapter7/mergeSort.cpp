#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//mergeSort vector
template<class Comparable>
void mergeSort(vector<Comparable> &v);

//mergeSort inner part to be ordered small array
template<class Comparable>
void mergeSort(vector<Comparable> &v, vector<Comparable> &temArray, int left, int right);

//merge v_left and v_riht part
template<class Comparable>
void merge(vector<Comparable> &v, vector<Comparable> &temArray, int leftPos, int rightPos, int rightEnd);

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
	mergeSort(v);
	for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
	}
	cout << endl;
	
	cout << " done ." << endl;
	return 0;
}

template<class Comparable>
void mergeSort(vector<Comparable> &v){
	vector<Comparable> temArray(v.size());
	mergeSort(v, temArray, 0, v.size() - 1);
}

template<class Comparable>
void mergeSort(vector<Comparable> &v, vector<Comparable> &temArray, int left, int right){
	if(left < right){
		int center = (left + right) / 2;
		//iterative merge left part
		mergeSort(v, temArray, left, center);
		//iterative merge right part
		mergeSort(v, temArray, center + 1, right);
		//merge the left part and right part
		merge(v, temArray, left, center + 1, right);
	}
}

template<class Comparable>
void merge(vector<Comparable> &v, vector<Comparable> &temArray, int leftPos, int rightPos, int rightEnd){
	int leftEnd = rightPos - 1;
	int temPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	//left part and right part has same size
	while(leftPos <= leftEnd && rightPos <= rightEnd){
		//compare the two parts and assingn the smaller value to temArray
		if(v[leftPos] < v[rightPos]){
			temArray[temPos++] = v[leftPos++];
		}else{
			temArray[temPos++] = v[rightPos++];
		}
	}
	//if left part has more elements, insert into the temArray last
	while(leftPos <= leftEnd){
		temArray[temPos++] = v[leftPos++];
	}
	//if right part has more elements, insert into the temArray last
	while(rightPos <= rightEnd){
		temArray[temPos++] = v[rightPos++];
	}
	//copy the sorted temArray to vector v
	for(int i = 0; i < numElements; i++, rightEnd--){
		v[rightEnd] = temArray[rightEnd];
	}
}
