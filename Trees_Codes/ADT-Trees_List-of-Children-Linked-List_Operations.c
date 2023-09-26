// ADT Trees Operations (List of Children)_Linked List

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node {
	int data;
	struct node* link;
}*LIST;

typedef struct {
	LIST Header[SIZE];
	int root;
}Tree;


int PARENT (int n, Tree T);
int LEFTMOST_CHILD (int n, Tree T);
int RIGHT_SIBLING(int n, Tree T);
int ROOT (Tree T);
int LABEL (int n, Tree T);
void CREATE ();
void INITIALIZE (int root, Tree *T);
void POPULATE_TREE (int p, int n, Tree *T);
void DISPLAY(Tree T);

void main () {
	Tree T, T2;
	
	
	printf("----- INITIALIZE TREE ------- \n\n");
	INITIALIZE (5, &T);
	DISPLAY(T);
	
	printf("\n----- POPULATE TREE ------- \n\n");
	POPULATE_TREE(5, 0, &T);
	POPULATE_TREE(5, 6, &T);
	POPULATE_TREE(5, 2, &T);
	
	POPULATE_TREE(1, 4, &T);
	POPULATE_TREE(1, 7, &T);
	
	POPULATE_TREE(2, 8, &T);
	POPULATE_TREE(6, 3, &T);
	POPULATE_TREE(6, 1, &T);
	DISPLAY(T);
	
	printf("----- LOOKING FOR PARENT ------- \n\n");
	printf("Parent of Node 0: %d \n", PARENT(0, T));
	printf("Parent of Node 2: %d \n", PARENT(2, T));
	printf("Parent of Node 1: %d \n", PARENT(1, T));
	printf("Parent of Node 7: %d \n", PARENT(7, T));
	printf("Parent of Node 5: %d \n", PARENT(5, T));
	printf("Parent of Node 9: %d \n\n", PARENT(9, T));
	
	printf("----- LOOKING FOR LEFTMOST CHILD ------- \n\n");
	printf("Leftmost Child of Node 6: %d \n", LEFTMOST_CHILD(6, T));
	printf("Leftmost Child of Node 2: %d \n", LEFTMOST_CHILD(2, T));
	printf("Leftmost Child of Node 1: %d \n", LEFTMOST_CHILD(1, T));
	printf("Leftmost Child of Node 0: %d \n\n", LEFTMOST_CHILD(0, T));
	
	printf("----- LOOKING FOR RIGHTMOST SIBLING ------- \n\n");
	printf("Right Sibling of Node 0: %d \n", RIGHT_SIBLING(0, T));
	printf("Right Sibling of Node 6: %d \n", RIGHT_SIBLING(6, T));
	printf("Right Sibling of Node 4: %d \n\n", RIGHT_SIBLING(4, T));
	
	printf("----- LOOKING FOR ROOT OF TREE ------- \n\n");
	printf("Root of Tree: %d \n", ROOT(T));
	
	
}

void INITIALIZE (int root, Tree *T) { //initialize each pointer to be NULL
	int i;
	T->root = root;
	
	for (i = 0; i < SIZE; i++){
		T->Header[i] = NULL;
	}
}

void POPULATE_TREE (int p, int n, Tree *T) {
	LIST temp = (LIST) malloc(sizeof(struct node));
	LIST *trav;
	
	if (p < SIZE) {
		
		for (trav = &T->Header[p]; (*trav) != NULL; trav = &(*trav)->link) {}
		
		if (temp != NULL) {
			temp->data = n;
			temp->link = *trav;
			*trav = temp;
		}
		
	}
}

int PARENT (int n, Tree T) { //go thru each index and find parent
	int i, p = -1;
	LIST trav;
	
	for (i = 0; i < SIZE; i++) {
		for (trav = T.Header[i]; trav != NULL; trav = trav->link) {
			if (trav->data == n) {
				p = i;
			}
		}
	}
	
	return p;
}

int LEFTMOST_CHILD (int p, Tree T) {
	int L;
	
	return L = (p < SIZE && T.Header[p] != NULL) ?  T.Header[p]->data : -1;

}

int RIGHT_SIBLING(int n, Tree T) { //look for immediate right sibling  BROKENNNN
	
	int i, p, R = -1, ctr = 0;
	LIST trav, temp;

	p = PARENT(n, T);

	for (trav = T.Header[p]; trav != NULL; trav = trav->link) {
		if (trav->data == n) {
			temp = trav->link;
			R = temp->data;
		}
	}
	return R;
}

int ROOT (Tree T) {
	return T.root;
}

void DISPLAY(Tree T) {
	int i;
	LIST trav;
	
	printf("Root: [%d] \n\n", T.root);
	
	for (i = 0; i < SIZE; i++) {
		printf("[%d] -> ", i);
		for (trav = T.Header[i]; trav != NULL; trav = (trav->link)){
			printf(" |%d| -> ", trav->data);
		}
		printf("\n");
	}
}



