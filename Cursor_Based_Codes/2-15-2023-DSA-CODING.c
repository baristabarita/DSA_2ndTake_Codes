//A. Include Files
#include<stdio.h>
#define MAX 10

//B. Data Structure Definitions
typedef struct{
    char data;
    int link;
}nodeType;

typedef struct{
    nodeType head[MAX];
    int avail;
}VirtualHeap;

typedef int CBList;

//C. Function Prototypes
    // 3 VirtualHeap Management Routines
void initVirtualHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int index);

//ADT List Functions
void initList(CBList *L);
void displayList(VirtualHeap VH, CBList L);
void insertLast(VirtualHeap *VH, CBList *L, char elem);
void insertFirst(VirtualHeap *VH, CBList *L, char elem);
void deleteElem(VirtualHeap *VH, CBList *L, char elem);


//D. The Main Function
void main(){
	/*
    Task 1: initialize the VirtualHeap and the List.
    Populate the List w/ the elements "H", "E", "L", "L", "O"
    and display the List
    */
	VirtualHeap VH;
    CBList L1;
    initVirtualHeap(&VH);
	initList(&L1);

    printf("Displaying Task 1:\n");


	insertLast(&VH, &L1, 'H');
	insertLast(&VH, &L1, 'E');
	insertLast(&VH, &L1, 'L');
	insertLast(&VH, &L1, 'L');
	insertLast(&VH, &L1, 'O');
	displayList(VH, L1);
	/*
    Task 2: Populate a 2nd List with elements "U", "S", "C" and display the List 
    */
    printf("\n\nDisplaying Task 2:\n");
    CBList L2;
    initList(&L2);
    insertFirst(&VH, &L2, 'U');
    insertFirst(&VH, &L2, 'S');
    insertFirst(&VH, &L2, 'C');
    displayList(VH, L2);
	
	
    /*
    Task 3: DeleteElem and stuff
    */
    
    printf("\n\nDisplaying Task 3:\n");
    deleteElem(&VH, &L1, 'E');
    displayList(VH, L1);
    printf("\n");
    deleteElem(&VH, &L2, 'C');
	displayList(VH, L2);
}

//E. Definition of Other Functions

void initVirtualHeap(VirtualHeap *VH){
    int index;
    VH->avail = MAX-1;
    for(index = 0; index < MAX; index++){
        VH->head[index].link = index - 1;
    }
}
int allocSpace(VirtualHeap *VH){
    int temp = -1;
        temp = VH->avail;
        VH->avail = VH->head[temp].link;
    return temp;
}
void deallocSpace(VirtualHeap *VH, int index){
    VH->head[index].link = VH->avail;
    VH->avail = index;
}

    //ADT List Functions
void initList(CBList *L){
    (*L) = -1;
}

void insertLast(VirtualHeap *VH, CBList *L, char elem){
        int *trav;
        int temp;
        for(trav = L; (*trav)!=-1; trav = &VH->head[*trav].link){}
        temp = allocSpace(VH);
        if(temp != -1){
            VH->head[temp].data = elem;
            VH->head[temp].link = -1;
            *trav = temp;
        }     
    }
void insertFirst(VirtualHeap *VH, CBList *L, char elem){
    int temp = allocSpace(VH);
        if(temp != -1){
            VH->head[temp].data = elem;
            VH->head[temp].link = *L;
            *L = temp;
        }    
}
void deleteElem(VirtualHeap *VH, CBList *L, char elem){
    CBList *trav, temp;

    for(trav = L; (*trav) != -1;){
        if(VH->head[*trav].data == elem){
            temp = *trav;
            *trav = VH->head[temp].link;
            deallocSpace(VH, temp);
        } else{
            trav = &VH->head[*trav].link;
        }
    }
}
void displayList(VirtualHeap VH, CBList L){
	CBList trav;
	for(trav = L; trav != -1; trav = VH.head[trav].link){
		printf("%c ", VH.head[trav].data);
	}
}