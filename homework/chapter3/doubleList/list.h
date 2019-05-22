#ifndef LIST_H_
#define LIST_H_

using std::cout;
using std::endl;
using std::swap;

template<class dataType>
struct Node{
	Node(const dataType d);
	dataType data;
	Node* next;
	Node* prev;
};

template<class dataType>
class List{
private:
	Node<dataType>* head;
	Node<dataType>* tail;
public:
	List();
	List(const List &l);
	List & operator=(List &l);
	~List();
	
	void reverse();
	void print();
	void clear();
	void pushFront(const dataType d);
	void pushBack(const dataType d);
	void popFront();
	void popBack();
	void insert(Node<dataType> *positon, dataType d);
	void erase(Node<dataType> *positon);
	void remove(dataType d);
	Node<dataType>* find(dataType d);
	int count();
};

//Node constructior
template<class dataType>
Node<dataType>::Node(const dataType d):data(d), next(NULL), prev(NULL){}

//List constructior
template<class dataType>
List<dataType>::List():head(NULL), tail(NULL){}

//List copy constructior
template<class dataType>
List<dataType>::List(const List<dataType> &l):head(NULL), tail(NULL){
	if(l.head == NULL){
		return;
	}
	Node<dataType>* temp = l.head;
	while(temp){
		pushBack(temp -> data);
		temp = temp -> next;
	}
}

//List operator=
template<class dataType>
List<dataType>& List<dataType>::operator=(List<dataType> &l){
	if(this != &l){
		std::swap(head, l.head);
		std::swap(tail, l.head);
	}
	return *this;
}

//List destructor
template<class dataType>
List<dataType>::~List(){
	clear();
}

//reverse the List
template<class dataType>
void List<dataType>::reverse(){
	if(head == NULL || head == tail){
		return;
	}
	Node<dataType>* begin = head;
	Node<dataType>* end = tail;
	int num = count();
	while(num){
		if(end -> next == begin){
			break;
		}
		num /= 2;
		std::swap(begin -> data, end -> data);
		begin = begin -> next;
		end = end -> prev;
	}
}

//print the List
template<class dataType>
void List<dataType>::print(){
	if(head == NULL){
		cout << "The List is empty ! " << endl;
	}
	else{
		Node<dataType>* temp = head;
		while(temp){
			cout << temp -> data << " ";
			temp = temp -> next;
		}
		cout << endl;
	}
}

//clear the List
template<class dataType>
void List<dataType>::clear(){
	Node<dataType>* temp = head;
	while(temp -> next != tail){
		head = head -> next;
		delete temp;
		temp = head;
	}
	head = NULL;
	tail = NULL;
}

//push data from the head
template<class dataType>
void List<dataType>::pushFront(const dataType d){
	if(head == NULL){
		pushBack(d);
	}else{
		Node<dataType>* temp = head;
		head = new Node<dataType>(d);
		head -> next = temp;
		temp -> prev = head;
	}
}

//push data from the tail
template<class dataType>
void List<dataType>::pushBack(const dataType data){
	if(head == NULL){
		head = new Node<dataType>(data);
		tail = head;
	}
	else{
		tail -> next = new Node<dataType>(data);
		tail -> next -> prev = tail;
		tail = tail -> next;
	}
}

// pop data from head
template<class dataType>
void List<dataType>::popFront(){
	if(head == NULL){
		cout << "the List is empty ! " << endl;
	}
	else{
		Node<dataType>* temp = head;
		head = head -> next;
		head -> prev = NULL;
		delete temp;
	}
}

//pop data from tail
template<class dataType>
void List<dataType>::popBack(){
	if(head == NULL){
		cout << "the List is empty !" << endl;
	}
	else if(head == tail){
		delete head;
		head = NULL;
		tail = NULL;
	}
	else{
		Node<dataType>* temp = head;
		while(temp -> next != tail){
			temp = temp -> next;
		}
		delete tail;
		tail = temp;
		tail -> prev = temp -> prev;
		tail -> next = NULL;
	}
}

//from Node positon insert Object data
template<class dataType>
void List<dataType>::insert(Node<dataType> *positon, dataType d){
	assert(positon);
	if(positon == tail){
		pushBack(d);
	}
	else{
		Node<dataType>* temp = new Node<dataType>(d);
		temp -> next = positon -> next;
		positon -> next = temp;
		temp -> next -> prev = temp;
		temp -> prev = positon;
	}
}

//erase the data in Node positon
template<class dataType>
void List<dataType>::erase(Node<dataType> *positon){
	assert(positon);
	if(positon == tail){
		popBack();
	}
	else if(positon == head){
		popFront();
	}
	else{
		positon -> prev -> next = positon -> next;
		positon -> next -> prev = positon -> prev;
		delete positon;
	}
}

//remove the data form List
template<class dataType>
void List<dataType>::remove(dataType d){
	if(head == NULL){
		cout << "the List is empty !" << endl;
	}
	else{
		Node<dataType>* temp = find(d);
		if(temp != NULL){
			erase(temp);
		}
	}
}

//find the data in List Node
template<class dataType>
Node<dataType>* List<dataType>::find(dataType d){
	if(head == NULL){
		cout << "the List is empty !" << endl;
		return NULL;
	}
	else{
		Node<dataType>* temp = head;
		while(temp -> next != tail){
			if(temp -> data == d){
				return temp;
			}
			temp = temp -> next;
		}
		return NULL;
	}
}

//count the List elements
template<class dataType>
int List<dataType>::count(){
	if(head == NULL){
		return 0;
	}
	else{
		Node<dataType>* temp = head;
		int num = 0;
		while(temp != tail){
			num++;
			temp = temp -> next;
		}
		return ++num;
	}
}

#endif

