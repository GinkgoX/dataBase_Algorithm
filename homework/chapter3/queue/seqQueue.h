#ifndef SEQQUEUE_H_
#define SEQQUEUE_H_

#include<iostream>

template<class dataType>
class SeqQueue{
private:
	dataType* data;
	int front, rear;
	int maxSize;
public:
	SeqQueue(int max = 10);
	~SeqQueue(){delete[] data;};
	bool deQueue(dataType &d);
	bool enQueue(const dataType &d);
	void clear(){front = rear = 0;};
	bool isEmpty() const{return front == rear;};
	bool isFull() const{return front == (rear + 1) % maxSize;}; 
	int getSize() const{return (rear - front + maxSize) % maxSize ;};
};

template<class dataType>
SeqQueue<dataType>::SeqQueue(int max){
	data = new dataType[max];
	front = rear = 0;
	maxSize = max;
}

template<class dataType>
bool SeqQueue<dataType>::deQueue(dataType &d){
	if(isEmpty()){
		return false;
	}
	else{
		d = data[front];
		front = (front + 1) % maxSize;
		return true;
	}
}

template<class dataType>
bool SeqQueue<dataType>::enQueue(const dataType &d){
	if(isFull()){
		return false;		
	}
	else{
		data[rear] = d;
		rear = (rear + 1) % maxSize;
		return true;
	}
}

#endif

