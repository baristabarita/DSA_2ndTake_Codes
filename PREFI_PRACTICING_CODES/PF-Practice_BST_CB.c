// Pre-Final Practice : BST - [Cursor-based Implementation]

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef int node;
typedef enum  {FALSE, TRUE} boolean;

// VIRTUAL HEAL DEFINITIONS
typedef struct node {
	int data;
	int LC;
	int RC;
}Node;

typedef struct heap {
	Node Nodes[SIZE];
	int avail;
}*Vheap;

// LIST AND BST USING VHEAP
typedef struct List {
	int elemPtr;
	Vheap VH;
}BTree;

// VIRTUAL HEAP MANAGEMENT OPERATIONS
void initVH(Vheap *VH);
int allocSpace(Vheap *VH);
void deallocSpace (Vheap *VH, int index);

// BST OPERATIONS
void INITIALIZE(BTree *S, Vheap *VH);
boolean MEMBER(BTree S, node n);
void INSERT(BTree *S, node n);
void DELETE(BTree *S, node n);
node MIN(BTree S);
node MAX(BTree S);

//DISPLAY
void PREORDER(BTree S);
void INORDER(BTree S);
void POSTORDER(BTree S);
void displayList(BTree S);

void main () {
	Vheap VH;
	initVH(&VH);
	
	BTree S;
	INITIALIZE(&S, &VH);
	
	//testing successful initialization
	printf("Initiliazed VH & List \n\n");
	displayList(S);
	
	printf("\n----INSERTING ELEMENTS---- \n");
	
	printf("Inserting Set S = {10, 5, 14, 12, 7, 18, 15} \n\n");
	INSERT(&S, 10);
	INSERT(&S, 5);
	INSERT(&S, 7);
	INSERT(&S, 14);
	INSERT(&S, 12);
	INSERT(&S, 18);
	INSERT(&S, 15);
	
	printf("\n----- DISPLAY TREE (Ordering Traversal) ------- \n\n");
	//printf("INORDER \n\n");
	//INORDER(S); // 5 7 10 12 14 15 18
	//printf("\n\nPREORDER \n\n");
	//PREORDER(S); // 10 5 7 14 12 18 15
	printf("\n\nPOSTORDER \n\n");
	POSTORDER(S); // 7 5 12 15 18 14 10
	
	
	printf("\n\n----- DELETING ELEMENTS ------- \n\n");
	
	printf("Delete Element: 7 14 10 \n\n");
	DELETE(&S, 7);
	DELETE(&S, 14);
	DELETE(&S, 10);
	INORDER(S);
	
	printf("\n\n---- CHECKING MEMBERSHIP---- \n");
	
	int elem = 10;
	printf("\nIs ' %d ' a member of List? ", elem);
	(MEMBER(S, elem) == 1)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 1;
	printf("\nIs ' %d ' a member of List? ", elem);
	(MEMBER(S, elem) == 1)? printf("Yes, it's a member.") : printf("No, it's not a member.");
}

void initVH(Vheap *VH) {
	int index;
	
	(*VH) = (Vheap) malloc (sizeof(struct heap)); //VH is a POINTER to a structure, so MALLOC IT LORRRRRRDDD.
	
	if ((*VH) != NULL) {
		(*VH)->avail = SIZE-1;
	
		for (index = 0; index < SIZE; index++) {
			(*VH)->Nodes[index].LC = index - 1;
			(*VH)->Nodes[index].RC = index - 2;
		}
	}
	
}
int allocSpace(Vheap *VH) {
	int temp;
	
	if ((*VH)->avail != -1) {
		temp = (*VH)->avail;
		(*VH)->avail = (*VH)->Nodes[temp].RC; //RC will point to next available node
	}
	
	return temp;
}
void deallocSpace (Vheap *VH, int index) {
	(*VH)->Nodes[index].RC = (*VH)->avail;
	(*VH)->avail = index;
}



void INITIALIZE(BTree *S, Vheap *VH) {
	S->elemPtr = -1;
	S->VH = *VH;
}
boolean MEMBER(BTree S, node n) {
	int trav;
	
	for (trav = S.elemPtr; trav != -1 && S.VH->Nodes[trav].data != n;) {
		trav = ( n < S.VH->Nodes[trav].data) ? S.VH->Nodes[trav].LC : S.VH->Nodes[trav].RC;
	}
	
	return (trav != -1) ? TRUE: FALSE;
}

void INSERT(BTree *S, node n) {
	int temp = allocSpace(&S->VH);
	int *trav;
	
	if (S->elemPtr != -1) { //check if list is initially empty
		for (trav = &S->elemPtr; (*trav) != -1;) { // look for leaf node
			trav = (n < S->VH->Nodes[(*trav)].data) ? &(S->VH->Nodes[(*trav)].LC): &(S->VH->Nodes[(*trav)].RC);
		}
		
		if ((*trav) == -1 && temp != -1) {
			S->VH->Nodes[temp].data = n;
			S->VH->Nodes[temp].LC = S->VH->Nodes[temp].RC = -1;
			*trav = temp;
		}
	}else {
		S->VH->Nodes[temp].data = n;
		S->VH->Nodes[temp].LC = S->VH->Nodes[temp].RC = -1;
		S->elemPtr = temp;
	}

}
void DELETE(BTree *S, node n) {
	int *trav, *trav2;
	node temp;
	
	if (S->elemPtr != -1) {
		for (trav = &S->elemPtr; (*trav) != -1 && S->VH->Nodes[(*trav)].data != n;) {
			trav = (n < S->VH->Nodes[(*trav)].data) ? &S->VH->Nodes[(*trav)].LC : &S->VH->Nodes[(*trav)].RC;
		}
		
		if (S->VH->Nodes[(*trav)].LC != -1 && S->VH->Nodes[(*trav)].RC != -1) { //two children
			for (trav2 = &S->VH->Nodes[(*trav)].RC; S->VH->Nodes[(*trav2)].LC != -1; trav2 = &S->VH->Nodes[(*trav)].LC) {}
			temp = *trav2;
			*trav2 = S->VH->Nodes[temp].RC;
			S->VH->Nodes[*trav].data = S->VH->Nodes[temp].data;
			deallocSpace(&S->VH, temp);
			
		} else {
			temp = *trav;
			*trav = (S->VH->Nodes[*trav].LC == -1) ? S->VH->Nodes[*trav].RC : S->VH->Nodes[*trav].LC;
			deallocSpace(&S->VH, temp);
		}
	} else {
		S->elemPtr = -1;
	}
}
node MIN(BTree S) {
	int trav;
	
	for (trav = S.elemPtr; trav != -1 && S.VH->Nodes[trav].LC != -1; trav = S.VH->Nodes[trav].LC) {}
	
	return S.VH->Nodes[trav].data;
}
node MAX(BTree S) {
	int trav;
	
	for (trav = S.elemPtr; trav != -1 && S.VH->Nodes[trav].RC != -1; trav = S.VH->Nodes[trav].RC) {}
	
	return S.VH->Nodes[trav].data;	
}


void PREORDER(BTree S) {
	
	int og = S.elemPtr; //keep original root value
	if (S.elemPtr != -1) {
		printf("%d ", S.VH->Nodes[S.elemPtr].data);
		S.elemPtr = S.VH->Nodes[S.elemPtr].LC;
		PREORDER(S);
		
		S.elemPtr = og;
		S.elemPtr = S.VH->Nodes[S.elemPtr].RC;
		PREORDER(S);
	}
}
void INORDER(BTree S) {
	
	int og = S.elemPtr;
	if (S.elemPtr != -1) {
		
		S.elemPtr = S.VH->Nodes[S.elemPtr].LC;
		INORDER(S);
		
		S.elemPtr = og;
		printf("%d ", S.VH->Nodes[S.elemPtr].data);
		
		S.elemPtr = S.VH->Nodes[S.elemPtr].RC;
		INORDER(S);
	}
}
void POSTORDER(BTree S) { // BROKEN
	
	int og = S.elemPtr; //keep original root value
	if (S.elemPtr != -1) {
		
		S.elemPtr = S.VH->Nodes[S.elemPtr].LC;
		POSTORDER(S);
		
		S.elemPtr = og;
		S.elemPtr = S.VH->Nodes[S.elemPtr].RC;
		POSTORDER(S);
		
		printf("%d ", S.VH->Nodes[S.elemPtr].data);
	}
	
}

void displayList(BTree S){
	
	printf("\nAvail: %d", S.VH->avail);
	printf("\nList: %d \n\n", S.elemPtr);

}


