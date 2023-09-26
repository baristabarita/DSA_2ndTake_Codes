#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef int dtype; //data type - can be changed to char,struct,etc.

typedef struct cell{
	int child;
	struct cell*link;
}*childList;

typedef struct node{
	dtype label;
	int parent;
	childList cList;
}Ntype;

typedef struct{
	int root;
	Ntype node[MAX];
}Tree;

void initialize(Tree*);
void insertRoot(Tree*,dtype);
void insertLeaf(Tree*,int,dtype);
void deleteLeaf(Tree*,dtype);
void populateTree(Tree*);

dtype label(Tree,int);
int root(Tree);
int isLeafV1(Tree,int);
int isLeafV2(Tree,int);
int parentV1(Tree,int);
int parentV2(Tree,int);
int leftmostChildV1(Tree,int);
int leftmostChildV2(Tree,int);
int rightSibV1(Tree,int);
int rightSibV2(Tree,int);

/*ADT GenTree Traversal*/
void displayPreorderRecur(Tree T, int node);
void displayPostorderRecur(Tree T, int node);
void displayInorderRecur(Tree T, int node);
void displayPreorderNonRecur(Tree T, int node);
void displayPostorderNonRecur(Tree T, int node);
void displayInorderNonRecur(Tree T, int node);

/*Custom Display*/
void displayTree(Tree T);

void main(){
	Tree A;
	initialize(&A);
	populateTree(&A);
	displayTree(A);

	printf("\n\nRoot of Tree : %d",root(A));

	//Version 1 & Version 2
	printf("\n\nParent of %d : %d",4,parentV1(A,4));
	printf("\nParent of %d : %d",4,parentV2(A,4));
	printf("\nParent of %d : %d",8,parentV1(A,8));
	printf("\nParent of %d : %d",8,parentV2(A,8));	
	

	//Version 1 & Version 2
	printf("\n\nLeftmost Child of %d : %d",0,leftmostChildV1(A,0));
	printf("\nLeftmost Child of %d : %d",0,leftmostChildV2(A,0));
	printf("\nLeftmost Child of %d : %d",5,leftmostChildV1(A,5));
	printf("\nLeftmost Child of %d : %d",5,leftmostChildV2(A,5));
	
	//Version 1 & Version 2
	printf("\n\nRight Sibling of %d : %d",3,rightSibV1(A,3));
	printf("\nRight Sibling of %d : %d",3,rightSibV2(A,3));
	printf("\nRight Sibling of %d : %d",7,rightSibV1(A,7));
	printf("\nRight Sibling of %d : %d",7,rightSibV2(A,7));

	//Version 1 & Version 2
	printf("\n\nIs %d a Leaf? [1/0] : %d",2,isLeafV1(A,2));
	printf("\nIs %d a Leaf? [1/0] : %d",2,isLeafV2(A,2));
	printf("\nIs %d a Leaf? [1/0] : %d",6,isLeafV1(A,6));
	printf("\nIs %d a Leaf? [1/0] : %d",8,isLeafV2(A,8));	
	
	printf("\n");
	deleteLeaf(&A,3); //Error: Not A Leaf
	deleteLeaf(&A,0); //Error: Does Not Exist
	deleteLeaf(&A,1);
	printf("\n\nLeftmost Child of %d : %d",0,leftmostChildV1(A,0));
	printf("\n\n");
	displayTree(A);


	printf("\n\nPreorder [Recursion]: ");
	displayPreorderRecur(A,0);
	printf("\nInorder [Recursion]: ");
	displayInorderRecur(A,0);
	printf("\nPostorder [Recursion]: ");
	displayPostorderRecur(A,0);	
	
	printf("\n\nPreorder [Non-Recursion]: ");
	displayPreorderNonRecur(A,0);
	printf("\nInorder [Non-Recursion]: ");
	displayInorderNonRecur(A,0);
	printf("\nPostorder [Recursion]: ");
	displayPostorderRecur(A,0);	
}

void displayTree(Tree T){
	int x;
	childList trav;
	printf("Index\t\tLabel\t\tParent\t\tChild\n------------------------------------------------------------");
	for(x=0;x<MAX;x++){
		printf("\n%d\t\t%d\t\t%d\t\t",x,T.node[x].label,T.node[x].parent);
		for(trav=T.node[x].cList;trav!=NULL;trav=trav->link){
			printf("%d ",trav->child);
		}
	}	
}

void initialize(Tree*T){
	int x;
	T->root=-1;
	for(x=0;x<MAX;x++){
		T->node[x].parent=-2;
		T->node[x].label=-2;
		T->node[x].cList=NULL;
	}
}

void insertRoot(Tree*T,dtype label){
	int x;
	if(T->root==-1){
		T->node[0].label=label;
		T->node[0].parent=-1;
		T->root=0;
	}else{
		for(x=0;x<MAX && T->node[x].parent!=-1;x++){}
		if(x<MAX){
			T->node[T->root].parent=x;
			T->node[x].label=label;
			T->node[x].parent=-1;
			T->node[x].cList=(childList)calloc(1,sizeof(struct cell));
			T->node[x].cList->child=T->root;
			T->root=x;
		}
	}
}

void insertLeaf(Tree*T,int parent,dtype label){
	int x;
	childList *trav;
	if(T->node[parent].parent!=-2){
		for(x=0;x<MAX && T->node[x].parent!=-2;x++){}
		T->node[x].label=label;
		T->node[x].parent=parent;
		for(trav=&T->node[parent].cList; *trav!=NULL;trav=&(*trav)->link){}
		(*trav)=(childList)calloc(1,sizeof(struct cell));
		(*trav)->child=x;
		(*trav)->link=NULL;
	}
}

void deleteLeaf(Tree*T,dtype label){
	int x;
	childList *trav,temp;
	for(x=0;x<MAX && T->node[x].label!=label;x++){}
	if(x<MAX){
		if(T->node[x].cList==NULL){//Or put the x<MAX in this condition
			for(trav=&T->node[T->node[x].parent].cList; (*trav)->child!=x ;trav=&(*trav)->link){}
			temp=*trav;
			*trav=temp->link;
			free(temp);
			T->node[x].label=-2;
			T->node[x].parent=-2;
		}else{
			printf("\nError: Can't be Deleted! Not A Leaf.");
		}
	}else{
		printf("\nError: Can't Be Deleted! Does Not Exist.");
	}
}

void populateTree(Tree*T){
	insertRoot(T,9);
	insertLeaf(T,0,1);
	insertLeaf(T,0,2);
	insertLeaf(T,0,3);
	insertLeaf(T,2,4);
	insertLeaf(T,2,5);
	insertLeaf(T,3,6);
	insertLeaf(T,5,7);
	insertLeaf(T,5,8);
}

dtype label(Tree T,int node){
	dtype dummy=-1;
	dtype ret=dummy;
	if(node>=0 && node<MAX && T.node[node].parent!=-2){
		ret=T.node[node].label;
	}	
	return ret;
}

int root(Tree T){
	return T.root;
}

int isLeafV1(Tree T,int node){
	int x=0;
	if(node>=0 && node<MAX){
		for(;x<MAX && T.node[x].parent!=node;x++){}
	}
	return (x==MAX) ? 1 : 0;
}

int isLeafV2(Tree T,int node){
	return (node>=0 && node<MAX && T.node[node].cList==NULL)?1:0;
}

int parentV1(Tree T,int node){
	return (node>=0 && node<MAX) ? T.node[node].parent : -1;	
}

int parentV2(Tree T,int node){
	int x,isMatch=0;
	childList trav;
	if(node>=0 && node<MAX){
		for(x=0;x<MAX && isMatch==0;x++){
			for(trav=T.node[x].cList;trav!=NULL && trav->child!=node;trav=trav->link){}
			if(trav!=NULL){
				isMatch=1;
			}
		}
	}
	return (isMatch==1) ? x-1 : -1;	
}

int leftmostChildV1(Tree T,int node){
	int x=-1;
	if(node>=0 && node<MAX){
		for(x=0;x<MAX && T.node[x].parent!=node;x++){}
	}	
	return (x>=0 && x<MAX) ? x : -1;
}

int leftmostChildV2(Tree T,int node){
	int ret=-1;
	if(node>=0 && node<MAX && T.node[node].cList!=NULL){
		ret=T.node[node].cList->child;
	}
	return ret;
}

int rightSibV1(Tree T,int node){
	int x=-1,parent;
	if(node>=0 && node<MAX){
		parent=T.node[node].parent; /*parent variable is not necessary*/
		for(x=node+1;x<MAX && T.node[x].parent!=parent;x++){}
	}
	return (x>=0 && x<MAX) ? x : -1;
}

int rightSibV2(Tree T,int node){
	int x,isMatch=0;
	childList trav;
	if(node>=0 && node<MAX){
		for(x=0;x<MAX && isMatch==0;x++){
			for(trav=T.node[x].cList;trav!=NULL && trav->child!=node;trav=trav->link){}
			if(trav!=NULL){
				isMatch=1;
				trav=trav->link;
			}
		}
	}
	return (isMatch==1 && trav!=NULL) ? trav->child : -1;
}

/*ADT GenTree Traversal*/
void displayPreorderRecur(Tree T, int node){
	if (node>=0 && node<MAX){
		int nextNode;
		printf("%d ",label(T,node));
		nextNode=leftmostChildV2(T,node);
		while(nextNode!=-1){
			displayPreorderRecur(T,nextNode);
			nextNode=rightSibV1(T,nextNode);
		}
	}
}

void displayPostorderRecur(Tree T, int node){
	if (node>=0 && node<MAX){
		int nextNode;
		nextNode=leftmostChildV2(T,node);
		while(nextNode!=-1){
			displayPostorderRecur(T,nextNode);
			nextNode=rightSibV1(T,nextNode);
		}
		printf("%d ",label(T,node));
	}
}

void displayInorderRecur(Tree T,int node){
	if(node>=0 && node<MAX){
		int nextNode=leftmostChildV2(T,node);
		displayInorderRecur(T,nextNode);
		printf("%d ",label(T,node));
		while(nextNode!=-1){
			nextNode=rightSibV1(T,nextNode);
			displayInorderRecur(T,nextNode);
		}
	}		
}

void displayPreorderNonRecur(Tree T, int node){
	if(node>=0 && node<MAX){
		int stack[MAX];
		int top=-1,n;
		
		stack[++top]=node;
		while(top!=-1){
			n=stack[top];
			printf("%d ",label(T,n));
			top--;
			if(rightSibV1(T,n)!=-1){
				stack[++top]=rightSibV1(T,n);
			}
			if(leftmostChildV2(T,n)!=-1){
				stack[++top]=leftmostChildV2(T,n);
			}
		}
	}
}

void displayInorderNonRecur(Tree T, int node){
	if(node>=0 && node<MAX){
		int stack[MAX];
		int top=-1,curr;
		
		curr=node;
		while(curr!=-1 || top!=-1){
			if(curr!=-1){
				stack[++top]=curr;
				curr=leftmostChildV2(T,curr);
			}else{
				curr=stack[top];
				top--;
				printf("%d ",label(T,curr));
				curr=leftmostChildV2(T,curr);
				curr=rightSibV1(T,curr); 
				
			}
		}
	}
}

void displayPostorderNonRecur(Tree T, int node){
	if(node>=0 && node<MAX){
		int stack[MAX];
		int top=-1,curr;
		
		curr=node;
		while(curr!=-1 || top!=-1){
			if(curr!=-1){
				stack[++top]=curr;
				curr=leftmostChildV2(T,curr);
			}else{
				curr=stack[top];
				top--;
				printf("%d ",label(T,curr));
				curr=rightSibV1(T,curr); 
			}
		}
	}
}