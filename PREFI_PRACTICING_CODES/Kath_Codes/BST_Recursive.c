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
	deleteV2(&Tree,10);*/

	display(Tree);

	printf("\n\nSmallest Element: %d",deleteMin(&Tree));
	printf("\nLargest Element: %d",deleteMax(&Tree));
}

void initialize(BST*A){
	*A=NULL;
}

void insert(BST*T,int elem){
	BST *A;
	A=T;
	if(*A==NULL){
		*A=(BST)malloc(sizeof(struct node));
		if(*A!=NULL){
			(*A)->elem=elem;
			(*A)->LC=(*A)->RC=NULL;
		}
	}else if(elem!=(*A)->elem){
		elem < (*A)->elem ? insert(&(*A)->LC,elem) : insert(&(*A)->RC,elem);
	}else{
		printf("\nCannot Insert Node.\n");
	}
}

int isMember(BST T,int elem){
	if(T==NULL){
		return 0;
	}else if(T->elem==elem){
		return 1;
	}else{
		return elem < T->elem ? isMember(T->LC,elem) : isMember(T->RC,elem);
	}
}

void deleteV1(BST*S,int elem){
	BST temp;
	if((*S)==NULL){
		printf("\nElem/Node not found"); //Can use return; but not sure if it is advised
	}else if((*S)->elem==elem){
		if((*S)->LC==NULL || (*S)->RC==NULL){
			temp=*S;
			if((*S)->RC!=NULL){
				*S=temp->RC;
			}else{
				*S=temp->LC;
			}
			free(temp);
		}else{
			(*S)->elem=deleteMin(&(*S)->RC);
		}
	}else{
		elem < (*S)->elem ? deleteV1(&(*S)->LC,elem) : deleteV1(&(*S)->RC,elem);
	}	
}

void deleteV2(BST*S,int elem){
	BST temp;
	if((*S)==NULL){
		printf("\nElem/Node not found"); //Can use return; but not sure if it is advised
	}else if((*S)->elem==elem){
		if((*S)->LC==NULL || (*S)->RC==NULL){
			temp=*S;
			if((*S)->RC!=NULL){
				*S=temp->RC;
			}else{
				*S=temp->LC;
			}
			free(temp);
		}else{
			(*S)->elem=deleteMax(&(*S)->LC);
		}
	}else{
		elem < (*S)->elem ? deleteV2(&(*S)->LC,elem) : deleteV2(&(*S)->RC,elem);
	}	
}

int deleteMin(BST*A){
	BST*trav,temp;
	int ret;
	
	trav=A;
	if((*trav)->LC==NULL){
		temp=*trav;
		ret=temp->elem;
		*trav=temp->RC;
		free(temp);
		return ret;
	}else{
		return deleteMin(&(*trav)->LC);
	}
}

int deleteMax(BST*A){
	BST*trav,temp;
	int ret;
	
	trav=A;
	if((*trav)->RC==NULL){
		temp=*trav;
		ret=temp->elem;
		*trav=temp->LC;
		free(temp);
		return ret;
	}else{
		return deleteMax(&(*trav)->RC);
	}
}

/*Display*/
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