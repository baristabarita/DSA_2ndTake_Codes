/*
ADT STACK Linked List Implementation
*/

//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>

//B. Data Structure definition
typedef struct node{
    char data;
    struct node *link;
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
    push(&S, 'Z');
    push(&S, 'E');
    push(&S, 'E');
    push(&S, 'D');
    displayStack(S);
    printf("\n***** CHECK TOP, ISEMPTY, ISFULL *****\n");
    printf("Current top: %c\n", isTop(S));
    printf("is Empty?: %d\n", isEmpty(S));
    printf("\n***** POP ELEMENTS *****\n");
    pop(&S);
    pop(&S);
    displayStack(S);
    printf("\n***** CHECK TOP, ISEMPTY, ISFULL *****\n");
    pop(&S);
    pop(&S);
    printf("Current top: %c\n", isTop(S));
    printf("after popping all elems, is Empty?: %d\n", isEmpty(S));

}
//E. Function definitions of the prototypes
void initStack(STACK *S){
    *S = NULL;
}
void push(STACK *S, char elem){
    STACK temp = (STACK)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->data = elem;
        temp->link = *S;
        *S = temp;
    }
}
void pop(STACK *S){
    STACK temp;
    if(*S != NULL){
        temp = *S;
        *S = temp->link;
        free(temp);
    }
}
char isTop(STACK S){
    return(S != NULL)? S->data : '\0';
}
int isEmpty(STACK S){
    return (S == NULL)? 1 : 0;
}
void displayStack(STACK S){
    STACK trav;
    for(trav = S; trav != NULL; trav = trav->link){
        printf("%c -> ", trav->data);
    }
    printf("NULL\n");
}