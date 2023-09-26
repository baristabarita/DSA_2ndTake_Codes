#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include <stdio.h>
#include <stdlib.h>

#define MAX 8
typedef struct{
    char elem[MAX];
    int top;
}Stack;

void initStack(Stack *S){
    S->top = -1;
}
void push(char x, Stack *S){
    if(S->top != MAX-1){
        S->top++;
        S->elem[S->top] = x;
    }
}
void pop(Stack *S){
    if(S->top != -1){
        S->top--;
    }
}
char top(Stack S){
    return S.top != -1? S.elem[S.top] : '\0';
}
int isEmpty(Stack S){
    return S.top == -1? 1: 0;
}
int isFull(Stack S){
    return S.top == MAX ? 1:0;
}

void display(Stack S){
    for(;S.top != -1; S.top--){
        printf("%c ", S.elem[S.top]);
    }
}
#endif