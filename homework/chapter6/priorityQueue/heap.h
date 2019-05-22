#ifndef HEAP_H_
#define HEAP_H_

#include<iostream>
#include<vector>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;

template<class T>
class Heap{
public:
	//Heap constructor
	explicit Heap(int cap = 10):array(cap + 1),currentSize(0){
	};
	
	//another Heap constructor
	explicit Heap(const vector<T> &arr): array(arr.size() + 10), currentSize(arr.size()){
		for(int i = 0; i < arr.size(); i++){
			array[i + 1] = arr[i];
		}
		buildHeap();
	};
	
	//judge whether the array is empty
	bool isEmpty() const{
		return currentSize == 0;
	};
	
	//make the array empty
	void makeEmpty(){
		if(isEmpty()){
			return;
		}
		for(int i = array.size(); i > 0; i--){
			array.pop_back();
		}
		currentSize = 0;
	};
	
	//find the minimum item
	const T & findMin() const{
		return array[1];
	};
	
	//insert item into array
	void insert(const T &item){
		if(currentSize == array.size() - 1){
			array.resize(array.size() * 2);
		}
		int hole = ++currentSize;
		for(; hole > 1 && item < array[hole / 2]; hole /= 2){
			array[hole] = array[hole / 2];
		}
		array[hole] = item;
	};
	//delete minimum item in array
	void deleteMin(){
		if(isEmpty()){
			cout << " the array is empty, failed to deleteMin" << endl;
			return;
		}
		array[1] = array[currentSize--];
		percolateDown(1);
	};
	//deleteMin overload
	void deleteMin(T &item){
		if(isEmpty()){
			cout << " the array is empty, failed to deleteMin" << endl;
			return;
		}
		item = array[1];
		array[1] = array[currentSize--];
		percolateDown(1);
	};
	//print the array
	void print(){
		for(int i = 0; i < currentSize; i++){
			cout << array[i] << " ";
		}
		cout << endl;
	};
private:
	void buildHeap(){
		for(int i = currentSize / 2; i >0 ; i--){
			percolateDown(i);
		}
	};
	void percolateDown(int hole){
		int child;
		T temp = array[hole];
		for(; hole * 2 < currentSize; hole = child){
			child = hole * 2;
			if(child != currentSize && array[child + 1] < array[child]){
				child++;
			}
			if(array[child] < temp){
				array[hole] = array[child];
			}else{
				break;
			}
		}
		array[hole] = temp;
	};
private:
	int currentSize;
	vector<T> array;
};

#endif

