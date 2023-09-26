
#include<stdio.h>
#include<stdlib.h>
#define N 8

typedef struct node{
	int elem;
	struct node * LC;
	struct node * RC;	
}*BST;

typedef int SET[N];

void initialize(BST*);
void insert(BST*,int);
int isMember(BST,int);
void deleteV1(BST*,int);
void deleteV2(BST*,int);
int deleteMin(BST*);
int deleteMax(BST*);

/*Display*/
void preorder(BST);
void inorder(BST);
void postorder(BST);

void display(BST);

void main(){
	BST Tree;
	int x;
	
	printf("Task 1: Initialize\n-----------------------------\n");
	initialize(&Tree);
	display(Tree);
	
	printf("\n\nTask 2: Insert\n-----------------------------");
	SET A={10,5,14,12,7,18,15,11};
	for(x=0;x<N;x++){
		insert(&Tree,A[x]);
	}
	display(Tree);
	insert(&Tree,7);
	display(Tree);
	printf("\n\nTask 3: isMember\n-----------------------------\n");
	printf("Is %d a Member? %d",5,isMember(Tree,5));
	printf("\nIs %d a Member? %d",13,isMember(Tree,13));	
	
	printf("\n\nTask 4: Delete\n-----------------------------");
	deleteV1(&Tree,15); //Deleting a leaf
	deleteV1(&Tree,12); //Deleting an inode with a left child only
	deleteV1(&Tree,5); //Deleting an inode with a right child only
	deleteV1(&Tree,10); //Deleting an inode with 2 children
	
	/*deleteV2(&Tree,15);
	deleteV2(&Tree,12);
	deleteV2(&Tree,5);
	deleteV2(&Tree,10);*/
	
	display(Tree);
	
	printf("\n\nSmallest Element: %d",deleteMin(&Tree));
	printf("\nLargest Element: %d",deleteMax(&Tree));
}

void initialize(BST*A){
	*A=NULL;
}

void insert(BST*A,int elem){
	BST *trav;

	for(trav=A; *trav!=NULL && elem!=(*trav)->elem;){
		trav = elem < (*trav)->elem ? &(*trav)->LC : &(*trav)->RC;
	}
	
	if(*trav==NULL){
		*trav=(BST)malloc(sizeof(struct node));
		if(*trav!=NULL){
			(*trav)->elem=elem;
			(*trav)->LC=(*trav)->RC=NULL;
		}
	}
}

int isMember(BST A,int elem){
	BST trav;
	for(trav=A;trav!=NULL && elem!=trav->elem;){
		trav= elem < trav->elem ? trav->LC : trav->RC;
	}
	return trav!=NULL ? 1 : 0;
}

void deleteV1(BST*S,int elem){
	BST *A,*B,temp;
	
	for(A=S; *A!=NULL && (*A)->elem!=elem;){
		A = elem < (*A)->elem ? &(*A)->LC : &(*A)->RC;
	}
	
	if(*A!=NULL){
		if((*A)->LC==NULL || (*A)->RC==NULL){
			temp=*A;
			if((*A)->LC==NULL){
				*A=temp->RC; //can be (*A)->RC
			}else{
				*A=temp->LC;
			}
		}else{ /*Can be changed to deleteMax*/
			for(B=&(*A)->RC; (*B)->LC!=NULL;B=&(*B)->LC){}
			(*A)->elem=(*B)->elem;
			temp=*B;
			*B=temp->RC; 
		}	
		free(temp);
	}
}

void deleteV2(BST*S,int elem){
	BST *A,*B,temp;
	
	for(A=S; *A!=NULL && (*A)->elem!=elem;){
		A = elem < (*A)->elem ? &(*A)->LC : &(*A)->RC;
	}
	
	if(*A!=NULL){
		if((*A)->LC==NULL || (*A)->RC==NULL){
			temp=*A;
			if((*A)->LC==NULL){
				*A=(*A)->RC;
			}else{
				*A=(*A)->LC;
			}
			free(temp);
		}else{ /*Can be changed to deleteMax*/
			(*A)->elem=deleteMin(&(*A)->RC);
		}
	}	
}

int deleteMin(BST*A){
	BST *trav,temp;
	int retVal;
	if(*A!=NULL){
		for(trav=A;(*trav)->LC!=NULL;trav=&(*trav)->LC){}
		retVal=(*trav)->elem;
		temp=*trav;
		*trav=temp->RC;
		free(temp);
	}
	return retVal;
}

int deleteMax(BST*A){
	BST *trav,temp;
	int retVal;
	if(*A!=NULL){
		for(trav=A;(*trav)->RC!=NULL;trav=&(*trav)->RC){}
		retVal=(*trav)->elem;
		temp=*trav;
		*trav=temp->LC;
		free(temp);
	}
	return retVal;
}

void preorder(BST T){
	if(T!=NULL){
		printf("%d ",T->elem);
		preorder(T->LC);
		preorder(T->RC);
	}
}

void inorder(BST T){
	if(T!=NULL){
		inorder(T->LC);
		printf("%d ",T->elem);
		inorder(T->RC);
	}
}

void postorder(BST T){
	if(T!=NULL){
		postorder(T->LC);
		postorder(T->RC);
		printf("%d ",T->elem);
	}
}

void display(BST T){
	if(T!=NULL){
		printf("\n\nPreorder | ");
		preorder(T);
		printf("\nInorder | ");
		inorder(T);
		printf("\nPostorder | ");
		postorder(T);
	}else{
		printf("\nBST is Empty");
	}
}