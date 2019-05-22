#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;
const int REPEAT = 100; //repeat REPEAT time to calcuate the time

class myPoint {
public:
    float x;
    float y;
};

//compare point a and b controlled by type
bool compare(myPoint a, myPoint b, int type) {
    if (type == 1) {
        return a.x > b.x;
    }
    else {
        return a.y > b.y;
    }
}
void Initial(int N, myPoint* X, myPoint* Y) {
    srand(time(0));  //get the system clock 
    int i;
    for (i = 0; i < N; i++) {  //generate the random value [-10, 10]
        X[i].x = rand() / double(RAND_MAX)*20 - 10;
        X[i].y = rand() / double(RAND_MAX)*20 - 10;
        Y[i].x = X[i].x;
        Y[i].y = X[i].y;
        cout << "The rand pair is : (" << X[i].x << ", " << X[i].y << " ) " << endl;
    }
}
double Distance(myPoint p1, myPoint p2) {  //calcuate the distance
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

//quickSort the axis value controlled by type
void quickSort(myPoint* P, int start, int end, int type) {
    if (start == end)	//only one point
        return;
    int primary_start = start; 		//save the original start
    int primart_end = end;			//save the original end
    myPoint pivotKey = P[start]; 	//set pivotKey

    while (start < end)		//quickSort algrithm
    {	//find the right border
        while (start < end && compare(P[end], pivotKey, type))
        {
            end--;
        }
        //update the start
        if (start < end) {
            P[start++] = P[end];
        }
        //find the left border
        while (start < end &&  compare(pivotKey, P[start], type))
        {
            start++;
        }
        //update the end
        if (start < end) {
            P[end--] = P[start];
        }
    }
    //update pivotKey when start = end
    P[start] = pivotKey;
	
	//quickSort the left part
    if (start - 1>primary_start){
    	quickSort(P, primary_start, start - 1, type);
    }
	//quickSort the right part
    if (start + 1<primart_end){
    	quickSort(P, start + 1, primart_end, type);
    }
}

//direct solve the nearest points
double force(int start, int end, myPoint* P, myPoint& P1, myPoint& P2) {
    int i, j;
    if (end - start<1) {	//only one point
        return 0.0;
    }
    double minDis = Distance(P[start], P[start + 1]);  //init the minDis
    P1 = P[start];		//init P1
    P2 = P[start+1];	//init P2
    for (i = start; i <= end; i++) {
        for (j = start; j <= end; j++) {
            if (i != j && Distance(P[i], P[j])<minDis) {
                minDis = Distance(P[i], P[j]);
                P1 = P[i];
                P2 = P[j];
            }
        }
    }
    return minDis;
}

//divide_conquer algrithm for nearest points
double divide_conquer(int start, int end, myPoint* X, myPoint* Y, myPoint& P1, myPoint& P2) {

    if (end - start < 3){
        return force(start, end, X,P1,P2);
   }
   //divide
    int mid = (start + end) / 2; 
    int leftLen = 0, rightLen = 0, i, j; 
    myPoint* YL = new myPoint[(end - start + 1) ];//y left part
    myPoint* YR = new myPoint[(end - start + 1) ];//y right part
	//conquer
    for (i = 0; i <= end - start; i++){
        if (Y[i].x <= X[mid].x) {
            YL[leftLen++] = Y[i];
        }
        else {
            YR[rightLen++] = Y[i];
        }
    }
    double left = divide_conquer(start, mid, X, YL,P1,P2);	//find the left minDis
    myPoint leftP1 = P1;			//save P1
    myPoint leftP2 = P2;			//save P2
    double right = divide_conquer(mid + 1, end, X, YR,P1,P2);  //find the right minDis
    double minDis;
    //take the minDis from left and right, refill P1 and P2
    if (left < right) {
        minDis = left;
        P1 = leftP1;
        P2 = leftP2;
    }
    else {
        minDis = right;
    }
    //setup the danding region
    myPoint* newY = new myPoint[(end - start + 1)];
    int newYLen = 0;
    double leftBorder = X[mid].x - minDis;
    double rightBorder = X[mid].x + minDis;
    //find the points in region
    for (i = 0; i <= end - start; i++) {
        if (Y[i].x >= leftBorder && Y[i].x <= rightBorder){
        	newY[newYLen++] = Y[i];
        }
    }
    //find the nearest 7 distance
    for (i = 0; i<newYLen; i++) {
        for (j = 1; j <= 7; j++) {
        	//keep the newY in region
            if ((i + j)<newYLen) {
                double dis = Distance(newY[i], newY[i + j]);
                if (dis < minDis) {
                    minDis = dis;
                    P1 = newY[i];
                    P2 = newY[i + j];
                }
            }
        }
    }
    delete YL;
    delete YR;
    delete newY;
    return minDis;
}
int main(){
    int N;
    cout << "Enter the total number of points :";
    cin >> N;
    //create X and Y(same as X) points set
    myPoint* X = new myPoint[N];
    myPoint* Y = new myPoint[N];
    int i;
    clock_t start, end;
    double ave = 0.0;
    double minDis = 0.0;
    myPoint P1, P2; //init the nearest points result
    Initial(N, X, Y);	//instantiation the X and Y
    for (i = 0; i < REPEAT; i++) {	//repeat REPEAT times
        start = clock();
        minDis += force(0, N - 1, X,P1,P2);
        end = clock();
        ave += (double)(end - start);
    }
    ave /= REPEAT;
    minDis /= REPEAT;
    cout << "force: minDis : " << minDis << " time loss : " <<ave<<" ms" << setw(4);
    cout << " Position：(" << P1.x << "," << P1.y << "),(" << P2.x << "," << P2.y << ")"<<endl;

    ave = 0.0;
    minDis = 0.0;
    for (i = 0; i < REPEAT; i++) {  
        start = clock();
        quickSort(X, 0, N - 1, 1);	//sort X axis
        quickSort(Y, 0, N - 1, 2);	//sort Y axis
        minDis+= divide_conquer(0, N - 1, X, Y,P1, P2);
        end = clock();
        ave += (double)(end - start);
    }
    ave /= REPEAT;
    minDis /= REPEAT;
    cout << "divide_conquer: minDis : " <<minDis<< " time loss : " << ave << " ms" << setw(4);
    cout << " Position：(" << P1.x << "," << P1.y << "),(" << P2.x << "," << P2.y << ")" << endl;
    delete[]X;
    delete[]Y;
    return 0;
}
