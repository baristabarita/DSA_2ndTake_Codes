/*
ADT STACK Array Implementation Version 2
Version 2: List is a pointer to structure containing array and count
Note: this uses View 2 where Stack will grow from 0 to MAX-1 (usual for Array Imps)
*/

//A. Include files and macro definition
#include<stdio.h>
#include <stdlib.h>
#define MAX 10

//B. Data Structure definition
typedef struct node{
    char data[MAX];
    int top;
}*STACK;
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
    printf("Current top#: %d", S->top);
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
    (*S) = (STACK)malloc(sizeof(struct node));
    if((*S) != NULL){
        (*S)->top = -1;
    }
}
void push(STACK *S, char elem){
    if((*S)->top != MAX-1){
        //View2: top increases
        (*S)->top++;
        (*S)->data[(*S)->top] = elem;
    }
}
void pop(STACK *S){
    if((*S)->top != -1){
        //View2: top decreases
        (*S)->top--;
    }
}
char isTop(STACK S){
    return (S->top != -1)? S->data[S->top]:'\0';
}
int isEmpty(STACK S){
    return(S->top == -1)? 1 : 0;
}
int isFull(STACK S){
    return(S->top == MAX-1)? 1: 0;
}
void displayStack(STACK S){
    int index;
    for(index = S->top; index != -1; index--){
        printf("%c\n", S->data[index]);
    }
    printf("NULL/EMPTY\n");
}