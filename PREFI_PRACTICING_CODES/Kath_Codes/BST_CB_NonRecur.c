#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
#define M 8

typedef struct{
	int elem;
	int LC;
	int RC;	
}Node;

typedef struct node{
	Node N[SIZE];
	int avail;
}VHeap;

typedef int BST;
typedef int SET[M];

void initialize(BST*,VHeap*);
void insert(BST*,VHeap*,int);
int isMember(BST,VHeap,int);
void deleteV1(BST*,VHeap*,int);
void deleteV2(BST*,VHeap*,int);
int deleteMin(BST*,VHeap*);
int deleteMax(BST*,VHeap*);

/*Display*/
void preorder(BST,VHeap);
void inorder(BST,VHeap);
void postorder(BST,VHeap);

void display(BST,VHeap);

void main(){
	BST Tree;
	VHeap VH;
	int x;
	
	printf("Task 1: Initialize\n-----------------------------\n");
	initialize(&Tree,&VH);
	display(Tree,VH);
	
	printf("\n\nTask 2: Insert\n-----------------------------");
	SET A={10,5,14,12,7,18,15,11};
	for(x=0;x<M;x++){
		insert(&Tree,&VH,A[x]);
	}
	display(Tree,VH);
	insert(&Tree,&VH,7);
	display(Tree,VH);
	printf("\n\nTask 3: isMember\n-----------------------------\n");
	printf("Is %d a Member? %d",5,isMember(Tree,VH,5));
	printf("\nIs %d a Member? %d",13,isMember(Tree,VH,13));	
	
	printf("\n\nTask 4: Delete\n-----------------------------");
	deleteV1(&Tree,&VH,15); //Deleting a leaf
	deleteV1(&Tree,&VH,12); //Deleting an inode with a left child only
	deleteV1(&Tree,&VH,5); //Deleting an inode with a right child only
	deleteV1(&Tree,&VH,10); //Deleting an inode with 2 children
	
	/*deleteV2(&Tree,&VH,15);
	deleteV2(&Tree,&VH,12);
	deleteV2(&Tree,&VH,5);
	deleteV2(&Tree,&VH,10);*/
	
	display(Tree,VH);
	
	printf("\n\nSmallest Element: %d",deleteMin(&Tree,&VH));
	printf("\nLargest Element: %d",deleteMax(&Tree,&VH));
}

void initialize(BST*T,VHeap*VH){
	int i,lim=SIZE-1;
	
	*T=-1;
	VH->avail=0;
	for(i=0;i<lim;i++){
		VH->N[i].LC=i+1;
		VH->N[i].RC=i+1;
	}
	
	VH->N[i].LC=VH->N[i].RC=-1;
}

void insert(BST*A,VHeap*VH,int elem){
	BST *trav;

	for(trav=A;*trav!=-1 && elem!=VH->N[*trav].elem;){
		trav = elem < VH->N[*trav].elem ? &VH->N[*trav].LC : &VH->N[*trav].RC;
	}
	
	if(*trav==-1){
		*trav=VH->avail;
		if(*trav!=-1){
			VH->avail = VH->N[*trav].LC!=-1 ? VH->N[*trav].LC : VH->N[*trav].RC;
			VH->N[*trav].elem=elem;
			VH->N[*trav].LC=VH->N[*trav].RC=-1;
		}
	}
}

int isMember(BST A,VHeap VH,int elem){
	BST trav;
	for(trav=A;trav!=-1 && elem!=VH.N[trav].elem;){
		trav= elem < VH.N[trav].elem ? VH.N[trav].LC : VH.N[trav].RC;
	}
	return trav!=-1 ? 1 : 0;
}

void deleteV1(BST*S,VHeap *VH,int elem){
	BST *A,*B,temp;
	
	for(A=S; *A!=-1 && VH->N[*A].elem!=elem;){
		A = elem < VH->N[*A].elem ? &VH->N[*A].LC : &VH->N[*A].RC;
	}
	
	if(*A!=-1){
		if(VH->N[*A].LC==-1 || VH->N[*A].RC==-1){
			temp=*A;
			if(VH->N[*A].LC==-1){
				*A=VH->N[temp].RC; 
			}else{
				*A=VH->N[temp].LC;
			}
		}else{ /*Can be changed to deleteMax*/
			for(B=&VH->N[*A].RC; VH->N[*B].LC!=-1;B=&VH->N[*B].LC){}
			VH->N[*A].elem=VH->N[*B].elem;
			temp=*B;
			*B=VH->N[temp].RC; 
		}	
		VH->N[temp].LC=VH->N[temp].RC=VH->avail;
		VH->avail=temp;
	}
}

void deleteV2(BST*S,VHeap *VH,int elem){
	BST *A,*B,temp;
	
	for(A=S; *A!=-1 && VH->N[*A].elem!=elem;){
		A = elem < VH->N[*A].elem ? &VH->N[*A].LC : &VH->N[*A].RC;
	}
	
	if(*A!=-1){
		if(VH->N[*A].LC==-1 || VH->N[*A].RC==-1){
			temp=*A;
			if(VH->N[*A].LC==-1){
				*A=VH->N[temp].RC; 
			}else{
				*A=VH->N[temp].LC;
			}
			VH->N[temp].LC=VH->N[temp].RC=VH->avail;
			VH->avail=temp;
		}else{ /*Can be changed to deleteMax*/
			VH->N[*A].elem=deleteMin(&VH->N[*A].RC,VH);
		}	
	}
}

int deleteMin(BST*A,VHeap*VH){
	int *trav,temp,retVal;
	if(*A!=-1){
		for(trav=A;VH->N[*trav].LC!=-1;trav=&VH->N[*trav].LC){}
		retVal=VH->N[*trav].elem;
		temp=*trav;
		*trav=VH->N[temp].RC;
		VH->N[temp].LC=VH->N[temp].RC=VH->avail;
		VH->avail=temp;
	}
	return retVal;
}

int deleteMax(BST*A,VHeap*VH){
	int *trav,temp,retVal;
	if(*A!=-1){
		for(trav=A;VH->N[*trav].RC!=-1;trav=&VH->N[*trav].RC){}
		retVal=VH->N[*trav].elem;
		temp=*trav;
		*trav=VH->N[temp].LC;
		VH->N[temp].LC=VH->N[temp].RC=VH->avail;
		VH->avail=temp;
	}
	return retVal;
}

void preorder(BST T,VHeap VH){
	if(T!=-1){
		printf("%d ",VH.N[T].elem);
		preorder(VH.N[T].LC,VH);
		preorder(VH.N[T].RC,VH);
	}
}

void inorder(BST T,VHeap VH){
	if(T!=-1){
		inorder(VH.N[T].LC,VH);
		printf("%d ",VH.N[T].elem);
		inorder(VH.N[T].RC,VH);
	}
}

void postorder(BST T,VHeap VH){
	if(T!=-1){
		postorder(VH.N[T].LC,VH);
		postorder(VH.N[T].RC,VH);
		printf("%d ",VH.N[T].elem);
	}
}

void display(BST T,VHeap VH){
	if(T!=-1){
		printf("\n\nPreorder | ");
		preorder(T,VH);
		printf("\nInorder | ");
		inorder(T,VH);
		printf("\nPostorder | ");
		postorder(T,VH);
	}else{
		printf("\nBST is Empty");
	}
}