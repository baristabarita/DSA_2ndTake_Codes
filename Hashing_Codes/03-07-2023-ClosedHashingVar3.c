// dictionary - closed hashing (variation 3) operations

#include <stdio.h>

#define MAX 20
#define EMPTY ' '
#define DELETED '!' 

typedef struct node {
	char data;
	int link;
}nodeType;

typedef struct {
	nodeType Nodes[MAX];
	int avail;
}Dictionary;

//function prototypes
void initialize(Dictionary *D);
int hash(char x);
int isMember(Dictionary D, char x);
void insert(Dictionary *D, char x);
void deleteElem (Dictionary *D, char x);

void main () {
	
	int retval;
	Dictionary D;
	initialize (&D);
	
	
	insert(&D, 'a'); //97
	insert(&D, 'b'); //98
	insert(&D, 'c'); //99
	
	insert(&D, 'k'); //107
	insert(&D, 'l'); //108
	insert(&D, 'm'); //109
	
	insert(&D, 'u'); //117
	insert(&D, 'v'); //118
	insert(&D, 'w'); //119
	
	
	retval = isMember(D, 'a');
	printf("%d", retval);
	retval = isMember(D, 'l');
	printf("%d", retval);
	retval = isMember(D, 'w');
	printf("%d", retval);
	
	retval = isMember(D, 'd');
	printf("\n%d", retval);
	retval = isMember(D, 'h');
	printf("%d", retval);
	retval = isMember(D, 'e');
	printf("%d", retval);
	
	
	deleteElem(&D, 'a');
	deleteElem(&D, 'l');
	deleteElem(&D, 'w');
	
}

void initialize(Dictionary *D) {
	D->avail = MAX / 2;
	int index;
	
	//initialize prime data area to EMPTY
	for (index = 0; index < D->avail; index++) {
		D->Nodes[index].data = EMPTY;
	}
	
	//link all nodes in synonym area
	for (index = D->avail; index < MAX; index++) {
		D->Nodes[index].link = index + 1;
	}
	
	D->Nodes[MAX-1].link = -1;
}

int hash(char x) {
	return (x % 10);
}

int isMember (Dictionary D, char x) {
	int hashval = hash(x);
	int temp = 0, retval = -1;
	
	if (D.Nodes[hashval].data != EMPTY) {
		if (D.Nodes[hashval].data != x) {
			for (temp = D.Nodes[hashval].link; temp != -1 && D.Nodes[temp].data != x ; temp = D.Nodes[temp].link) {}
		}
		if (temp != -1) {
				retval = 0;
			}
	}
	
	return retval;
}

void insert(Dictionary *D, char x) {
	int hashval = hash(x);
	int temp;
	
	if (D->Nodes[hashval].data == EMPTY) {
		D->Nodes[hashval].data = x;
		D->Nodes[hashval].link = -1;
	} else {
		//insertFirst()
		 	temp = D->Nodes[D->avail].link;
		 	
			D->Nodes[D->avail].data = x;
			
			D->Nodes[D->avail].link = D->Nodes[hashval].link;
			D->Nodes[hashval].link = D->avail;
			D->avail = temp;
		}
}

void deleteElem (Dictionary *D, char x) {
	int hashval = hash(x);
	int temp;
	
	if (D->Nodes[hashval].data != EMPTY) {
		if (D->Nodes[hashval].data == x) {
			D->Nodes[hashval].data = DELETED;
		} else {
			for (temp = D->Nodes[hashval].link; temp != -1 && 
                    D->Nodes[temp].data != x ; 
                    temp = D->Nodes[temp].link) {}
			
			if (temp != -1) {
				D->Nodes[temp].data = DELETED; 
				D->Nodes[temp].link = D->avail;
				D->avail = temp;
			}	
		}
			
	}
}
