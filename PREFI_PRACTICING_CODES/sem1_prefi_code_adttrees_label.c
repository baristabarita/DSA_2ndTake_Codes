#include<stdio.h>

#define TSIZE 10
typedef int Node;
typedef struct{
    Node parent;
    char label;
}TNode;

typedef TNode PTree[TSIZE];

void INITIALIZE(PTree T);
void POPULATE(Node par, Node new, char lbl, PTree T);
char getRightSiblingLabel(Node node, PTree T);
void DISPLAY(PTree T);

void main(){

}

void INITIALIZE(PTree T){
    int index;
    for(index = 0; index < TSIZE; T[index].parent = -2, index){}
}
void POPULATE(Node par, Node new, char lbl, PTree T){
    if(new < TSIZE){
        T[new].parent = par;
        T[new].label = lbl;
    }
}
char getRightSiblingLabel(Node node, PTree T){
    int index;
    char r_s = '*';

    for(index = 0; index < TSIZE && r_s == '*'; index++){
        if(T[index].parent == T[node].parent && index > node){
            r_s = T[index].label;
        }
    }

    return r_s;
}

void DISPLAY(PTree T){
    int index;

    for(index = 0; index < TSIZE; index++){
        printf("[%d] %d | %c \n", index, T[index].parent, T[index].label);
    }
    printf("\n");
}