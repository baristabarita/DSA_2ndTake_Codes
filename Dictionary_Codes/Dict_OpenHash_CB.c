/*
Dictionary Open-Hashing Cursor Based Implementation
*/
//A. Include files and macro definition
#include <stdio.h>

#define HEAPMAX 20
#define MAX 10
//B. Data Structure definition
typedef struct{
    int data;
    int link;
}NodeType;

typedef struct{
    NodeType Nodes[HEAPMAX];
    int Avail;
}VirtualHeap;

typedef int Dictionary[MAX];

//C. Function prototypes
    //VirtualHeap Management Routines
void initVirtualHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int index);
    //Operations
void initDict(Dictionary D);
void displayDict(VirtualHeap VH, Dictionary D);
int hash(int elem);
void insertDict(VirtualHeap *VH, Dictionary D, int elem);
void deleteDict(VirtualHeap *VH, Dictionary D, int elem);
int isMember(VirtualHeap VH, Dictionary D, int elem);

//D. Function main
void main(){
    VirtualHeap VH;
    Dictionary D;
    printf("\n***** INITIALIZATION *****\n");
    initVirtualHeap(&VH);
    initDict(D);
    displayDict(VH,D);
    
    printf("\n**** INSERT ELEMENTS ****\n");
    insertDict(&VH, D, 3);
    insertDict(&VH, D, 60);
    insertDict(&VH, D, 4);
    insertDict(&VH, D, 20);
    insertDict(&VH, D, 69);
    displayDict(VH,D);
    
    printf("\n**** DELETE ELEMENTS ****\n");
    deleteDict(&VH, D, 60);
    displayDict(VH, D);
    
    printf("\n***** CHECK MEMBERSHIP *****\n");
    printf("is 69 a part of the Dictionary?: %d\n", isMember(VH,D,69));
    printf("is 80 a part of the Dictionary?: %d\n", isMember(VH,D,80));
    
}
//E. Function definitions of the prototypes
void initVirtualHeap(VirtualHeap *VH){
    int index;
    VH->Avail = HEAPMAX -1;
    for(index = 0; index < HEAPMAX; index++){
        VH->Nodes[index].link = index-1;
    }
}
int allocSpace(VirtualHeap *VH){
    int temp = -1;
    if(VH->Avail != -1){
        temp = VH->Avail;
        VH->Avail = VH->Nodes[temp].link;
    }
    return temp;
}
void deallocSpace(VirtualHeap *VH, int index){
    VH->Nodes[index].link = VH->Avail;
    VH->Avail = index;
}
    //Operations
void initDict(Dictionary D){
    int index;
    for(index = 0; index < MAX; index++){
        D[index] = -1;
    }
}
void displayDict(VirtualHeap VH, Dictionary D){
    int index, trav;
    for(index = 0; index < MAX; index++){
        printf("[%d] ", index);
        for(trav = D[index]; trav != -1; trav = VH.Nodes[trav].link){
            printf("%3d -> ", VH.Nodes[trav].data);
        }
        printf("NULL\n");
    }
}
int hash(int elem){
    return (elem % MAX);
}
void insertDict(VirtualHeap *VH, Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp, *trav;
    for(trav = &D[hashVal]; *trav != -1 && VH->Nodes[*trav].data != elem; trav = &VH->Nodes[*trav].link){}
    if(*trav == -1){
        temp = allocSpace(VH);// can be temp = VH->Avail
        if(temp != -1){
            //can hab VH->Avai; = VH->Nodes[temp].link if allocSpace not called    
            VH->Nodes[temp].data = elem;
            VH->Nodes[temp].link = *trav;
            *trav = temp;
        }
    }
}
void deleteDict(VirtualHeap *VH, Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp, *trav;
    for(trav = &D[hashVal]; *trav != -1 && VH->Nodes[*trav].data != elem; trav = &VH->Nodes[*trav].link){}
    if(*trav != -1){
        temp = *trav;
        *trav = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
        /*
        can be:
        VH->Nodes[temp].link = VH->Avail;
        VH->Avail = temp;
        if deallocSpace is not called
        */
    }
}
int isMember(VirtualHeap VH, Dictionary D, int elem){
    int hashVal = hash(elem);
    int trav;
    for(trav = D[hashVal]; trav != -1 && VH.Nodes[trav].data != elem; trav = VH.Nodes[trav].link){}
    return (trav == -1)? 0 : 1;
}

