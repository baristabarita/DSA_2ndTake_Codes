#include<stdio.h>
#include<stdlib.h>
#define MAX 101
#define SIZE 5

typedef int Graph[SIZE][SIZE];
typedef int Vertex[SIZE]; //Using Array Imp

void initialize(Graph);
void populate(Graph);
Vertex *Dijkstra(Graph,Vertex,int);

void display(Vertex*);


void main(){
	Graph A;
	initialize(A);
	populate(A);
	Vertex B = {0,1,2,3,4};
	Vertex*C=Dijkstra(A,B,0);
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

Vertex *Dijkstra(Graph C,Vertex V,int start){
	int S[SIZE],i,x,j,sum=0,w,Scount=0,min=MAX;
	
	Vertex * D = (Vertex*)calloc(1,sizeof(Vertex));
	
	if(D!=NULL){
		S[Scount++]=start;
		
		for(i=1;i<SIZE;i++){
			(*D)[i]=C[start][i]; //Initializes D
		}
		
		for(i=1;i<SIZE;i++){
			for(x=0;x<SIZE;x++){
				for(j=0;j<Scount && V[x]!=S[j];j++){}
	   				if(j==Scount && (*D)[V[x]] < min){
	   					min=(*D)[V[x]];
						w=V[x];
    				}
			}
			
			S[Scount++]=w;
			
			for(x=0;x<SIZE;x++){
				for(j=0;j<Scount && V[x]!=S[j];j++){}
	   				if(j==Scount){
	   					sum = (*D)[w] + C[w][V[x]];
						(*D)[V[x]]= (*D)[V[x]] < sum ? (*D)[V[x]] : sum;
    				}
			}
			min=MAX;			
		}
	}
	return D;
}
