#include<stdio.h>
#include<stdlib.h>
#define MAX 101
#define SIZE 5

typedef int Graph[SIZE][SIZE];
typedef int Vertex[SIZE]; //Using Bit Vector

void initialize(Graph);
void populate(Graph);
Vertex *Dijkstra(Graph,int);

void display(Vertex*);


void main(){
	Graph A;
	initialize(A);
	populate(A);
	Vertex*C=Dijkstra(A,0);
	display(C);
}

void display(Vertex*A){
	int x;
	for(x=0;x<SIZE;x++){
		printf("%d ",(*A)[x]);
	}
}

void initialize(Graph A){
	int x,j;
	for(x=0;x<SIZE;x++){
		for(j=0;j<SIZE;j++){
			A[x][j]=MAX;
		}
	}
}

void populate(Graph A){
	A[0][1]=10;
	A[0][3]=30;
	A[0][4]=100;
	A[1][2]=50;
	A[2][0]=20;
	A[2][4]=10;
	A[3][2]=20;
	A[3][4]=60;
}

Vertex *Dijkstra(Graph C,int start){
    int i,x,j,sum=0,w,min;
    Vertex A;
    Vertex S = {1,0,0,0,0};
        
    Vertex * D = (Vertex*)calloc(1,sizeof(Vertex));
    
    if(D!=NULL){
        
        for(i=1;i<SIZE;i++){
            (*D)[i]=C[start][i]; //Initializes D
        }
        
        for(i=1;i<SIZE;i++){ //Difference
            min=MAX;
            for(x=0;x<SIZE;x++){
                A[x] = 1 & ~ S[x];
            }            
            
            for(x=0;x<SIZE;x++){ //Chooses a vertex except the source vertex
                if(A[x]==1){
                    for(j=x+1;j<SIZE;j++){
                        if(A[j]==1){
                            if((*D)[x] < min && (*D)[j] < min){
                                w = (*D)[x] < (*D)[j] ? x : j;
                                min = (*D)[w];
                            }
                        }
                    }
                }
            }
            S[w]=1;
            A[w]=0;
            
            for(x=1;x<SIZE;x++){
                if(A[x]==1){
                    sum = (*D)[w] + C[w][x];
                    (*D)[x] = (*D)[x] < sum ? (*D)[x] : sum;
                }
            }
        }
    }
    return D;
}
