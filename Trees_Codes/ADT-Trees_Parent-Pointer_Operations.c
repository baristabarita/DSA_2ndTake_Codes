// ADT Trees Operations (Parent-Pointer / Array Representation)

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef int node;
typedef int Tree[SIZE];

node PARENT (node n, Tree T);
node LEFTMOST_CHILD (node n, Tree T);
node RIGHT_SIBLING(node n, Tree T);
node ROOT (Tree T);
int LABEL (node n, Tree T);
void CREATE ();
void INITIALIZE (Tree T);
void POPULATE_TREE (node p, node n, Tree T);
void DISPLAY(Tree T);


void main () {
	Tree T, T2;
	
	
	printf("----- INITIALIZE TREE ------- \n\n");
	INITIALIZE (T);
	INITIALIZE (T2);
	DISPLAY(T);
	
	printf("----- POPULATE TREE ------- \n\n");
	POPULATE_TREE(5, 0, T);
	POPULATE_TREE(6, 1, T);
	POPULATE_TREE(5, 2, T);
	POPULATE_TREE(6, 3, T);
	POPULATE_TREE(1, 4, T);
	POPULATE_TREE(-1, 5, T);
	POPULATE_TREE(5, 6, T);
	POPULATE_TREE(1, 7, T);
	POPULATE_TREE(2, 8, T);
	POPULATE_TREE(-2, 9, T);
	DISPLAY(T);
	
	printf("----- LOOKING FOR PARENT ------- \n\n");
	printf("Parent of Node 0: %d \n", PARENT(0, T));
	printf("Parent of Node 3: %d \n", PARENT(3, T));
	printf("Parent of Node 8: %d \n", PARENT(8, T));
	printf("Parent of Node 9: %d \n\n", PARENT(9, T));
	
	printf("----- LOOKING FOR LEFTMOST CHILD ------- \n\n");
	printf("Leftmost Child of Node 6: %d \n", LEFTMOST_CHILD(6, T));
	printf("Leftmost Child of Node 1: %d \n\n", LEFTMOST_CHILD(1, T));
	
	printf("----- LOOKING FOR RIGHT SIBLING ------- \n\n");
	printf("Right Sibling of Node 0: %d \n", RIGHT_SIBLING(0, T)); //should be 2
	printf("Right Sibling of Node 2: %d \n", RIGHT_SIBLING(2, T)); //should be 6
	printf("Right Sibling of Node 4: %d \n\n", RIGHT_SIBLING(4, T)); //should be 7
	/*
	printf("----- LOOKING FOR ROOT OF TREE ------- \n\n");
	printf("Root of Tree: %d \n", ROOT(T));
	printf("Root of Tree: %d \n", ROOT(T2));
	*/
}

void INITIALIZE(Tree T) {
	int i;
	/*
	for (i = 0; i < SIZE; i++) {
		T[i] = -2;
	}
	*/
	for(i = 0; i < SIZE; T[i] = -2, i++){}
}

void POPULATE_TREE (node p, node n, Tree T) {
	
	if (n < SIZE) {  // node index should be in range of SIZE
		T[n] = p;
	}
}

node PARENT (node n, Tree T) {
	return (n < SIZE && T[n] != -2) ? T[n] : -2; 
}

node LEFTMOST_CHILD (node n, Tree T) { // assume artificial ordering
	int i;
	
	for (i = 0; i < SIZE && n != T[i]; i++) {}
	
	return (i < SIZE) ? i : -2;
}

node RIGHT_SIBLING(node n, Tree T) {
	/*
	/int i;
	node r = -2;
	node p = T[n];
	int ctr = 0; // use counter to stop sequential searchS

	for (i = 0; i < SIZE; i++) { 
		if (T[i] == p && i > n && ctr == 0) { //look for other nodes with == parent
			r = i;
			ctr++;
		}
		
	}
	
	return r;
	*/
	node ctr, r_s = -2;
	for(ctr = 0; ctr < SIZE && r_s == -2; ctr++){
		if(T[ctr] == T[n] && ctr > n){
			r_s = ctr;
		}
	}
	return r_s;
}

node ROOT (Tree T) {
	int i;
	
	for (i = 0; i < SIZE && T[i] != -1; i++) {} //look for root
	
	return (i < SIZE) ? i : -2;
}
void DISPLAY(Tree T) {
	int i;
	
	for (i = 0; i < SIZE; i++) {
		printf("[%d] %d \n", i, T[i]);
	}
	
	printf("\n");
}
