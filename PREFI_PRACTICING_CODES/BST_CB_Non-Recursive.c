#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

//Data Structure Definitions
typedef struct{
    int elem;
    int LC;
    int RC;
}NodeType;

typedef struct node{
    NodeType Node[SIZE];
    int Avail;
}VHeap;

typedef int BST;

//Function Prototypes
void INITIALIZE(BST *T, VHeap *VH);
void INSERT(BST *T, VHeap *VH, int node);
int ISMEMBER(BST T, VHeap VH, int node);
void DELETE(BST *T, VHeap *VH, int node);
int MIN(BST T, VHeap VH);
int MAX(BST T, VHeap VH);

void PREORDER(BST T, VHeap VH);
void INORDER(BST T, VHeap VH);
void POSTORDER(BST T, VHeap VH);

void main(){
    printf("\n - - Initialize the BST Tree and VHeap - -\n");
    BST T;
    VHeap VH;
    INITIALIZE(&T, &VH);

    printf("\n- - Insert of Nodes of Set T = {10, 5, 14, 12, 7, 18, 15} - -\n");
    INSERT(&T, &VH, 10);
    INSERT(&T, &VH, 5);
    INSERT(&T, &VH, 14);
    INSERT(&T, &VH, 12);
    INSERT(&T, &VH, 7);
    INSERT(&T, &VH, 18);
    INSERT(&T, &VH, 15);
    printf("\n- - Display Traversals - -\n");
    printf("\nPREORDER : ");
    PREORDER(T, VH);
    printf("\nINORDER : ");
    INORDER(T, VH);
    printf("\nPOSTORDER : ");
    POSTORDER(T, VH);
    printf("\nCurrent MIN: %d", MIN(T,VH));
    printf("\nCurrent MAX: %d", MAX(T,VH));
    printf("\n- - Deleting Nodes - -\n");
    DELETE(&T,&VH,7);
    DELETE(&T, &VH, 5);
    DELETE(&T, &VH, 18);
    DELETE(&T, &VH, 10);
    printf("\n- - Display Traversals After Delete - -\n");
    printf("\nPREORDER : ");
    PREORDER(T, VH);
    printf("\nINORDER : ");
    INORDER(T, VH);
    printf("\nPOSTORDER : ");
    POSTORDER(T, VH);   
    printf("\n Is 14 a member ?: %d", ISMEMBER(T,VH,14));
    printf("\n Is 5 a member ?: %d", ISMEMBER(T,VH,5));
    
}

void INITIALIZE(BST *T, VHeap *VH){
    int index;

    //initialize BST
    *T = -1; 
    //initialize Virtual Heap
    VH->Avail = 0;
    for(index = 0; index < SIZE-1; index++){
        VH->Node[index].LC = index+1;
        VH->Node[index].RC = index+1;
    }
    VH->Node[index].LC = VH->Node[index].RC = -1;
}
void INSERT(BST *T, VHeap *VH, int node){
    BST *trav;
    for(trav = T; *trav != -1 && VH->Node[*trav].elem != node;){
        trav = node < VH->Node[*trav].elem ? &VH->Node[*trav].LC : &VH->Node[*trav].RC;
    }
    
    if(*trav == -1){
        *trav = VH->Avail;
        if(*trav != -1){
            VH->Avail = VH->Node[*trav].LC != -1 ? VH->Node[*trav].LC : VH->Node[*trav].RC;
            VH->Node[*trav].elem = node;
            VH->Node[*trav].LC = VH->Node[*trav].RC = -1;
        }
    }
}
int ISMEMBER(BST T, VHeap VH, int node){
    BST trav;
    for(trav = T; trav != -1 && VH.Node[trav].elem != node;){
        trav = (VH.Node[trav].elem > node)? VH.Node[trav].LC : VH.Node[trav].RC;
    }
    return(trav == -1)? 0 : 1;
}
void DELETE(BST *T, VHeap *VH, int node){
    BST *trav, *trav2, temp;
    if(*T != -1){
        for(trav = T; *trav != -1 && VH->Node[*trav].elem != node;){
            trav = (VH->Node[*trav].elem > node)? &VH->Node[*trav].LC : &VH->Node[*trav].RC;
        }

        if(VH->Node[*trav].LC != -1 && VH->Node[*trav].RC != -1){ //if two children
            for(trav2 = &VH->Node[*trav].RC; VH->Node[*trav2].LC != -1; trav2 = &VH->Node[*trav2].LC){} //finding
            temp = *trav2;
            *trav2 = VH->Node[temp].RC;
            VH->Node[*trav].elem = VH->Node[temp].elem;
        }else{
            temp = *trav;
            *trav = (VH->Node[*trav].LC == -1)? VH->Node[*trav].RC : VH->Node[*trav].LC;
        }
        //dealloc space
        VH->Node[temp].LC = VH->Node[temp].RC = VH->Avail;
        VH->Avail = temp;


    } else {
        *T = -1;
    }
}
int MIN(BST T, VHeap VH){
    BST trav;
    for(trav = T; trav != -1 && VH.Node[trav].LC != -1; trav = VH.Node[trav].LC){}
    return VH.Node[trav].elem;
}
int MAX(BST T, VHeap VH){
    BST trav;
    for (trav = T; trav != -1  && VH.Node[trav].RC != -1; trav = VH.Node[trav].RC){}
    return VH.Node[trav].elem;
}

void PREORDER(BST T, VHeap VH){
    if(T != -1){
        printf("%d ", VH.Node[T].elem);
        PREORDER(VH.Node[T].LC, VH);
        PREORDER(VH.Node[T].RC, VH);
    }
}
void INORDER(BST T, VHeap VH){
    if(T != -1){
        INORDER(VH.Node[T].LC, VH);
        printf("%d ", VH.Node[T].elem);
        INORDER(VH.Node[T].RC, VH);
    }
}
void POSTORDER(BST T, VHeap VH){
    if(T != -1){
        POSTORDER(VH.Node[T].LC, VH);
        POSTORDER(VH.Node[T].RC, VH);
        printf("%d ", VH.Node[T].elem);
    }
}

