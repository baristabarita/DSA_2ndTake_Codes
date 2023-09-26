// ADT Trees Operations (Parent-Pointer / array representaion)

#include <stdio.h>

#define SIZE 10

typedef int Tree[SIZE];
typedef int node;

node PARENT(node n, Tree T);
node LEFTMOST_CHILD(node n, Tree T);
node RIGHT_SIBLING(node n, Tree T);
node ROOT(Tree T);
void INITIALIZE(Tree T);

void main(){

}
void INITIALIZE(Tree T){
    int index;
    for(index = 0; index < SIZE; index++){
        T[index] = -2;
    }
}
node PARENT(node n, Tree T){
    return(n < SIZE && T[n] != -2) ? T[n] : -2;
}
node LEFTMOST_CHILD(node n, Tree T){ // we must assume artificail ordering
    int i;
    for(i = 0; i < SIZE && n != T[i]; i++){}
    return(i < SIZE) ? i : -2;    
}
node RIGHT_SIBLING(node n, Tree T){
    int i;
    node r = -2;
    node p = T[n];
    int ctr = 0;

    for(i = 0; i < SIZE; i++){
        if(T[i] == p && i > n && ctr == 0){
            r = i;
            ctr++;
        }
    }
    return r;
}
node ROOT(Tree T){
    int i;
    for(i = 0; i < SIZE && T[i] != -1; i++){}
    return (i < SIZE)? i : -2;
}
