#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

typedef int Tree[SIZE];
typedef int node;

void initialize(Tree); //the same as makeNull
node root(Tree);
node rightSibling(Tree,node);
node leftmostChild(Tree,node);
node parent(Tree,node);
int isLeaf(Tree,node);

/*Can be used instead of create*/
void insertChild(Tree,node,node);

/*display*/
void display(Tree);
void preorder(Tree,node);
void inorder(Tree,node);
void postorder(Tree,node);

void main(){
	Tree A;
	initialize(A);
	printf("--> Initialize\n");
	display(A);
	printf("\n--> Insert\n");
	insertChild(A,0,5);
	insertChild(A,1,6);
	insertChild(A,2,5);
	insertChild(A,3,6);
	insertChild(A,4,1);
	insertChild(A,5,-1);
	insertChild(A,6,5);
	insertChild(A,7,1);
	insertChild(A,8,2);
	display(A);
	printf("\n--> Leaf \n");
	printf("Is %d a leaf? %d",0,isLeaf(A,0));
	printf("\nIs %d a leaf? %d",1,isLeaf(A,1));
	printf("\n\n--> Traversals\n");
	printf("PREORDER | ");
	preorder(A,root(A)); //5 0 2 8 6 1 4 7 3
	printf("\nINORDER | ");
	inorder(A,root(A)); //0 5 8 2 4 1 7 6 3
	printf("\nPOSTORDER | ");
	postorder(A,root(A)); //0 8 2 4 7 1 3 6 5
}

void initialize(Tree A){
	int x;
	for(x=0;x<SIZE;x++){
		A[x]=-2;
	}
}

node root(Tree A){
	int x;
	for(x=0;x<SIZE && A[x]!=-1;x++){}
	return x<SIZE ? x : -1;
}

void insertChild(Tree A,node b,node c){
	//Can add condition or not
		A[b]=c;
}

node rightSibling(Tree A,node b){
	int x;
	for(x=b+1;x<SIZE && A[x]!=A[b];x++){}
	return x<SIZE ? x : -1;
}

node leftmostChild(Tree A,node b){
	int x;
	for(x=0;x<SIZE && A[x]!=b;x++){}
	return x<SIZE ? x : -1;
}

node parent(Tree A,node b){
	return (b>=0 && b<SIZE) ? A[b] : -1; /*May add condition to be sure*/
}

int isLeaf(Tree A,node b){
	int x=0;
	if(b>=0 && b<SIZE){
		for(;x<SIZE && A[x]!=b;x++){}
	}
	return x==SIZE && A[b]!=-2 ? 1 : 0;
}

void display(Tree A){
	int x;
	for(x=0;x<SIZE;x++){
		printf("%d | %d\n",x,A[x]);
	}
}

void preorder(Tree A,node b){
    if(b!=-1){
    	printf("%d ",b);
    	preorder(A,leftmostChild(A,b));
    	preorder(A,rightSibling(A,b));
	}
}

void inorder(Tree A, node b){
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

void postorder(Tree A,node b){
    if(b!=-1){
    	postorder(A,leftmostChild(A,b));
    	printf("%d ",b);
    	postorder(A,rightSibling(A,b));
	}	
}
