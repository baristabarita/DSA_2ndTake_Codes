// A. Include Files
#include <stdio.h>
#define MAX 10

// B. Data Structure Definition
    typedef struct{
        char data;
        int link;
    }nodeType;
    
    typedef struct{
        nodeType Nodes[MAX];
        int avail;
    }VirtualHeap;

    typedef int CBList;

// C. Function Prototypes
    void initVirtualHeap(VirtualHeap *VH);
    int allocSpace(VirtualHeap *VH);
    void deallocSpace(VirtualHeap *VH, int index);

    void initList(CBList *L);
    void displayList(VirtualHeap VH, CBList L);
    void insertLast(VirtualHeap *VH, CBList *L, char elem);
    
// D. The main() Function
    void main(){
    //Task1: initialize the VirtualHeap and the List
    VirtualHeap VH;
    CBList L;

    initVirtualHeap(&VH);
    initList(&L);
    insertLast(&VH, &L, 'H');
    displayList(VH,L);
    //Populate the List w//the elements "H", "E", "L", "L", "O"
    //and display the List

    //Task 2: make a new list w/ elements "U", "S", "C"

    }
// F. Definition of other Functions
    void initVirtualHeap(VirtualHeap *VH){
        int c;
        for(c=MAX-1;c>=0;c--){
            VH->Nodes[c].link = c-1;
        }

    }
    int allocSpace(VirtualHeap *VH){
        CBList temp;
        temp = -1;
        if(VH->avail!=-1){
            temp = VH->avail;
            VH->avail = VH->Nodes[temp].link;
        }

    }
    void deallocSpace(VirtualHeap *VH, int index){
        VH->Nodes[index].link = VH->avail;
        VH->avail = index;
    }

    void initList(CBList *L){
        (*L)=-1;
    }
    void displayList(VirtualHeap VH, CBList L){
        CBList trav;
        for(trav=L; trav!=-1; trav = VH.Nodes[trav].link){
            printf(" %c",VH.Nodes[trav].data);
        }
    }
    void insertLast(VirtualHeap *VH, CBList *L, char elem){
        CBList *trav, temp;
        temp = allocSpace(VH);
        for(trav=L; *trav=-1; trav = &(VH->Nodes[(*trav)].link)){}
        *trav = temp;
        VH->Nodes[temp].data = elem;
        VH->Nodes[temp].link = -1;
    }