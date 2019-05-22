#include<iostream>
#include<vector>
#include<cmath>
#include<set>

using namespace std;

const int N = 6;

bool place(vector<int> &x, multiset<int> distSet, int N, int left, int right){
	int dmax;
	bool found = false;
	//when all distSet elements have been checked, return
	if(distSet.empty()){
		return true;
	}
	//copy of distSet
	multiset<int> dSet = distSet;
	dmax = *distSet.rbegin();
	//place dmax to x[right]
	x[right] = dmax;
	bool flag = true;
	//find the difference in left part
	for(int i = 1; i < left; i++){
		if(dSet.find(abs(dmax - x[i])) == dSet.end()){
			flag = false;
			break;
		}
		//take off the distance from left part(right part complement)
		dSet.erase(dSet.find(abs(x[i] - x[right])));
	}
	//find the difference in right part
	for(int i = right + 1; i <= N; i++){
		if(dSet.find(abs(dmax - x[i])) == dSet.end()){
			flag = false;
			break;
		}
		//take off the distance from right part
		dSet.erase(dSet.find(abs(x[i] - x[right])));
	}
	//iterative recall place method when flag = true
	if(flag){
		distSet = dSet;
		found = place(x, distSet, N, left, right - 1);
		//if not, reinsert the distance into distSet [backTracing]
		if(!found){
			for(int i = 1; i < left; i++){
				distSet.insert(abs(x[i] - x[right]));
			}
			for(int i = right + 1; i <= N; i++){
				distSet.insert(abs(x[i] - x[right]));
			}
		}
	}
	
	flag = true;
	dSet = distSet;
	//if not found suitable place in right, try the left
	if(!found){
		x[left] = x[N] - dmax;
		for(int i = 1; i < left; i++){
			if(dSet.find(abs(x[i] - x[left])) == dSet.end()){
				flag = false;
				break;
			}
			dSet.erase(dSet.find(abs(x[i] - x[left])));
		}
		for(int i = right + 1; i <= N; i++){
			if(dSet.find(abs(x[i] - x[left])) == dSet.end()){
				flag = false;
				break;
			}
			dSet.erase(dSet.find(abs(x[i] - x[left])));
		}
		//iterative recall place method when flag = true
		if(flag){
			distSet = dSet;
			found = place(x, distSet, N, left + 1, right);
			//if not, reinsert the distance into distSet [backTracing]
			if(!found){
				for(int i = 1; i < left; i++){
					distSet.insert(abs(x[N] - dmax - x[i]));
				}
				for(int i = right + 1; i <= N; i++){
					distSet.insert(abs(x[N] - dmax - x[i]));
				}
			}
		}
	}
	return found;
}

int main(){
	vector<int> x(N + 1);
	multiset<int> distSet;
	int dist[] = {1, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 10};
	int len = sizeof(dist) / sizeof(dist[0]);
	for(int i = 0; i < len; i++){
		distSet.insert(dist[i]);
	}
	//x_1 = 0
	x[1] = 0;
	//x_n = max, rebegin() reverse iterator
	x[N] = *distSet.rbegin();
	//take out the max distance
	distSet.erase(*distSet.rbegin());
	//traceBacking algorithm
	bool found = place(x, distSet, N, 2, N - 1);
	vector<int>::iterator itr;
	for(itr = x.begin() + 1; itr != x.end(); itr++){
		cout << *itr << " . ";
	}
	cout << endl;
	cout << " done." << endl;
	return 0;
}
