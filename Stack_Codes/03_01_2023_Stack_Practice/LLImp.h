#ifndef LLSTACK_H
#define LLSTACK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char elem;
    struct node *link;
}*Stack;

void initStack(Stack *S){
    *S = NULL;
}
void display(Stack S){
    Stack trav;
    for(trav = S; trav != NULL; trav = trav->link){
        printf("%c -> ", trav->elem);
    }
    printf("NULL");
}
void push(char x, Stack *S){
    Stack temp = (Stack)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->elem = x;
        temp->link = *S;
        *S = temp;
    }
}
void pop(Stack *S){
    Stack temp;
    if(*S != NULL){
        temp = *S;
        *S = temp->link;
        free(temp);
    }
}
char top(Stack S){
    return S != NULL? S->elem : '\0';
}
int isEmpty(Stack S){
    return S == NULL ? 1:0;
}
#endif