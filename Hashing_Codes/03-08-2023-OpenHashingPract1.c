//A. Include files and macro definition
#include<stdio.h>
#include<stdlib.h>

#define SIZE 10

//B. Data Structure definition
typedef struct node{
    int elem;
    struct node *link;
}LIST;

typedef LIST Dictionary[SIZE];
typedef int Set[];

//C. Function prototypes
int hash(int elem);
void initDic(Dictionary *D);
void displayDic();
void insert(Dictionary *D, int elem);
void populateDic(Set S, Dictionary *D);
void delete(Dictionary *D, int elem);
int isMember(Dictionary D, int elem);

//D. Function main
void main(){
    //Task1: initialize the dictionary and display the contents of dictionary
    Dictionary D;
    Set S = {0, 13, 20, 28, 30, 33, 45, 48, 108};
    initDic(&D);
    displayDic();
    //Task2: Populate Dictionary and display the elements of the dictionary
    populateDic(S, &D);
    displayDic();
    
    //Task3: 
}

//E. Function definitions of the prototypes
int hash(int elem){
    return (elem % 10);
}