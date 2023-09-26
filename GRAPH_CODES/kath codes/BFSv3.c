#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
#define VISITED -1
#define UNVISITED -2

typedef struct node{
	int elem;
	struct node*link;
}*ptr;

typedef ptr Graph[SIZE];

typedef struct cell{
    int child;
    struct cell*next;
}*Header;

typedef struct{
    Header H[SIZE];
    int root;
}Tree;

typedef struct{
	int elem[SIZE];
	int front,rear;
}Queue;

//Mark
struct{
	int vertex[SIZE];
	int count;	
}mark;

void enqueue(int,Queue*);
int front(Queue);
void initGraph(Graph);
void dequeue(Queue*);
void populate(Graph);
void insertVertex(int,int,Graph);
void bfs(Graph A,int vertex);
void displayGraph(Graph L);
void initMark();
void insertChild(Tree*,int,int);
void displayTree(Tree);

Tree gen;

void main(){
	Graph A;
	initGraph(A);
	initMark();
	initTree();
	populate(A);
		displayGraph(A);
		
	int root=4;
	gen.root=root;
	bfs(A,4);
	if(mark.count<SIZE){
		int x;
		for(x=0;mark.vertex[x]!=UNVISITED;x++){}
		bfs(A,x);
	}
	printf("\n\nRoot: %d\n",gen.root);
	displayTree(gen);
	
}

void initQueue(Queue*A){
	A->front=0;
	A->rear=-1;
}

void initTree(){
    int x;
    for(x=0;x<SIZE;x++){
        gen.H[x]=NULL;
    }
}

void insertChild(Tree*T,int parent,int child){
    Header*trav;
    for(trav=&T->H[parent]; *trav!=NULL && (*trav)->child!=child;trav=&(*trav)->next){}
    if(*trav==NULL){
        *trav=(Header)malloc(sizeof(struct cell));
        if(*trav!=NULL){
            (*trav)->child=child;
            (*trav)->next=NULL;
        }
    }
}

void displayTree(Tree A){
	Header trav;
	int x;
	
	for(x=0;x<SIZE;x++){
		printf("%d | ",x);
		if(A.H[x]==NULL){
			printf("NULL");
		}else{
			for(trav=A.H[x];trav!=NULL;trav=trav->next){
				printf("%d ",trav->child);
			}
		}		
		printf("\n");
	}    
}

void enqueue(int elem,Queue*Q){
	if((Q->rear+2)%SIZE!=Q->front){
		Q->rear=(Q->rear+1)%SIZE;
		Q->elem[Q->rear]=elem;
	}	
}

void initMark(){
	int x;
	for(x=0;x<SIZE;x++){
		mark.vertex[x]=UNVISITED;
	}
	mark.count=0;
}

void initGraph(Graph A){
	int x;
	for(x=0;x<SIZE;x++){
		A[x]=NULL;
	}	
}

int front(Queue Q){
	return (Q.rear+1)%SIZE!=Q.front ? Q.elem[Q.front] : -1;
}

void dequeue(Queue*Q){
	if((Q->rear+1)%SIZE!=Q->front){
		Q->front=(Q->front+1)%SIZE;
	}
}

void populate(Graph L){
  insertVertex(0, 1, L);
  insertVertex(0, 2, L);
  insertVertex(1, 2, L);
  insertVertex(1, 3, L);
  insertVertex(2, 0, L);
  insertVertex(3, 0, L);
  insertVertex(3, 2, L);
  insertVertex(4, 5, L);
  insertVertex(4, 6, L);
  insertVertex(5, 1, L);
  insertVertex(6, 3, L);
  insertVertex(6, 5, L);	
}

void insertVertex(int parent,int child,Graph G){
	ptr *trav;
	for(trav=&G[parent];(*trav)!=NULL;trav=&(*trav)->link){}
	if(*trav==NULL){
		*trav=(ptr)malloc(sizeof(struct node));
		if(*trav!=NULL){
			(*trav)->elem=child;
			(*trav)->link=NULL;
		}
	}
}

void displayGraph(Graph L){
    int x;
    ptr ptr;
    for(x=0; x<SIZE; x++){
        printf("%d -> ", x);
        for(ptr=L[x]; ptr!=NULL; ptr = ptr->link){
            printf("%d -> ", ptr->elem);
        }
        printf("NULL\n");
    }
}

void bfs(Graph A,int vertex){
	Queue Q;
	initQueue(&Q);
	ptr trav;
	int x,y;
	mark.vertex[vertex]=VISITED;
	mark.count++;
	enqueue(vertex,&Q);
	while((Q.rear+1)%SIZE!=Q.front){
		x = front(Q);
		printf("%d ",x);
		dequeue(&Q);
		for(trav=A[x];trav!=NULL;trav=trav->link){
			y=trav->elem;
			if(mark.vertex[y]==UNVISITED){
				mark.vertex[y]=VISITED;
				mark.count++;
				enqueue(y,&Q);
				insertChild(&gen,x,y);
			}
		}
	}
}