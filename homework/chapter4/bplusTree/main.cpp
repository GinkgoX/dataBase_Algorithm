#include <iostream>  
#include <cstdlib>  
 using namespace std;  
 #include "btree.h"  
 int main(){  
     BTree<int> btree(3);  
     int init[]={1, 2 , 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 15, 16, 14, 19, 18, 17, 20};  
     for (int i=0; i<20; i++){  
         btree.Insert(init[i]);  
     }  
     btree.Print();  
     cout << endl << endl << endl;  
     Triple<int> result = btree.Search(13);  
     cout << result.m_pfind->GetKey(result.m_nfind) << endl;  
     cout << endl << endl << endl;  
     for (int i=0; i<4; i++){ 
     	cout << "********* Remove " << init[i] << " ******** " << endl; 
         btree.Remove(init[i]);  
         btree.Print();  
         cout << endl << endl << endl;  
     }  
     return 0;  
 }  
