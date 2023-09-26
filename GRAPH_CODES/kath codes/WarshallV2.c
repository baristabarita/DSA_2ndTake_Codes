#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 101
#define SIZE 5

typedef struct node{
    int node;
    struct node*link;
}point,*ptr;

typedef ptr GraphA[SIZE];

typedef int GraphB[SIZE][SIZE];

void Warshall(GraphB,GraphA);
void display(GraphB);
void populate(GraphA);
void initialize(GraphB);
void insert(GraphA,int,int);

void main(){
	GraphA G;
	GraphB A;
	initialize(A);
	int x;
	for(x=0;x<SIZE;x++){
	   G[x]=NULL;
	}
	populate(G);
	Warshall(A,G);
	display(A);
	
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
			A[x][j]=0;
		}
	}
}


void populate(GraphA A){
    int i,j;
    insert(A,0,0);
    insert(A,0,1);
    insert(A,0,2);
    insert(A,0,3);
    insert(A,0,4);
    for(i=1;i<SIZE-1;i++){
        for(j=1;j<SIZE;j++){
            insert(A,i,j);
        }
    }
    insert(A,4,2);
	insert(A,4,3);
	insert(A,4,4);
}

void insert(GraphA A,int parent,int child){
    int x;
    ptr *trav;
    for(trav=&A[parent];*trav!=NULL;trav=&(*trav)->link){}
    if(*trav==NULL){
        *trav=(ptr)malloc(sizeof(struct node));
        if(*trav!=NULL){
            (*trav)->node=child;
            (*trav)->link=NULL;
        }
    }
}

void Warshall(GraphB A,GraphA C){
	int i,j,k;
	
	ptr trav;
	
	for(i=0;i<SIZE;i++){
		for(trav=C[i];trav!=NULL;trav=trav->link){
			A[i][trav->node]=1;
		}		
	}
	
	for(k=0;k<SIZE;k++){
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(A[i][j]==0){
					A[i][j] = A[i][k] && A[k][j];
				}
			}
		}
	}
}
