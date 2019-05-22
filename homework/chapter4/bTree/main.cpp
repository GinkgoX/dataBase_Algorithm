#include<iostream>
#include "btree.h"

using namespace std;

int main()
{
    /*//freopen("in.txt","r",stdin);
    int order=0;
    while(order!=7)
    {
        puts("---------------------------------------------------------------------");
        puts("Select menu");
        puts("1:Creat a new 3-B-tree");
        puts("2:Insert element");
        puts("3:Find element");
        puts("4:Delete element");
        puts("5:Print B-tree");
        puts("6:exit");
        cin>>order;
        switch(order)
        {
            case 1 : {Destory(T);creat_btree();break;}
            case 2 : {insert_keytype();break;}
            case 3 : {find_keytype();break;}
            case 4 : {delete_keytype();break;}
            case 5 : {show_Btree(T);puts("");break;}
            case 6 : {return 0;}
        }
    }*/
    //调试用代码
    BTree T = new BTNode ;
    T->keynum=0;
    result p ;
    int in[]={35,16,18,70,5,50,22,60,13,17,12,45,25,42,15,90,30,7};
    for(int i=0;i<18;i++)
    {
        printf("insert %d ",in[i]);
        SearchBTree(T,in[i],p);
        InsertBTree(T,in[i],p.pt,p.i);
        show_Btree(T);
        puts("");
    }
    show_Btree2(T,0);
    int out[]={45,90,50,22,42};
    for(int i=0;i<5;i++)
    {
        SearchBTree(T,out[i],p);
        if(p.tag)
        {
            printf("delete %d ",out[i]);
            DeleteBTree(p.pt,p.i,T);
            show_Btree(T);
            puts("");
             show_Btree2(T,0);
        }
        else
        {
            printf("%d is not in the tree\n",out[i]);
        }
    }
    Destory(T);
    if(T){
    	show_Btree(T);
    }
    else{
    	printf("B-tree is empty\n");
    }
    return 0;
}
