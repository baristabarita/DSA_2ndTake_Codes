// Pre-Final Practice : ADT Trees - [Parent Pointer Problem]

#include <stdio.h>
#include <stdlib.h>

#define TSIZE 10

typedef int Node;
typedef struct {
	Node parent;
	char label;
}TNode;

typedef TNode PTree[TSIZE];

void INITIALIZE(PTree T);
void POPULATE(Node p, Node n, char c, PTree T);
char getRightSiblingLabel(PTree T, Node n);
void DISPLAY(PTree T);

void main () {
	PTree S;
	
	
	printf("----- INITIALIZE TREE ------- \n\n");
	INITIALIZE(S);
	DISPLAY(S);
	
	printf("----- POPULATE TREE ------- \n\n");
	POPULATE(5, 0, 'a',  S);
	POPULATE(6, 1, 'b', S);
	POPULATE(5, 2, 'c', S);
	POPULATE(6, 3, 'd', S);
	POPULATE(1, 4, 'e', S);
	POPULATE(-1, 5, 'f', S);
	POPULATE(5, 6, 'g', S);
	POPULATE(1, 7, 'h', S);
	POPULATE(2, 8, 'i', S);
	POPULATE(1, 9, 'j', S);
	DISPLAY(S);
	
	printf("----- LOOKING FOR RIGHT SIBLING ------- \n\n");
	printf("Right Sibling of Node 0: %c \n", getRightSiblingLabel(S, 0));
	printf("Right Sibling of Node 1: %c \n", getRightSiblingLabel(S, 1));
	printf("Right Sibling of Node 4: %c \n", getRightSiblingLabel(S, 4));
	printf("Right Sibling of Node 7: %c \n", getRightSiblingLabel(S, 7));
	printf("Right Sibling of Node 9: %c \n", getRightSiblingLabel(S, 9));
	printf("Right Sibling of Node 8: %c \n", getRightSiblingLabel(S, 8));
}

void INITIALIZE(PTree T) {
	int index;
	
	for (index = 0; index < TSIZE; T[index].parent = -2, index++) {}
}

void POPULATE(Node p, Node n, char c, PTree T) {
	
	if (n < TSIZE) {
		T[n].parent = p;
		T[n].label = c;
	}
}

char getRightSiblingLabel(PTree T, Node n) {
	int index;
	char r_s = '*';
	
	for (index = 0; index < TSIZE && r_s == '*'; index++) {
		if (T[index].parent == T[n].parent && index > n) {
			r_s = T[index].label;
		}
	}
	
	return r_s;
}

void DISPLAY(PTree T) {
	int i;
	
	for (i = 0; i < TSIZE; i++) {
		printf("[%d] %d | %c \n", i, T[i].parent, T[i].label);
	}
	
	printf("\n");
}
