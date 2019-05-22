#ifndef HEAP_H_
#define HEAP_H_

#include<iostream>
using std::cout;
using std::endl;

template<class T>
class Heap{
public:
	//Heap constructor
	Heap(int tSize = 30){
		currentSize = 0;
		totalSize = tSize;
		array = new T[totalSize];
	};
	
	//Heap destructor
	~Heap(){
		currentSize = 0;
		totalSize = 0;
		delete[] array;
	};
	
	//get data index in array
	int getIndex(T data){
		for(int i = 0; i < currentSize; i++){
			if(array[i] == data){
				return i;
			}
		}
		return -1;
	};
	
	//insert data into array
	int insert(T data){
		if(currentSize == totalSize){
			return -1;
		}
		array[currentSize] = data;
		filterUp(currentSize);
		currentSize++;
		return 0;
	};
	
	//remove data from array
	int remove(T data){
		if(currentSize == 0){
			return -1;
		}
		int index = getIndex(data);
		if(index == -1){
			return -1;
		}
		array[index] = array[--currentSize];
		filterDown(index, currentSize - 1);
		return 0;
	};
	
	//print date info
	void print(){
		for(int i = 0; i < currentSize; i++){
			cout << array[i] << " ";
		}
		cout << endl;
	};
	
private:
	void filterDown(int start, int end);
	void filterUp(int start);
private:
	T *array;
	int totalSize;
	int currentSize;
};

template<class T>
void Heap<T>::filterDown(int start, int end){
	int i = start;
	int l = 2 * i + 1;
	T temp = array[i];
	while(l <= end){
		if(l < end && array[l] < array[l + 1]){
			l++;
		}
		//if temp <= array[l] minimum heap adjust
		if(temp >= array[l]){	//maximum heap adjust
			break;
		}else{
			array[i] = array[l];
			i = l;
			l = 2 * l + 1;
		}
	}
	array[i] = temp;
}

template<class T>
void Heap<T>::filterUp(int start){
	int i = start;
	int p = (i - 1) / 2;
	T temp = array[i];
	while(i > 0){
		//if array[p] <= temp minimum heap adjust
		if(array[p] >= temp){	//maximum heap adjust
			break;
		}else{
			array[i] = array[p];
			i = p;
			p = (p - 1) / 2;
		}
	}
	array[i] = temp;
}
#endif
