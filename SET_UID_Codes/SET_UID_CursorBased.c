/*
SET UID Cursor Based Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

//B. Data Structure definition
typedef struct{
    int data;
    int link;
}NodeType;
typedef struct{
    NodeType Nodes[MAX];
    int Avail;
}VirtualHeap;

typedef int CBSET;

//C. Function prototypes
    //VirtualHeap Management Routines
void initVirtualHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int index);
    //Operations
void initCBSet(CBSET *S);
void displaySet(VirtualHeap VH, CBSET S);
void insertSet(VirtualHeap *VH, CBSET *S, int elem);
void deleteSet(VirtualHeap *VH, CBSET *S, int elem);
int isMember(VirtualHeap VH, CBSET S, int elem);
    //UID Operations
CBSET UnionSet(VirtualHeap *VH, CBSET A, CBSET B);
CBSET IntersectionSet(VirtualHeap *VH, CBSET A, CBSET B);
CBSET DifferenceSet(VirtualHeap *VH, CBSET A, CBSET B);
int isSubset(VirtualHeap VH, CBSET A, CBSET B);

//D. Function main
void main(){
    VirtualHeap VH;
    CBSET A, B, C;
    printf("\n***** INITIALIZATION *****\n");
    initVirtualHeap(&VH);
    initCBSet(&A);
    displaySet(VH,A);
    initCBSet(&B);
    displaySet(VH,B);
    
    printf("\n***** INSERT ELEMENTS *****\n");
    printf("Insert SET A Elements: ");
    insertSet(&VH, &A, 3);
    insertSet(&VH, &A, 2);
    insertSet(&VH, &A, 5);
    insertSet(&VH, &A, 8);
    displaySet(VH,A);
    printf("\nInsert SET B Elements: ");
    insertSet(&VH, &B, 1);
    insertSet(&VH, &B, 2);
    insertSet(&VH, &B, 4);
    insertSet(&VH, &B, 5);
    insertSet(&VH, &B, 9);
    displaySet(VH,B);


    printf("\n***** UID OPERATIONS *****\n");
    printf("Union Set of A and B: ");
    C = UnionSet(&VH, A, B);
    displaySet(VH, C);
    printf("\nIntersection of Sets A and B: ");
    C = IntersectionSet(&VH, A, B);
    displaySet(VH, C);
    printf("\nDifference of Sets A and B: ");
    C = DifferenceSet(&VH, A, B);
    displaySet(VH, C);
    
    printf("\n***** DELETE ELEMENTS *****\n");
    printf("DELETING SET A Elements: ");
    deleteSet(&VH, &A, 5);
    displaySet(VH,A);
    
    printf("\n***** CHECK MEMBERSHIP/ISSUBSET *****\n");
    printf("is 1 a part of SET A?: %d\n", isMember(VH,A,1));
    printf("is 5 a part of SET B?: %d\n", isMember(VH,B,5));
    printf("is SET B a Subset of SET A?: %d\n", isSubset(VH,A,B));
    
    
}
//E. Function definitions of the prototypes
//VirtualHeap Management Routines
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
    //Operations
void initCBSet(CBSET *S){
    (*S) = -1;
}
void displaySet(VirtualHeap VH, CBSET S){
    int trav;
    for(trav = S; trav != -1; trav = VH.Nodes[trav].link){
        printf("%d, ", VH.Nodes[trav].data);
    }
    printf("NULL\n");
}
void insertSet(VirtualHeap *VH, CBSET *S, int elem){
    int temp, *trav;
    for(trav = S; *trav != -1 && VH->Nodes[*trav].data < elem; trav = &VH->Nodes[*trav].link){}
    if(*trav != -1 && VH->Nodes[*trav].data == elem){
        //do nothing        
    } else {
        temp = allocSpace(VH); //can be temp = VH->Avail;
        if(temp != -1){
            //can have VH-Avail = VH->Node[temp].link; if allocSpace not called
            VH->Nodes[temp].data = elem;
            VH->Nodes[temp].link = *trav;
            *trav = temp;
        }
    }
}
void deleteSet(VirtualHeap *VH, CBSET *S, int elem){
    int temp, *trav;
    for(trav = S; *trav != -1 && VH->Nodes[*trav].data != elem; trav = &VH->Nodes[*trav].link){}
    if(*trav != -1){
        temp = *trav;
        *trav = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
    }
}
int isMember(VirtualHeap VH, CBSET S, int elem){
    int trav;
    for(trav = S; trav != -1 && VH.Nodes[trav].data != elem; trav = VH.Nodes[trav].link){}
    return(trav == -1)? 0 : 1;
}
    //UID Operations
CBSET UnionSet(VirtualHeap *VH, CBSET A, CBSET B){
    CBSET C, atrav, btrav, *ctrav, temp;
    initCBSet(&C);
    for(atrav = A, btrav = B; atrav != -1 && btrav != -1;){
        temp = allocSpace(VH); //can be temp = VH->Avail
        if(temp != -1){
            //can have VH->Avail = VH->Nodes[temp].link if allocpace not called
            if(VH->Nodes[atrav].data <= VH->Nodes[btrav].data){
                if(VH->Nodes[atrav].data == VH->Nodes[btrav].data){
                    btrav = VH->Nodes[btrav].link;
                }
                VH->Nodes[temp].data = VH->Nodes[atrav].data;
                atrav = VH->Nodes[atrav].link;
            }else{
                VH->Nodes[temp].data = VH->Nodes[btrav].data;
                btrav = VH->Nodes[btrav].link;
            }
            VH->Nodes[temp].link = -1;
            (C == -1) ? (C = temp) : (*ctrav = temp);
            ctrav = &(VH->Nodes[temp].link);
        }
    }
    atrav = (atrav == -1)? btrav : atrav;
    for(;atrav != -1; atrav = VH->Nodes[atrav].link){
        temp = allocSpace(VH); //can be temp = VH->Avail;
        if(temp != -1){
            //can have VH->Avail = VH->Nodes[temp].link if allocspace not called
            VH->Nodes[temp].data = VH->Nodes[atrav].data;
            VH->Nodes[temp].link = -1;
            (C == -1)? (C = temp) : (*ctrav = temp);
            ctrav = &(VH->Nodes[temp].link);
        }

    }
    return C; 
}
CBSET IntersectionSet(VirtualHeap *VH, CBSET A, CBSET B){
    CBSET C, atrav, btrav, *ctrav, temp;
    initCBSet(&C);
    for(atrav = A, btrav = B; atrav != -1 && btrav != -1;){
        if(VH->Nodes[atrav].data <= VH->Nodes[btrav].data){
            if(VH->Nodes[atrav].data == VH->Nodes[btrav].data){
                    temp = allocSpace(VH); //can be temp = VH->Avail;
                    if(temp != -1){
                    //can have VH-Avail = VH->Nodes[temp].link if allocSpace not called
                    VH->Nodes[temp].data = VH->Nodes[atrav].data;
                    VH->Nodes[temp].link = -1;
                    (C == -1)? (C = temp) : (*ctrav = temp);
                    ctrav = &(VH->Nodes[temp].link);
                    }
                    btrav = VH->Nodes[btrav].link;
                }
                atrav = VH->Nodes[atrav].link;
            } else {
                btrav = VH->Nodes[btrav].link;
            }
        
    }
    return C;
}
CBSET DifferenceSet(VirtualHeap *VH, CBSET A, CBSET B){
    CBSET C, atrav, btrav, *ctrav, temp;
    initCBSet(&C);
    for(atrav = A, btrav = B; atrav != -1 && btrav != -1; ){
        if(VH->Nodes[atrav].data <= VH->Nodes[btrav].data){
            if(VH->Nodes[atrav].data != VH->Nodes[btrav].data){
                temp = allocSpace(VH); //can be temp = VH->Avail;
                if(temp != -1){
                    //can have VH-Avail = VH->Nodes[temp].link if allocSpace not called
                    VH->Nodes[temp].data = VH->Nodes[atrav].data;
                    VH->Nodes[temp].link = -1;
                    (C == -1)? (C = temp) : (*ctrav = temp);
                    ctrav = &(VH->Nodes[temp].link);
                }
            } else {
                btrav = VH->Nodes[btrav].link;
            }
            atrav = VH->Nodes[atrav].link;
        } else{
            btrav = VH->Nodes[btrav].link;
        }
    }
    for(;atrav != -1; atrav = VH->Nodes[atrav].link){
        temp = allocSpace(VH); //can be temp = VH->Avail
        if(temp != -1){
            //can have VH->Avail = VH->Nodes[temp].link if allocSpace not called
            VH->Nodes[temp].data = VH->Nodes[atrav].data;
            VH->Nodes[temp].link = -1;
            (C == -1)? (C = temp):(*ctrav = temp);
            ctrav = &(VH->Nodes[temp].link);
        }
    }
    return C;
}
int isSubset(VirtualHeap VH, CBSET A, CBSET B){
    CBSET atrav, btrav;
    for(atrav = A, btrav = B; atrav != -1 && btrav != -1;){
        (VH.Nodes[atrav].data == VH.Nodes[btrav].data)? (atrav = VH.Nodes[atrav].link) : (btrav = VH.Nodes[btrav].link);
    }
    return (atrav == -1)? 1 : 0;
}
