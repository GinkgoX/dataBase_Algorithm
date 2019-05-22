#include<iostream>
#include"hash.h"

using namespace std;

int main(){
	Student stu[6] = {
		Student("Aimi", "python", 80.6),
		Student("Brone", "C++", 90.3),
		Student("Cver", "python", 85.6),
		Student("David", "C++", 89.7),
		Student("Eular", "java", 85.0),
		Student("Frank", "C++", 92.1)
	};
	
	vector<Student> vstu;
	for(int i = 0; i < 6; i++){
		vstu.push_back(stu[i]);
	}
	
	for(int i = 0; i < 6; i++){
		cout << vstu[i];
	}
	
	cout << "******** insert ********" << endl;
	HashTable<Student> hashTable;
	for(int i = 0; i < 6; i++){
		hashTable.insert(vstu[i]);
	}
	
	cout << "******** print ********" << endl;
	hashTable.print();
	
	cout << "******** contain ********" << endl;	
	if(hashTable.contain(stu[0])){
		cout << " contain " << stu[0] << endl;
	}else{
		cout << "does not exist the object !" << endl;
	}
	
	cout << "******** findElement ********" << endl;
	cout << hashTable.findElement(stu[1]) << endl;
	
	cout << "******** insert ********" << endl;
	hashTable.insert(Student("Furier", "java", 89.0));
	hashTable.print();
	
	cout << "******** remove ********" << endl;	
	hashTable.remove(stu[3]);
	hashTable.print();	
	return 0;
}
