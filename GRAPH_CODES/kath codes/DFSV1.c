#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
//can use bit vector or computer word for visited or unvisited
#define VISITED -1
#define UNVISITED -2 

typedef struct node{
	int label;
	struct node*link;
}*ptr;

typedef ptr Graph[SIZE];

int count=0; //Global variable for mark count

void initGraph(Graph);
void initMarked(int[]);
void populateGraph(Graph);
void insert(int,int,Graph);
void dfs(Graph,int,int[]);

void main(){
	Graph A;
	int mark[SIZE];
	initGraph(A);
	initMarked(mark);
	populateGraph(A);
	dfs(A,0,mark);
	if(count<SIZE-1){
		dfs(A,count,mark);
	}
	
}

void initGraph(Graph A){
	int x;
	for(x=0;x<SIZE;x++){
		A[x]=NULL;
	}
}

void initMarked(int mark[]){
	int i;
	for(i=0;i<SIZE;i++){
		mark[i]=UNVISITED;
	}
}

void populateGraph(Graph A){
	insert(0,1,A);
	insert(0,2,A);
	insert(1,2,A);
	insert(1,3,A);
	insert(2,0,A);
	insert(3,0,A);
	insert(3,2,A);
	insert(4,5,A);
	insert(4,6,A);
	insert(5,1,A);
	insert(6,3,A);
	insert(6,5,A);
}

void insert(int ancestor,int desc,Graph A){
	ptr *trav;
	for(trav=&A[ancestor];*trav!=NULL && (*trav)->label!=desc;trav=&(*trav)->link){}
	if(*trav==NULL){
		*trav=(ptr)malloc(sizeof(struct node));
		if(*trav!=NULL){
			(*trav)->label=desc;
			(*trav)->link=NULL;
		}
	}
}

void dfs(Graph A,int vertex,int mark[]){
	int w;
	mark[vertex]=VISITED;
	ptr trav;
	count++;
	printf("Now at node %d \n",vertex);
	for(trav=A[vertex];trav!=NULL;trav=trav->link){
		w=trav->label;
		if(mark[w]==UNVISITED){
			dfs(A,w,mark);
		}
	}
}