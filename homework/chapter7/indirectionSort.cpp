#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<class Comparable>
class Pointer{
public:
	//Pointer constructor
	Pointer(Comparable *p = NULL):pointee(p){
	
	};
	
	//operator< overwrite
	bool operator<(const Pointer &p) const{
		return (*pointee < *p.pointee);
	};
	//access the pointer value
	operator Comparable * ( ) const{
		return pointee;
	};
	
private:
	Comparable *pointee;
};

template<class Comparable>
void indirectionSort(vector<Comparable> &v);

//quickSort vector v
template<class Comparable>
void quickSort(vector<Comparable> &v);

//find median in vector v from index left, center, right
template<class Comparable>
const Comparable & median3(vector<Comparable> &v, int left, int right);

//quickSort the inner part
template<class Comparable>
void quickSort(vector<Comparable> &v, int left, int right);

//backup sort when vector size is smaller than 10
template<class Compareable>
void inserationSort(vector<Compareable> &v, int left, int right);

//main function
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
	indirectionSort(v);
	for(typename vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr){
		cout << *itr << " ";
	}
	cout << endl;
	
	cout << " done ." << endl;
	return 0;
}

template<class Comparable>
void indirectionSort(vector<Comparable> &v){
	vector<Pointer<Comparable> > p(v.size());
	int i, j, nextj;
	//copy vector v into p
	for(i = 0; i < v.size(); i++){
		p[i] = &v[i];			//background construt temp variable
	}
	cout << endl;
	//sort p
	quickSort(p);
	cout << " the sorted p is : ";
	for(i = 0; i < v.size(); i++){
		cout << *p[i] << " ";
	}
	cout << endl;
	//restore p into v
	for(i = 0; i < v.size(); i++){
		if(p[i] != &v[i]){		//implicit convert Pointer<Comparable> p to Comparable* p
			Comparable temp = v[i];
			//find the proper index of v[i]
			for(j = i; p[j] != &v[i]; j = nextj){
				nextj = p[j] - &v[0];	//the distance betweent v[i] and v[0]
				v[j] = *p[j];
				p[j] = &v[j];
			}
			//insert v[i]
			v[j] = temp;
			//update p[j]/p[i]
			p[j] = &v[j];
		}
	}	
}

template<class Comparable>
void quickSort(vector<Comparable> &v){
	quickSort(v, 0, v.size() - 1);
}

template<class Comparable>
const Comparable & median3(vector<Comparable> &v, int left, int right){
	int center = (left + right) / 2;
	//cout << v[left] << " , " << v[center] << " , " << v[right];
	//sort the left, center and right in order
	if(v[center] < v[left]){
		swap(v[left], v[center]);
	}
	if(v[right] < v[left]){
		swap(v[left], v[right]);
	}
	if(v[right] < v[center]){
		swap(v[center], v[right]);
	}
	//cout << " : median is " << v[center] << endl;
	swap(v[center], v[right -1]);		//place the median to the last index
	return v[right - 1];
}

template<class Comparable>
void quickSort(vector<Comparable> &v, int left, int right){
	if(left + 10 <= right){ 	// using the quickSort when vector size is larger than 10
		Comparable pivot = median3(v, left, right);
		int i = left, j = right - 1;
		for(;;){
			while(v[++i] < pivot){};	//find the j's warning mark
			while(pivot < v[--j]){};	//find the i's warning mark
			if(i < j){
				swap(v[i], v[j]);		//swap the warning mark
			}else{
				break;
			}
		}
		swap(v[i], v[right - 1]);		//restore the pivot
		quickSort(v, left, i - 1);		//iterative quickSort the left part
		quickSort(v, i + 1, right);		//iterative quickSort the right part
	}else{								//using the inserationSort when vector size is smaller than 10
		inserationSort(v, left, right + 1);
	}
}

template<class Compareable>
void inserationSort(vector<Compareable> &v, int left, int right){
	if(left < right){
		int j;
		//traverse the vector form left to right
		for(int p  = left; p < right; p++){
			Compareable temp = v[p];
			//find the proper location
			for(j = p; j > 0 && temp < v[j - 1]; j--){
				v[j] = v[j - 1];
			}
			//insert into proper location
			v[j] = temp;
		}
	}
}

