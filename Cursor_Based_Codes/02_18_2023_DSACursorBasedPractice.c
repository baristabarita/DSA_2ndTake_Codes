#include<stdio.h>
#define MAX 5

//Data Structure Definitions
typedef struct{
    char data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int Avail;
}VirtualHeap;

typedef int CBList;

//Function Prototypes
void initVirtualHeap(VirtualHeap *VH);
int deleteNode(VirtualHeap *VH);
void insertNode(VirtualHeap *VH, int index);
void initList(CBList *L);
void insertFirst(CBList *L, char elem, VirtualHeap *VH);
void display(CBList L, VirtualHeap VH);
int searchElem(CBList L, char elem, VirtualHeap VH);

void main(){
    VirtualHeap VH;
    CBList L;
    int checkElem;
    initVirtualHeap(&VH);
    initList(&L);
    insertFirst(&L, 'A', &VH);
    insertFirst(&L, 'B', &VH);
    insertFirst(&L, 'C', &VH);
    display(L,VH);
    checkElem = searchElem(L, 'D', VH);
    printf("SearchElem: %d", checkElem);
}

//Function Definitions
void initVirtualHeap(VirtualHeap *VH){
    int x;
    VH->Avail = MAX - 1;
    for(x = MAX-1; x>= 0; x--){
        VH->Nodes[x].link = x-1;
    }
}

int deleteNode(VirtualHeap *VH){
    int temp = VH->Avail;
    VH->Avail = VH->Nodes[temp].link;
    //can also be VH->Avail = VH->Nodes[VH->Avail].link; cuz saem
    return temp;
}

void insertNode(VirtualHeap *VH, int index){
    VH->Nodes[index].link = VH->Avail;
    VH->Avail = index;
}

void initList(CBList *L){
    (*L) = -1;
}


void insertFirst(CBList *L, char elem, VirtualHeap *VH){
    CBList temp;
    temp = deleteNode(VH); //also called as allocSpace, malloc
    VH->Nodes[temp].data = elem;
    VH->Nodes[temp].link = *L;
    *L = temp;
}

void display(CBList L, VirtualHeap VH){
    CBList trav;
    for(trav = L; trav != -1; trav = VH.Nodes[trav].link){
        printf("%c ", VH.Nodes[trav].data);
    }
}

int searchElem(CBList L, char elem, VirtualHeap VH){
    CBList trav;
    for(trav=L; trav!=-1 && VH.Nodes[trav].data!= elem; trav = VH.Nodes[trav].link){}
    return(trav!=-1)? 1 : 0;
}

