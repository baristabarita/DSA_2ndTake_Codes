/*
Dictionary Closed Hashing Grouping Synonyms Implementation
Note: Grouping SYnonyms is Variation 3
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define EMPTY -1
#define DELETED 0

//B. Data Structure definition
typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int Avail;
} Dictionary;

//C. Function prototypes
void initDict(Dictionary *D);
void displayDict(Dictionary D);
int hash(int elem);
void insertDict(Dictionary *D, int elem);
void deleteDict(Dictionary *D, int elem);
int isMemeber(Dictionary D, int elem);

//D. Function main
void main(){
    Dictionary D;
    printf("\n***** INITIALIZATION *****\n");
    initDict(&D);
    displayDict(D);
    
    printf("\n***** INSERT ELEMENTS *****\n");
    insertDict(&D, 33);
    insertDict(&D, 69);
    insertDict(&D, 73);
    insertDict(&D, 14);
    insertDict(&D, 19);
    insertDict(&D, 500);
    insertDict(&D, 284);
    insertDict(&D, 102);
    insertDict(&D, 420);
    insertDict(&D, 863);
    displayDict(D);
    

    printf("\n***** DELETE ELEMENTS *****\n");
    deleteDict(&D, 33);
    displayDict(D);

    printf("\n***** CHECK MEMBERSHIP ******\n");
    printf("is 33 a part of Dictionadry D: %d\n", isMemeber(D, 33));
    printf("is 69 a part of Dictionadry D: %d\n", isMemeber(D, 69));
    printf("is 73 a part of Dictionadry D: %d\n", isMemeber(D, 73));
    
}
//E. Function definitions of the prototypes
void initDict(Dictionary *D){
    int index;
    D->Avail = MAX / 2;
    //prime data area
    for(index = 0; index < D->Avail; index++){
        D->Nodes[index].data = EMPTY;
    }
    //synonym area;
    for(index = D->Avail; index < MAX; index++){
        D->Nodes[index].data = EMPTY;
        D->Nodes[index].link = index+1;
    }
    D->Nodes[MAX-1].link = -1;
}

void displayDict(Dictionary D){
    int index;
    //prime data area
    for(index = 0; index < D.Avail; index++){
        printf("[%d] ", index);
        if(D.Nodes[index].data == EMPTY){
            printf("EMPTY | __");
        } else if(D.Nodes[index].data == DELETED){
            printf("DELETED | %d", DELETED);
        } else{
            printf("%d | %d", D.Nodes[index].data, D.Nodes[index].link);
        }
        printf("\n");
    }
    //synonym area;
    
    for(index = D.Avail; index < MAX; index++){
        printf("[%d] %d | %d\n", index, D.Nodes[index].data, D.Nodes[index].link);
    }
    printf("\nCurrent Avail: %d", D.Avail);
}
int hash(int elem){
    return (elem % (MAX/2));
}
void insertDict(Dictionary *D, int elem){
    int hashVal = hash(elem);
    int temp;
    if(D->Nodes[hashVal].data == EMPTY || D->Nodes[hashVal].data == DELETED){
        D->Nodes[hashVal].data = elem;
        D->Nodes[hashVal].link = -1;
    } else {
        temp = D->Nodes[D->Avail].link;
        D->Nodes[D->Avail].data = elem;
        D->Nodes[D->Avail].link = D->Nodes[hashVal].link;
        D->Nodes[hashVal].link = D->Avail;
        D->Avail = temp;
    }
}
void deleteDict(Dictionary *D, int elem){
    int hashVal = hash(elem);
    int temp;
    
    if(D->Nodes[hashVal].data != EMPTY){
        if(D->Nodes[hashVal].data == elem){
            D->Nodes[hashVal].data = DELETED;
        } else {
            for(temp = D->Nodes[hashVal].link; temp != -1 && D->Nodes[temp].data != elem; temp = D->Nodes[temp].link){}
            if(temp != -1){
                D->Nodes[temp].data = DELETED;
                D->Nodes[temp].link = D->Avail;
                D->Avail = temp;
            }
        }
    }
}
int isMemeber(Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp = 0, retval = 0;
    if(D.Nodes[hashVal].data != EMPTY){
        if(D.Nodes[hashVal].data != elem){
            for(temp = D.Nodes[hashVal].link; temp != -1 && D.Nodes[temp].data != elem; temp = D.Nodes[temp].link){}
        }
        if(temp != -1){
            retval = 1;
        }
    }
    return retval;
}
