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
private:
	vector<list<T> > table;
	int currentSize;
public:
	//HashTable constructor
	HashTable(int num = 11):table(num), currentSize(0){
	};
	
	//HashTable destructor
	~HashTable(){
	};
	
	//judge whether the table contain obj return T obj
	T findElement(const T &obj){
		list<T> &temp = table[myhash(obj)];
		typename list<T>::iterator itr = find(temp.begin(), temp.end(), obj);
		if(itr != temp.end()){
			return *itr;
		}else{
			T temp1;
			return temp1;
		}
	};
	
	//judge whether table contain obj reutrn bool
	bool contain(const T &obj) const{
		const list<T> &temp = table[myhash(obj)];
		return find(temp.begin(), temp.end(), obj) != temp.end();
	};
	
	//empty the table
	void makeEmpty(){
		for(int i = 0; i < table.size(); i++){
			table[i].clear();
		}
		currentSize = 0;
	};
	
	//judge whether table is empty
	bool isEmpty(){
		return currentSize == 0;
	};
	
	//insert obj into table
	bool insert(const T &obj){
		list<T> &temp = table[myhash(obj)];
		//judge whether obj exist in table
		if(find(temp.begin(), temp.end(), obj) != temp.end()){
			return false;
		}
		temp.push_back(obj);
		if(++currentSize > table.size()){
			rehash();
		}
		return true;
	};
	
	//remove obj outof table
	bool remove(const T &obj){
		list<T> &temp = table[myhash(obj)];
		typename list<T>::iterator itr = find(temp.begin(), temp.end(), obj);
		if(itr == temp.end()){
			return false;
		}
		temp.erase(itr);
		currentSize--;
		return true;
	};
	
	//print the table
	void print(){
		cout << " the table info as follows : " << endl;
		for(int i = 0; i < table.size(); i++){
			cout << i << " : " << endl;
			for(typename list<T>::iterator itr = table[i].begin(); itr != table[i].end(); ++itr){
				cout << *itr;
			}
		}
	};
private:
	//rehash operation
	void rehash(){
		vector<list<T> > temp = table;
		table.resize(nextPrime(table.size()));
		for(int i = 0; i < table.size(); i++){
			table[i].clear();
		}
		for(int i = 0; i < temp.size(); i++){
			typename list<T>::iterator itr = temp[i].begin();
			while(itr != temp[i].end()){
				insert(*itr);
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
	
	//find next prime while is bigger than the twice of currentSize
	int nextPrime(int n){
		//set flag
		bool flag = true;
		for(int i = 2 * n; ; i++) {
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
};

#endif
