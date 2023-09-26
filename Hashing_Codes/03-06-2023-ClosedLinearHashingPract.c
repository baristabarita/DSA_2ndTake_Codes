//Linear Hashing Practice

#include <stdio.h>

#define MAX 10
#define EMPTY ' '
#define DELETED '!'

typedef char Dictionary[MAX];

int hash(char elem){
	return (elem % 10);
}

void initDict(Dictionary D){
	int index;
	for(index = 0; index < MAX; index++){
		D[index] = EMPTY;
	}
}

void displayD(Dictionary D) {
    int ndx;
    
    printf("\n\tWHOLE DICTIONARY\t\n");
    printf("\n INDEX     ELEMENT  HASH VALUE ");
    for (ndx = 0; ndx < MAX; ndx++) {
        printf("\n%5d %9c ", ndx, D[ndx]);
		if(D[ndx] == EMPTY || D[ndx]== DELETED){
			printf("%9d", 0);
		}else{
			printf("%9d", hash(D[ndx]));
		}
	}
}

int isMember(Dictionary D, char x){
	int hashval = hash(x);
	int temp, retval;
	
	if (D[hashval] != x) {
		for (temp = hashval + 1; temp != hashval && D[temp] != x; temp = (temp + 1) % MAX) {} //temp = ((temp + 1) % MAX
	}
	
	return retval = (temp != hashval)? 0 : 1;
	
}
void insertDict(Dictionary D, char elem){
	int trav, hashVal;
	hashVal = hash(elem);
	if(isMember(D,elem)!=0){
		for(trav=hashVal; D[hashVal]!=EMPTY && 
		D[hashVal]!=DELETED; trav++){}
		D[hashVal]=elem;
	}
}
void main(){
	Dictionary D;
	initDict(D);
	displayD(D);
	insertDict(D,'a');
	printf("\na part of dict?: %d", isMember(D, 'a'));
	displayD(D);
}