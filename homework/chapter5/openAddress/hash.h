#ifndef HASH_H_
#define HASH_H_

#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<cmath>
#include<iomanip>

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::vector;
using std::list;
using std::setw;

class Student{
private:
	string name;
	string course;
	double score;
public:
	//Student constructor
	Student(const string &n, const string &c, double s):name(n), course(c), score(s){
	};
	//non parameter constructor
	Student():name(""), course(""), score(0.0){
	
	}
	
	//Student destructor
	~Student(){
	};
	
	//get name 
	const string & getName() const{
		return name;
	};
	
	//overload operator==
	bool operator==(const Student &stu) const{
		return name == stu.name;
	};
	
	//overload operator!=
	bool operator!=(const Student &stu) const{
		return !(*this == stu);
	};
	
	//overload operator<<
	friend ostream & operator<<(ostream &os, const Student &stu){
		cout << " name : " << stu.name << setw(8) << " course : " << setw(8) << stu.course << " score : " << stu.score << endl;
		return os;
	}	
};

//hash function
int hash(const string &key){
	int hashVal = 0;
	for(int i = 0; i < key.length(); i++){
		hashVal = 37 * hashVal + key[i];
	}
	return hashVal;
};

//overload hash function
int hash(const Student &stu){
	return hash(stu.getName());
};

template<class T>
class HashTable{
public:
	//define the EntryType 
	enum EntryType{ACTIVE, EMPTY, DELETED};
private:
	struct Entry{
		T element;
		EntryType info;
		//Entry constructor
		Entry(const T &obj = T(), EntryType i = EMPTY):element(obj), info(i){
		}
	};	
	
	vector<Entry> table;
	int currentSize;
public:
	//HashTable constructor
	HashTable(int num = 7):table(nextPrime(num)), currentSize(0){
		makeEmpty();
	};
	
	//HashTable destructor
	~HashTable(){
	};
	
	//judge whether the table contain obj return T obj
	T findElement(const T &obj){
		int currentPos = findPos(obj);
		if(isActive(currentPos)){
			return table[currentPos].element;
		}else{
			T temp;
			return temp;
		}
	};
	
	//find the position of obj
	int findPos(const T &obj){
		/*
			linear prober : f(i) = i, delta = 1;
			square prober : f(i) = i * i, delte = 2 * i - 1;
			double hash : f(i) = i * hash2(x), 
						  hash2(x) = R - (x % R) whether R is prime and R < currentSize 
						  delta = hash2(x)
		*/
		int offSet = 1;
		int currentPos = myhash(obj);
		while((table[currentPos].info != EMPTY) && (table[currentPos].element != obj)){
			//linear prober currentPos += offSet;
			//square prober 
			//currentPos += 2 * offSet - 1;
			//double hash
			currentPos = prePrime(table.size()) - currentPos % prePrime(table.size());
			offSet++;
		}
		if(currentPos >= table.size()){
			currentPos -=  table.size();
		}
		return currentPos;
	};
	
	//judge whether table contain obj reutrn bool
	bool contain(const T &obj){
		return isActive(findPos(obj));
	};
	
	//empty the table
	void makeEmpty(){
		for(int i = 0; i < table.size(); i++){
			table[i].info = EMPTY;
		}
		currentSize = 0;
	};
	
	//judge whether table is empty
	bool isEmpty(){
		return currentSize == 0;
	};
	
	//insert obj into table
	bool insert(const T &obj){
		int currentPos = findPos(obj);
		if(isActive(currentPos)){
			return false;
		}
		table[currentPos] = Entry(obj, ACTIVE);
		if(++currentSize >= table.size() / 2){
			rehash();
		}
		return true;
	};
	
	//remove obj outof table
	bool remove(const T &obj){
		int currentPos = findPos(obj);
		if(!isActive(currentPos)){
			return false;
		}
		table[currentPos].info = DELETED;
		currentSize--;
		return true;
	};
	
	//print the table
	void print(){
		cout << " the table info as follows : " << endl;
		for(int i = 0; i < table.size(); i++){
			if(isActive(i)){
				cout << i << " : " << table[i] << endl;
			}
		}
	};
	
	friend ostream & operator<<(ostream &os, const Entry &e){
		os << "element : " << e.element << setw(8) << " info : " << e.info << endl;
		return os; 
	};
	
private:
	//rehash operation
	void rehash(){
		vector<Entry> temp = table;
		table.resize(nextPrime(2 * table.size()));
		for(int i = 0; i < table.size(); i++){
			table[i].info = EMPTY;
		}
		currentSize = 0;
		for(int i = 0; i < temp.size(); i++){
			if(temp[i].info == ACTIVE){
				insert(temp[i].element);
			}
		}
	};
	
	//hash function
	int myhash(const T &obj) const{
		int hashVal = hash(obj);
		hashVal %= table.size();
		if(hashVal < 0){
			hashVal += table.size();
		}
		return hashVal;
	};
	
	//judge whether the obj at currentPos is actived or not 
	bool isActive(int currentPos) const{
		return table[currentPos].info == ACTIVE;
	};
	
	//find next prime which is bigger than currentSize
	int nextPrime(int n){
		//set flag
		bool flag = true;
		for(int i = n; ; i++) {
			for(int j = 2;j < i; j++) {
				if(i % j == 0) {
					//not a prime
					flag = false;
					break;
				}
			}
			//find the prime
			if(flag) {
				return i;
				break;
			}
			flag = true;
		}
	};
	
	//find previous prime which is smaller than currentSize
	int prePrime(int n){
		//set flag
		bool flag = true;
		for(int i = n; i > 1; i--) {
			for(int j = i - 1;j  > 1; j--) {
				if(i % j == 0) {
					//not a prime
					flag = false;
					break;
				}
			}
			//find the prime
			if(flag) {
				return i;
				break;
			}
			flag = true;
		}
	}; 
};

#endif
