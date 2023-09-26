#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 101
#define SIZE 5

typedef struct node{
    int weight;
    int node;
    struct node*link;
}point,*ptr;

typedef ptr GraphA[SIZE];

typedef int GraphB[SIZE][SIZE];

void Floyd(GraphB,GraphA);
void display(GraphB);
void populate(GraphA);
void initialize(GraphB);
int findCenter(GraphB);
void insert(GraphA,int,int,int);

void main(){
	GraphA G;
	GraphB A;
	initialize(A);
	int x;
	for(x=0;x<SIZE;x++){
	   G[x]=NULL;
	}
	populate(G);
	Floyd(A,G);
	display(A);
	
	printf("\nCenter of Graph: %d",findCenter(A));
}

void display(GraphB A){
	int x,j;
	for(x=0;x<SIZE;x++){
		for(j=0;j<SIZE;j++){
			printf("%d\t",A[x][j]);
		}
		printf("\n");
	}
}

void initialize(GraphB A){
	int x,j;
	for(x=0;x<SIZE;x++){
		for(j=0;j<SIZE;j++){
			A[x][j]=MAX;
		}
	}
}


void populate(GraphA A){
    insert(A,0,1,10);
    insert(A,0,3,30);
    insert(A,0,4,100);
    insert(A,1,2,50);
    insert(A,2,0,20);
    insert(A,2,4,10);
    insert(A,3,2,20);
    insert(A,3,4,60);
}

void insert(GraphA A,int parent,int child,int weight){
    int x;
    ptr *trav;
    for(trav=&A[parent];*trav!=NULL;trav=&(*trav)->link){}
    if(*trav==NULL){
        *trav=(ptr)malloc(sizeof(struct node));
        if(*trav!=NULL){
            (*trav)->weight=weight;
            (*trav)->node=child;
            (*trav)->link=NULL;
        }
    }
}

void Floyd(GraphB A,GraphA C){
	int i,j,k;
	
	ptr trav;
	
	for(i=0;i<SIZE;i++){
		for(trav=C[i];trav!=NULL;trav=trav->link){
			A[i][trav->node]=trav->weight;
		}		
	}

	
	for(i=0;i<SIZE;i++){
		A[i][i]=0;
	}
	
	for(k=0;k<SIZE;k++){
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(A[i][k] + A[k][j] < A[i][j]){
					A[i][j] = A[i][k] + A[k][j];
				}
			}
		}
	}
}

int findCenter(GraphB A){
  int max, x, y;
  int ecc[SIZE];
  for(y=0; y<SIZE; y++){
    max = A[0][y];
    for(x=1; x<SIZE; x++){
      max = (max>A[x][y])? max : A[x][y];
    }
    ecc[y] = max;
  }
  max = 0;
  for(x=1; x<SIZE; x++){
    max = (ecc[max]<ecc[x])? max : x;
  }
  return max;
}
