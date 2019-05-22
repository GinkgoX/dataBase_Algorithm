#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

class DisjointSet{
public:
	//DisjointSet constructor
	explicit DisjointSet(int n);
	
	//find value operation
	int find(int value) const;
	
	//union root2 to root1
	void unionSet(int root1, int root2);
	
	//union root2 to root1 by size
	void unionSetBySize(int root1, int root2);
	
	//union root2 to root1 by height
	void unionSetByHeight(int root1, int root2);
	
	//print the result
	void print();
	
	//reallocate s
	void init(){
		for(int i = 0; i < s.size(); i++){
			s[i] = -1;
		}
	};
private:
	vector<int> s;
};

DisjointSet::DisjointSet(int n = 10):s(n){
	for(int i = 0; i < n; i++){
		s[i] = -1;
	}
}

int DisjointSet::find(int value) const{
	if(s[value] == -1){
		return value;
	}else{
		return find(s[value]);
	}
}

/*
path compression : comparable to unionSetBySize, not totally comparable to unionSetByHeight
int DisjointSet::find(int value) {
	if(s[value] < 0){
		return value;
	}else{
		return s[value] = find(s[value]);
	}
}
*/
void DisjointSet::unionSet(int root1, int root2){
	s[root2] = root1;
}

void DisjointSet::unionSetBySize(int root1, int root2){
	if(s[root2] < s[root1]){	//size root2 is larger
		s[root2] += s[root1];
		s[root1] = root2;
	}else{ 						//size root1 is larger
		s[root1] += s[root2];
		s[root2] = root1;
	}
}

void DisjointSet::unionSetByHeight(int root1, int root2){
	if(s[root2] < s[root1]){			//root2 is deeper
		s[root1] = root2;
	}else if(s[root2] == s[root1]){		//the height is same
		s[root1]--;
		s[root2] = root1;
	}else{								//root1 is deeper
		s[root2] = root1;
	}
}

void DisjointSet::print(){
	cout << " the disjointSet info as follow " << endl;
	for(typename vector<int>::iterator itr = s.begin(); itr != s.end(); ++itr){
		cout << setw(4) << *itr << " ";
	}
	cout << endl;
	for(int i = 0; i < s.size(); i++){
		cout << setw(4) << i << " ";
	}
	cout << endl;
}

int main(){
	cout << "simple disjointSet : " << endl;
	DisjointSet disjointSet(8);
	disjointSet.unionSet(4, 5);
	disjointSet.unionSet(6, 7);
	disjointSet.unionSet(4, 6);
	disjointSet.unionSet(3, 4);
	disjointSet.print();
	/*for(int i = 0; i < disjointSet.s.size(); i++){
		cout << disjointSet.find(i) << " ";
	}
	cout << endl;*/
	
	cout << "union disjointSet by size : " << endl;
	disjointSet.init();
	disjointSet.unionSetBySize(4, 5);
	disjointSet.unionSetBySize(6, 7);
	disjointSet.unionSetBySize(4, 6);
	disjointSet.unionSetBySize(3, 4);
	disjointSet.print();
	/*for(int i = 0; i < disjointSet.s.size(); i++){
		cout << disjointSet.find(i) << " ";
	}
	cout << endl;*/
	
	cout << "union disjointSet by height : " << endl;
	disjointSet.init();
	disjointSet.unionSetByHeight(4, 5);
	disjointSet.unionSetByHeight(6, 7);
	disjointSet.unionSetByHeight(4, 6);
	disjointSet.unionSetByHeight(3, 4);
	disjointSet.print();
	/*for(int i = 0; i < disjointSet.s.size(); i++){
		cout << disjointSet.find(i) << " ";
	}
	cout << endl;*/
	
	cout << "done . " << endl;
	return 0;
}

