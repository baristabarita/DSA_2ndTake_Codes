// Binary Search Tree - Operations (Recursive)

#include <stdio.h>
#include <stdlib.h>

typedef enum  {FALSE, TRUE} boolean;


typedef struct cell {
	int elem;
	struct cell* LC;
	struct cell* RC;
}*BST;

boolean MEMBER (BST S, int n);
BST INSERT (BST *S, int n);
BST DELETE (BST *S, int n);
BST MIN(BST S);
BST MAX(BST S);
struct cell* newNode(int n);
void INITIALIZE (BST *S);

// Dispaly - Traversal Functions
void INORDER (BST S);
void PREORDER (BST S);
void POSTORDER (BST S);

void main () {
	BST S;
	
	printf("----- INITIALIZE TREE ------- \n\n");
	INITIALIZE (&S);
	
	printf("\n----- INSERT ELEMENTS ------- \n\n");
	
	printf("Inserting Set S = {10, 5, 14, 12, 7, 18, 15} \n\n");
	S = INSERT(&S, 10);
	INSERT(&S, 5);
	INSERT(&S, 7);
	INSERT(&S, 14);
	INSERT(&S, 12);
	INSERT(&S, 18);
	INSERT(&S, 15);
	
	printf("\n----- DISPLAY TREE (Ordering Traversal) ------- \n\n");
	printf("INORDER \n\n");
	INORDER(S); // 7 5 10 12 14 15 18
	printf("\n\nPREORDER \n\n");
	PREORDER(S); // 10 5 7 14 12 18 15
	printf("\n\nPOSTORDER \n\n");
	POSTORDER(S); // 7 5 12 15 18 14 10
	
	printf("\n\n----- DELETING ELEMENTS ------- \n\n");
	
	printf("Delete Element: 7 \n\n");
	S = DELETE(&S, 7);
	INORDER(S);
	
	printf("\n\nDelete Element: 14");
	S = DELETE(&S, 14);
	printf("\nDelete Element: 10 \n\n");
	S = DELETE(&S, 10);
	
	INORDER(S);
}

void INITIALIZE (BST *S) {
	*S = NULL;
}

boolean MEMBER (BST S, int n) {
	
	if (S != NULL && S->elem != n) {
		(n < S->elem) ? MEMBER(S->LC , n) : MEMBER(S->RC , n);
	}
	
	return (S != NULL) ? TRUE: FALSE;
}

struct cell* newNode(int n) {
	struct cell* temp = (struct cell*) malloc (sizeof(struct cell));
	
	if (temp != NULL) {
		temp->elem = n;
		temp->LC = temp->RC = NULL;
	}
	
	return temp;
}

BST INSERT (BST *S, int n) {
	
	if (*S == NULL) { //empty tree
		*S = newNode (n);
	} else if (n < (*S)->elem) {
		(*S)->LC = INSERT(&(*S)->LC, n);
	} else {
		(*S)->RC = INSERT(&(*S)->RC, n);
	}
	
	return *S;
}

BST DELETE (BST *S, int n) {
	
	if (*S == NULL) {
		(*S) = NULL;
	} 
	
	if ( n < (*S)->elem) {
		(*S)->LC = DELETE(&(*S)->LC, n);
	} else if (n > (*S)->elem) {
		(*S)->RC = DELETE(&(*S)->RC, n);
	} else { // check possible cases
	
		if ((*S)->LC != NULL && (*S)->RC != NULL) { //two children
			struct cell* temp = MIN((*S)->RC);
			(*S)->elem = temp->elem;
			(*S)->RC = DELETE(&(*S)->RC, temp->elem);
			
		} else { // one child
			struct cell* temp = ((*S)->LC == NULL) ? (*S)->RC: (*S)->LC;
			free(*S);
			return temp;
		}
		
	}
	
	return *S;
}

BST MIN(BST S) { //look for smallest value in tree (traverse left subtree)
	BST trav;
	
	for (trav = S; trav != NULL && trav->LC != NULL; trav = trav->LC) {}
	
	return trav;	
}

BST MAX(BST S) { //look for biggest value in tree (traverse right subtree)
	BST trav;
	
	for (trav = S; trav != NULL && trav->RC != NULL; trav = trav->RC) {}
	
	return trav;	
}

void INORDER (BST S) {
	if (S != NULL) {
		INORDER(S->LC);
		printf("%d ", S->elem);
		INORDER(S->RC);
	}
}

void PREORDER (BST S) {	
	if (S != NULL) {
		printf("%d ", S->elem);
		PREORDER(S->LC);
		PREORDER(S->RC);
	}
}

void POSTORDER (BST S) {	
	if (S != NULL) {
		POSTORDER(S->LC);
		POSTORDER(S->RC);
		printf("%d ", S->elem);
	}
}



