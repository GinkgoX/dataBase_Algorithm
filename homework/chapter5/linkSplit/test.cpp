#include<iostream>

using namespace std;

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
int main(){
	cout << nextPrime(14) << endl;
	cout << prePrime(14) << endl;
	return 0;
}
