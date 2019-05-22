#ifndef LINKQUEUE_H_
#define LINKQUEUE_H_

#include<iostream>
template<class dataType>
struct Node{
	dataType data;
	Node<dataType>* next;
	Node(dataType &d, Node<dataType> *n = NULL):data(d), next(n){};
};

template<class dataType>
class LinkQueue{
private:
	Node<dataType> *front, *rear;
public:
	LinkQueue():front(NULL), rear(NULL){};
	~LinkQueue(){clear();};
	void clear();
	int getSize();
	bool isEmpty();
	bool deQueue(dataType &d);
	bool enQueue(dataType &d);
};

template<class dataType>
void LinkQueue<dataType>::clear(){
	Node<dataType> *temp;
	while(front != NULL){
		temp = front;
		front = front -> next;
		delete front;
	}
}

template<class dataType>
int LinkQueue<dataType>::getSize(){
	int num = 0;
	Node<dataType> *temp = front;
	while(temp != NULL){
		num++;
		temp = temp -> next;
	}
	return num;
}

template<class dataType>
bool LinkQueue<dataType>::isEmpty(){
	return front == NULL;
}

template<class dataType>
bool LinkQueue<dataType>::deQueue(dataType &d){
	if(isEmpty()){
		return false;
	}
	Node<dataType> *temp = front;
	d = front -> data;
	front = front -> next;
	delete temp;
	return true;
}

template<class dataType>
bool LinkQueue<dataType>::enQueue(dataType &d){
	if(front == NULL){
		front = rear = new Node<dataType>(d);
	}
	else{
		rear = rear -> next = new Node<dataType>(d);
	}
	return true;
}

#endif

