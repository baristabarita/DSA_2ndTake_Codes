/*
ADT LIST Cursor Based Implementation
*/

//A. Include files and macro definition
#include<stdio.h>

#define MAX 10
//B. Data Structure definition
typedef struct{
    char data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int Avail;
}VirtualHeap;

typedef int CBList;
//C. Function prototypes
    //Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int index);
    //ADT List Functions
void initCBList(CBList *L);
void insertFirst(VirtualHeap *VH, CBList *L, char elem);
void insertLast(VirtualHeap *VH, CBList *L, char elem);
void insertSorted(VirtualHeap *VH, CBList *L, char elem);
void deleteFirst(VirtualHeap *VH, CBList *L);
void deleteLast(VirtualHeap *VH, CBList *L);
void deleteAllOccur(VirtualHeap *VH, CBList *L, char elem);
int isMember(VirtualHeap VH, CBList L, char elem);
void displayList(VirtualHeap VH, CBList L);

//D. Function main
void main(){
    VirtualHeap VH;
    CBList L;

    printf("\n****** List Initialization ******\n");
    initVirtualHeap(&VH);
    initCBList(&L);
    displayList(VH, L);
    printf("\n****** Inserting Elements ******\n");
    insertFirst(&VH, &L, 'b');
    insertFirst(&VH, &L, 'a');
    insertLast(&VH, &L, 'z');
    insertSorted(&VH, &L, 'l');
    insertLast(&VH, &L, 'm');
    insertSorted(&VH, &L, 'l');
    displayList(VH, L);
    printf("\n****** Deleting elements ******\n");
    deleteFirst(&VH, &L);
    deleteLast(&VH, &L);
    deleteAllOccur(&VH, &L, 'l');
    displayList(VH, L);
    printf("\n****** Check Member ******\n");
    printf("is 'a' a member?: %d\n", isMember(VH, L, 'a'));
    printf("is 'b' a member?: %d\n", isMember(VH, L, 'b'));
    printf("is 'o' a member?: %d\n", isMember(VH, L, 'o'));
    
}
//E. Function definitions of the prototypes
    //Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH){
    int index;
    
    VH->Avail = MAX -1;
    for(index = 0; index < MAX; index++){
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
    //ADT List Functions
void initCBList(CBList *L){
    (*L) = -1;
}
void insertFirst(VirtualHeap *VH, CBList *L, char elem){
    int temp = allocSpace(VH);
    if(temp != -1){
        VH->Nodes[temp].data = elem;
        VH->Nodes[temp].link = *L;
        *L = temp;
    }
}
void insertLast(VirtualHeap *VH, CBList *L, char elem){
    int temp = allocSpace(VH);
    int *trav;
    for(trav = L; (*trav) != -1; trav = &VH->Nodes[*trav].link){}
    if(temp != -1){
        VH->Nodes[temp].data = elem;
        VH->Nodes[temp].link = *trav;
        *trav = temp;
    }
}
void insertSorted(VirtualHeap *VH, CBList *L, char elem){
    int temp = allocSpace(VH);
    int *trav;
    for(trav = L; (*trav)!=-1 && VH->Nodes[*trav].data < elem; trav = &VH->Nodes[*trav].link){}
    if(temp != -1){
        VH->Nodes[temp].data = elem;
        VH->Nodes[temp].link = *trav;
        *trav = temp;
    }
}
void deleteFirst(VirtualHeap *VH, CBList *L){
    CBList temp;
    if((*L) != -1){
        temp = *L;
        *L = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
    }
}
void deleteLast(VirtualHeap *VH, CBList *L){
    CBList *trav, temp;
    for(trav = L; VH->Nodes[*trav].link != -1; trav = &VH->Nodes[*trav].link){}
    if((*trav) != -1){
        temp = *trav;
        *trav = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
    }
}
void deleteAllOccur(VirtualHeap *VH, CBList *L, char elem){
    CBList *trav, temp;
    for(trav = L; (*trav) != -1;){
        if(VH->Nodes[*trav].data == elem){
            temp = *trav;
            *trav = VH->Nodes[temp].link;
            deallocSpace(VH, temp);
        }else{
            trav = &VH->Nodes[*trav].link;
        }
    }
}
int isMember(VirtualHeap VH, CBList L, char elem){
    CBList trav;
    for(trav = L; trav != -1 && VH.Nodes[trav].data != elem; trav = VH.Nodes[trav].link){}
    return(trav!=-1)? 1: 0;
}
void displayList(VirtualHeap VH, CBList L){
    CBList trav;
    for(trav = L; trav != -1; trav = VH.Nodes[trav].link){
        printf("%c -> ", VH.Nodes[trav].data);
    }
    printf("NULL");
}