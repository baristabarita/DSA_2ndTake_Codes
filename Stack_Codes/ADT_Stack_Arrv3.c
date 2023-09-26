/*
ADT STACK Array Implementation Version 3
Version 3: List is a structure containing a pointer 
           to dynamically allocated array and count
Note: this uses View 2 where Stack will grow from 0 to MAX-1 (usual for Array Imps)
*/

//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
//B. Data Structure definition
typedef struct node{
    char *elemPtr;
    int top;
}STACK;
//C. Function prototypes
void initStack(STACK *S);
void push(STACK *S, char elem);
void pop(STACK *S);
char isTop(STACK S);
int isEmpty(STACK S);
int isFull(STACK S);
void displayStack(STACK S);

//D. Function main
void main(){
    STACK S;
    printf("\n***** INITIALIZATION *****\n");
    initStack(&S);
    displayStack(S);
    printf("\n***** PUSH ELEMENTS *****\n");
    push(&S, 'L');
    push(&S, 'L');
    push(&S, 'Z');
    push(&S, 'T');
    push(&S, 'U');
    push(&S, 'N');
    push(&S, 'Z');
    push(&S, 'E');
    push(&S, 'E');
    push(&S, 'D');
    displayStack(S);
    printf("\n***** CHECK TOP, ISEMPTY, ISFULL *****\n");
    printf("Current top: %c\n", isTop(S));
    printf("is Full?: %d\n", isFull(S));
    printf("is Empty?: %d\n", isEmpty(S));
    printf("\n***** POP ELEMENTS *****\n");
    pop(&S);
    pop(&S);
    displayStack(S);
    printf("\n***** CHECK TOP, ISEMPTY, ISFULL *****\n");
    printf("Current top: %c\n", isTop(S));
    printf("is Full?: %d\n", isFull(S));
    pop(&S);
    pop(&S);
    pop(&S);
    pop(&S);
    pop(&S);
    pop(&S);
    pop(&S);
    pop(&S);
    printf("after popping all elems, is Empty?: %d\n", isEmpty(S));

}
//E. Function definitions of the prototypes
void initStack(STACK *S){
    S->elemPtr = (char*)malloc(sizeof(char)*MAX);
    if(S->elemPtr != NULL){
        S->top = -1;
    }
}
void push(STACK *S, char elem){
    if(S->top != MAX-1){
        //View2: top increases when push
        S->top++;
        S->elemPtr[S->top] = elem;
    }
}
void pop(STACK *S){
    if(S->top != -1){
        S->top--;
    }
}
char isTop(STACK S){
    return(S.top != -1)? S.elemPtr[S.top] : '\0';
}
int isEmpty(STACK S){
    return(S.top == -1)? 1 : 0;
}
int isFull(STACK S){
    return(S.top == MAX-1)? 1 : 0 ;
}
void displayStack(STACK S){
    for(;S.top != -1; S.top--){
        printf("%c\n", S.elemPtr[S.top]);
    }
    printf("NULL/EMPTY\n");
}
