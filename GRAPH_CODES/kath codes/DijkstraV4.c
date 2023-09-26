#include<stdio.h>
#include<stdlib.h>
#define MAX 101
#define SIZE 5

typedef struct node{
    int weight;
    int node;
    struct node*link;
}point,*ptr;

typedef ptr Graph[SIZE];

int * Dijkstra(Graph,int);
void insert(Graph,int,int,int);
void display(int []);
void populate(Graph);

void main(){
	Graph G;
	int x;
	for(x=0;x<SIZE;x++){
	   G[x]=NULL;
	}
	populate(G);
	int *nGraph=Dijkstra(G,0);
	display(nGraph);
}

void display(int A[]){
	int x;
	for(x=0;x<SIZE;x++){
		printf("%d ",A[x]);
	}
}

void populate(Graph A){
    insert(A,0,1,10);
    insert(A,0,2,MAX);
    insert(A,0,3,30);
    insert(A,0,4,100);
    insert(A,1,2,50);
    insert(A,2,0,20);
    insert(A,2,4,10);
    insert(A,3,2,20);
    insert(A,3,4,60);
}

void insert(Graph A,int parent,int child,int weight){
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

int * Dijkstra(Graph G,int startV){
	int *N, S[SIZE],Scount=0,x,y,i,w,min=69000,sum=0;
	
	int V[SIZE]={0,1,2,3,4};
	N=(int*)calloc(1,sizeof(int)*SIZE);
	
	ptr trav;
	
	if(N!=NULL){
		S[0]=startV;
		++Scount;
		
		
		for(trav=G[0];trav!=NULL;trav=trav->link){
		    N[trav->node]=trav->weight;
		}
		
		for(i=1;i<SIZE;i++){
		    min=69000;
			for(x=0;x<SIZE;x++){
				for(y=0;y<Scount && V[x]!=S[y];y++){}
				if(y==Scount && N[V[x]]<min){
					min=N[V[x]];
					w=V[x];	
				}
			}
			
			S[Scount]=w;
			++Scount;
			
			for(x=0;x<SIZE;x++){
				for(y=0;y<Scount && V[x]!=S[y];y++){}
					if(y==Scount){
					    for(trav=G[w];trav!=NULL && trav->node!=V[x];trav=trav->link){}
					    if(trav!=NULL){
    					    sum = N[w] + trav->weight;
    					    N[V[x]] = N[V[x]] < sum ? N[V[x]] : sum;
					    }
					}
			}
		}
	}
	return N;
}