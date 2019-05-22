#include<iostream>
#include<ctime>
#include<cstdlib>
#include"disjointSet.h"

using namespace std;

const int N = 10;

int wall_row[N+1][N];
int wall_column[N][N+1];

//init the maze
void init();

//print the maze
void print();

//get random number
int getRand();

//reallcate flage type and location
void mapRand(int rdm, int &type, int &row, int &column);

//reallcate the root
void mapRoot(int type, int row, int column, int &root1, int &root2);

int main(){
	init();
	//print();
	srand(time(0));
	int amount = N * 10;
	DisjointSet disjointSet(amount);
	int count = 0;
	while(!disjointSet.isConnected(0, amount - 1)){
		count++;
		int type, row, column;
		do{
			int rdm = getRand();
			mapRand(rdm, type, row, column); 
		}while((type == 0 && wall_column[row][column] == 0) || (type == 1 && wall_row[row][column] == 0));
		int root1, root2;
		mapRoot(type, row, column, root1, root2);
		print();
		if( !disjointSet.isConnected(root1, root2)){
			if(type == 0){
				wall_column[row][column] = 0;
			}else{
				wall_row[row][column] = 0;
			}
			disjointSet.unionSet(root1, root2);
		}
	}
	cout << "After " << count << " times random access btreak the wall, the results as follow " << endl;
	print();
	return 0;
}


void init(){
	int i,j;
	for(i= 0; i < N+1; i++){
		for(j = 0; j < N; j++){
			wall_row[i][j] = 1;
		}
	}
	for(i= 0; i < N; i++){
		for(j = 0; j < N+1; j++){
			wall_column[i][j] = 1;
		}
	}
	wall_row[0][0] = 0;
	wall_column[0][0] = 0;
	wall_row[N][N-1] = 0;
	wall_column[N-1][N] = 0;
}

void print(){
	int i, j;
	for(i = 0; i < N+1; i++){
		for(j = 0; j < N+1; j++){
			if(i > 0){
				if(wall_column[i-1][j]){
					cout << "|";
				}else{
					cout << " ";
				}
			}
			if(j < N){
				if(i > 0){
					if(wall_row[i][j]){
						cout << "_";
					}else{
						cout << " ";
					}
				}else{
					if(wall_row[i][j]){
						cout << "_";
					}else{
						cout << " ";
					}
				}
			}
		}
		cout << endl;
	}
}

int getRand(){
	return rand() % (N * (N - 1) * 2);
}

void mapRand(int rdm, int &type, int &row, int &column){
	type = rdm >= (N * (N -1)) ? 1 : 0; 
	if(type == 0){
		row = rdm / (N - 1);
		column = rdm % (N - 1) + 1;
	}else{
		rdm -= N * (N - 1);
		row = rdm / N + 1;
		column = rdm % N;
	}
}

void mapRoot(int type, int row, int column, int &root1, int &root2){
	if(type == 0){
		root1 = row * N + column - 1;
		root2 = row * N + column;
	}else{
		root1 = (row - 1) * N + column;
		root2 = row * N + column;
	}
}

