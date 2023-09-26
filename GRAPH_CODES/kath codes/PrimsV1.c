#include<stdio.h>
#include<stdlib.h>
#define SIZE 6

typedef int Graph[SIZE][SIZE];

int Prim(Graph,int [],int);
void display(int []);

void main(){
    Graph A={{999,1,5,4,6,5},
             {1,999,5,999,999,6},
             {5,5,999,2,999,999},
             {4,999,2,999,1,999},
             {6,999,999,1,999,3},    
             {5,6,999,999,3,999},    
            };
    int V[]={0,1,2,3,4,5};
    printf("%d",Prim(A,V,0));
}

int Prim(Graph A,int V[],int start){
    int U[SIZE],a,b,c,d,count=0,min,cost=0;
    
    U[count++]=start;
    while(count!=SIZE){
        min=999;
        for(a=0;a<SIZE;a++){
            for(c=0;c<count && V[a]!=U[c];c++){}
            if(c==count){
                for(b=0;b<count;b++){
                    if(A[U[b]][V[a]] < min){ //999 can be 0 then add A[U[b]][V[a]]!=0
                          d=V[a];
                          min=A[U[b]][V[a]];
                    }
                }
            }
        }
        printf("%d\n",min);
        cost +=min;
        U[count++]=d;
        
        
    }
    return cost;
}