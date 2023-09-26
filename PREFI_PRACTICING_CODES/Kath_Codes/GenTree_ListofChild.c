#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

typedef struct cell{
	int child;
	struct cell*next;
}*Header;

typedef struct{
   Header H[SIZE];
   int Root;
}Tree;

void initialize(Tree*); //the same as makeNull
int root(Tree);
int rightSibling(Tree,int);
int leftmostChild(Tree,int);
int parent(Tree,int);
int isLeaf(Tree,int);

/*Can be used instead of create*/
void insertChild(Tree*,int,int);
void insertRoot(Tree*,int);

/*display*/
void display(Tree);
void preorder(Tree,int);
void inorder(Tree,int);
void postorder(Tree,int);

void main(){
	Tree A;
	initialize(&A);
	printf("--> Initialize\n");
	display(A);
	printf("\n--> Insert\n");
	insertRoot(&A,5);
	insertChild(&A,0,5);
	insertChild(&A,6,5);
	insertChild(&A,2,5);
	insertChild(&A,3,6);
	insertChild(&A,1,6);
	insertChild(&A,8,2);
	insertChild(&A,4,1);
	insertChild(&A,7,1);
	display(A);
	printf("\n--> Parent\n");
	printf("Parent of %d: %d",8,parent(A,8));
	printf("\nParent of %d: %d",5,parent(A,5));
	
	printf("\n--> isLeaf\n");
	printf("Is %d a leaf? : %d",3,isLeaf(A,3));
	printf("\nIs %d a leaf? : %d",5,isLeaf(A,5));
	printf("\n--> Traversals\n");
	printf("PREORDER | ");
	preorder(A,root(A)); //5 0 6 3 1 4 7 2 8
	printf("\nINORDER | ");
	inorder(A,root(A)); //0 5 3 6 4 1 7 8 2
	printf("\nPOSTORDER | ");
	postorder(A,root(A)); //0 3 4 7 1 6 8 2 5
}

void initialize(Tree*A){
	int x;
	A->Root=-1;
	for(x=0;x<SIZE;x++){
		A->H[x]=NULL;
	}
}//the same as makeNull

int root(Tree A){
	return A.Root;
}

int rightSibling(Tree A,int node){
	Header trav;
	int x=-1,match=0;
	if(node>=0 && node<SIZE){
		for(x=0;x<SIZE && match==0;x++){
			for(trav=A.H[x]; trav!=NULL && trav->child!=node;trav=trav->next){}
			if(trav!=NULL){
				match=1;
				trav=trav->next;
			}
		}
	}
	return (match==1 && trav!=NULL) ? trav->child : -1;
}

int leftmostChild(Tree A,int node){
	return (node>=0 && node<SIZE && A.H[node]!=NULL) ? A.H[node]->child : -1;
}

int parent(Tree A,int node){
	Header trav;
	int x,match=0;
	if(node>=0 && node<SIZE){
		for(x=0;x<SIZE && match==0;x++){
			for(trav=A.H[x];trav!=NULL && trav->child!=node;trav=trav->next){}	
			if(trav!=NULL){
				match=1;
			}		
		}
	}
	return match==1 ? x-1 : -1;
}

int isLeaf(Tree A,int node){
	return (node>=0 && node<SIZE && A.H[node]==NULL) ? 1 : 0;
}

/*Can be used instead of create*/
void insertRoot(Tree*T,int node){
    if(T->Root != -1){
        T->H[node] = (Header)malloc(sizeof(struct cell));
        T->H[node]->child = T->Root;
        T->H[node]->next = NULL;
    }
    T->Root = node;	
}

void insertChild(Tree*T,int child,int parent){
	Header *trav;
	for(trav=&T->H[parent]; *trav!=NULL;trav=&(*trav)->next){}
	*trav=(Header)malloc(sizeof(struct cell));
	if(*trav!=NULL){
		(*trav)->child=child;
		(*trav)->next=NULL;
	}
}

/*display*/
void display(Tree A){
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

void preorder(Tree T,int node){
  if(node>=0 && node<SIZE){
    int next;
    printf("%d ",node);
    next=leftmostChild(T,node);
    while(next!=-1){
       preorder(T,next);
       next=rightSibling(T,next);
    }
  }
}

void inorder(Tree A, int b){
    int temp;
	if(b!=-1){
    	temp=leftmostChild(A,b);
    	inorder(A,temp);
    	printf("%d ",b);
    	while(temp!=-1){
    		temp = rightSibling(A,temp);
			inorder(A,temp);
    	}
	}
}

void postorder(Tree T,int node){
  if(node>=0 && node<SIZE){
    int next;
    next=leftmostChild(T,node);
    while(next!=-1){
       postorder(T,next);
       next=rightSibling(T,next);
    }
    printf("%d ",node);
  }
}