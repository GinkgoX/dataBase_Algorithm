#ifndef DISJOINTSET_H_
#define DISJOINTSET_H_

#include<iostream>
#include<vector>

using std::vector;

class DisjointSet{
public:
	//DisjointSet constructor
	explicit DisjointSet(int n = 10):s(n){
		for(int i = 0; i < s.size(); i++){
			s[i] = -1;
		}
	};
	
	//find root without path compression
	int find(int root) const{
		if(s[root] < 0){
			return root;
		}else{
			return find(s[root]); 
		}
	};
	
	//unionSet by height
	void unionSet(int r1, int r2){
		//if root1 and root2 are in same class, do nothing
		int root1 = find(r1);
		int root2 = find(r2);
		if(root1 == root2){
			return;
		}
		//otherwise unionSet
		if(s[root2] < s[root1]){
			s[root1] = root2;
		}else if(s[root2] == s[root1]){
			s[root1]--;
			s[root2] = root1;
		}else{
			s[root2] = root1;
		}
	};
	
	//judge whether the root1 and root2 has same root
	bool isConnected(int root1, int root2){
		return find(root1) == find(root2);
	};
	
private:
	vector<int> s;
};

#endif

