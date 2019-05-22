#ifndef STACK_H_
#define STACK_H_

#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>

using std::cout;
using std::endl;
using std::string;

const int Max = 10;

//Stack template
template<class dataTpye>
class Stack{
private:
	int top;
	int maxTop;
	dataTpye* data;
public:
	Stack(int max = 10);
	~Stack(){delete[] data;};
	bool isEmpty(){return top == -1;};
	bool isFull(){return top == maxTop;};
	Stack<dataTpye> & push(const dataTpye &d);
	Stack<dataTpye> & pop(dataTpye &d);
	dataTpye getTop() const{return data[top];};
	void clear(){top = -1;};
	void print(){
		for(int i = 0; i < top + 1; i++){
			cout << data[i] << " ";
		}
		cout << endl;
	}
};

//Stack constructor
template<class dataTpye>
Stack<dataTpye>::Stack(int max){
	maxTop = max - 1;
	data = new dataTpye[max];
	top = -1;
}

//push data
template<class dataTpye>
Stack<dataTpye> & Stack<dataTpye>::push(const dataTpye &d){
	if(isFull()){
		cout << "the Stack is already full !" << endl;
		return *this;
	}
	else{
		data[++top] = d;
		return *this;
	}
}

//pop data
template<class dataTpye>
Stack<dataTpye> & Stack<dataTpye>::pop(dataTpye &d){
	if(isEmpty()){
		cout << "the Stack is already empty !" << endl;
		return *this;
	}
	else{
		d = data[top--];
		return *this;
	}
}

//judge where the character is a number nr not
bool isNum(char ch){
	if(ch >= '0' && ch <= '9'){
		return true;
	}
	else{
		return false;
	}
}

//omit the blank in string expression
void omitBlank(string &s){
	string::iterator i = s.begin();
	while((i = find(i, s.end(), ' ')) != s.end()){
		s.erase(i);
	}
}

//Calculator class
class Calculator{
private:
	string s;
	Stack<char>* symbol;
	Stack<int>* digital;
public:
	Calculator(string s);
	~Calculator();
	void init(string const s);
	int outerPriority(char outer);
	int innerPriority(char inner);
	bool judge(char outer, char inner);
	int judge(char op);
	void assign();
	int calculate();
};

//Calculator constructor
Calculator::Calculator(string s){
	init(s);
	symbol = new Stack<char>(Max);
	digital = new Stack<int>(Max);
}

//Calculator destructor
Calculator::~Calculator(){
	delete symbol;
	delete digital;
}

//Calculator init string
void Calculator::init(string const s){
	this -> s = "#" + s + "#";
	omitBlank(this -> s);
}

//outer priority outside ()
int Calculator::outerPriority(char outer){
	switch(outer){
		case '#' : return 0;
		case '(' : return 8;
		case '+' : return 2;
		case '-' : return 2;
		case '*' : return 4;
		case '/' : return 4;
		case '%' : return 4;
		case '^' : return 6;
		case ')' : return 1;
		default:
				throw 1;
	}
}

//inner priority inside ()
int Calculator::innerPriority(char inner){
	switch(inner){
		case '#' : return 0;
		case '(' : return 1;
		case '+' : return 3;
		case '-' : return 3;
		case '*' : return 5;
		case '/' : return 5;
		case '%' : return 5;
		case '^' : return 7;
		case ')' : return 8;
		default : throw 1;
		 
	}
}

//judge the priority between outer and inner
bool Calculator::judge(char outer, char inner){
	return outerPriority(outer) > innerPriority(inner);
}

//judge the operator
int Calculator::judge(char op){
	switch(op){
		case '#' : return -1;
		case ')' : return 0;
		default : return 1;
	}
}

//assign the operation based on symbol stack
void Calculator::assign(){
	char temp = 0;
	int data1 = 0;
	int data2 = 0;
	symbol -> pop(temp);
	digital -> pop(data1);
	digital -> pop(data2);
	switch(temp){
		case '+' : 
			data2 += data1;
			break;
		case '-' :
			data2 -= data1;
			break;
		case '*' :
			data2 *= data1;
			break;
		case '/' :
			if(data1 == 0){
				cout << "denominator can't be 0 !" << endl;
				throw 0;
			}
			else{
				data2 /= data1;
				break;
			}
		case '%' :
			data2 %= data1;
			break;
		case '^' :
			data2 = pow(data2, data1);
			break;
		default:
			throw 1;
	}
	digital -> push(data2);
}

//calculate the result based on the string characters
int Calculator::calculate(){
	for(int i = 0; i < s.size(); i++){
		if(isNum(s[i])){
			int num = s[i] - '0';
			int temp = 0;
			if(num > 0 && isNum(s[i-1])){
				digital -> pop(temp);
				num += temp * 10;
			}
			digital -> push(num);
		}
		else{
			char temp = s[i];
			if(symbol -> isEmpty()){
				symbol -> push(temp);
			}
			else{
				//judge priority between temp and symbol top
				if(judge(temp, symbol -> getTop())){
					symbol -> push(temp);
				}
				// case # symbol
				else if(judge(temp) == -1){
					while(symbol -> getTop() != '#'){
						assign();
					}
					int result = digital -> getTop();
					symbol -> clear();
					digital -> clear();
					return result;
				}
				//case ( symbol
				else if(judge(temp) == 0){
					while(symbol -> getTop() != '('){
						assign();
					}
					symbol -> pop(temp);
				}
				// case otherwise
				else if(judge(temp) == 1){
					while(! judge(temp, symbol -> getTop())){
						assign();
					}
					symbol -> push(temp);
				}
			}
		}
	}
}

#endif


