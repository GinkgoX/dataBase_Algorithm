#include<iostream>
#include<cstdlib>
#include"seqQueue.h"

using namespace std;

void menu(){
	cout << "************ *MENU* *************" << endl;
	cout << "********* *1 enQueue* ***********" << endl;
	cout << "********* *2 deQueue* ***********" << endl;
	cout << "********* *3 getSize* ***********" << endl;
	cout << "********* *4 clear* *************" << endl;
	cout << "********* *5 exit* **************" << endl;
}

void excute(int num, SeqQueue<int> *q){
	switch(num){
		int temp;
		case 1 : 
			cout << "Enter the enQueue number : ";
			cin >> temp;
			q -> enQueue(temp);
			cout << temp << " has been enQueued " << endl;
			break;
		case 2 :
			q -> deQueue(temp);
			cout << "deQueue the number into temp : " << temp << endl;
			break;
		case 3 :
			cout << "the queue size is : " << q -> getSize() << endl;
			break;
		case 4 :
			cout << "I have clear the queue " << endl;	
			break;
		case 5 :
			cout << "I will exit the program !" << endl;
			exit(1);
		default:
			cout << "only 1 ~ 5 is avaible, Wrong operation !" << endl;
			exit(1);
	}
}

int main()
{
	SeqQueue<int> *queue = new SeqQueue<int>;
	menu();
	int temp;
	while(true){
		cout << "choise your operation : ";
		cin >> temp;
		cin.get();
		excute(temp, queue);
	}
	cout << "done . " << endl;
	delete[] queue;
	return 0;
}


