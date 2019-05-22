#include<iostream>
#include<cstring>
#include"stack.h"

using namespace std;

int main()
{
	try{
		string s = "";
		Calculator calculator(s);
		bool flag = true;
		char ch;
		while(flag){
			cout << "enter an expression : ";
			getline(cin, s);
			calculator.init(s);
			cout << " the calculate result is : " << calculator.calculate() << endl;
			cout << "enter Y or N to continue or not : ";
			cin >> ch;
			if(ch == 'Y' || ch == 'y'){
				flag = true;
				cin.get();
			}
			else if(ch == 'N' || ch == 'n'){
				flag = false;
				cin.get();
			}
			else{
				cout << "only Y or N avaible, I will exit !" << endl;
				flag = false;
			}
		}
		cout << " done." << endl;
	
	}
	catch(int i){
		if(i == 0){
			cout << "denominator can't be 0! " << endl; 
		}
		else if(i == 1){
			cout << "wrong expression, please check it again !" << endl;
		}
	}
	return 0;
}
