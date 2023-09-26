//AVL Tree Pract (not Gfg)
#include <stdio.h>
#include <stdlib.h>

//Data struct definition:
typedef struct node{
    int elem, height;
    struct node *left;
    struct node *right;
}*Tree;

int height(Tree *T);
int maxInt(int num1, int num2);
Tree *rightRotate(Tree *parent);
Tree *leftRotate(Tree *x);
int getBalance(Tree *T);
void insertAVL(Tree *T, int elem);
void preOrder(Tree T);
void initTree(Tree *T);

void main(){
    Tree T;
    initTree(&T);
    insertAVL(&T, 10);
    insertAVL(&T, 20);
    insertAVL(&T, 30);
    insertAVL(&T, 40);
    insertAVL(&T, 50);
    insertAVL(&T, 25);
    printf("Preorder traversal of the constructed AVl tree is: \n");
    preOrder(T);
}

void initTree(Tree *T){
    *T = NULL;
}
int height(Tree *T){
    return (T != NULL) ? (*T)->height : 0;
}
int maxInt(int num1, int num2){
    return (num1 > num2) ? num1 : num2;
}
Tree *rightRotate(Tree *nodeY){
    Tree *nodeX = (*nodeY)->left;
    Tree *leaf = (*nodeX)->right;

    //perform the rotation
    (*nodeX)->right = nodeY;
    (*nodeY)->left = leaf;

    //Update heights
    (*nodeY)->height = ((height((*nodeY)->left) > height((*nodeY)->right)) ? (*nodeY)->left : (*nodeY)->right) + 1;
    (*nodeX)->height = ((height((*nodeX)->left) > height((*nodeX)->right)) ? (*nodeX)->left : (*nodeX)->right) + 1;

    //return the nodeX as the new root of the tree
    return nodeX;
}
Tree *leftRotate(Tree *nodeX){
    Tree *nodeY = (*nodeX)->right;
    Tree *leaf = (*nodeY)->left;

    //perform rotation
    (*nodeY)->left = nodeX;
    (*nodeX)->right = leaf;

    //update heights
    (*nodeX)->height = ((height((*nodeX)->left) > height((*nodeX)->right)) ? (*nodeX)->left : (*nodeX)->right) + 1;
    (*nodeY)->height = ((height((*nodeY)->left) > height((*nodeY)->right)) ? (*nodeY)->left : (*nodeY)->right) + 1;

    //return nodeY as the new root
    return nodeY;
}
int getBalance(Tree *T){
    return(T != NULL) ? (height((*T)->left) - height((*T)->right)) : 0;
}
void insertAVL(Tree *T, int elem){
    //perform normal BST insertion
    Tree *trav;
    for(trav = T; *trav != NULL && (*trav)->elem != elem;){
        trav = ((*trav)->elem > elem) ? &(*trav)->left : &(*trav)->right;
    }
    if(*trav != NULL){
        (*trav)->elem = elem;
    }

    Tree temp = (Tree)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->elem = elem;
        temp->left = *trav;
        temp->right = *trav;
        temp->height = 1;
        *trav = temp;
    }

    //Update height of this ancestor node
    (*trav)->height = 1 + ((height((*trav)->left) > height((*trav)->right)) ? (*trav)->left : (*trav)->right);

    //get balance factor
    int balane = (*trav != NULL) ? (height((*trav)->left) - height((*trav)->right)) : 0;

    //Left left case
    if(balane > 1 && elem < (*trav)->left->elem){
        return rightRotate(*trav);
    }

    //Right right Case
    if(balane < -1 && elem > (*trav)->right->elem){
        return leftRotate(*trav);
    }

    // Left Right Case
    if(balane > 1 && elem >(*trav)->left->elem){
        (*trav)->left = leftRotate((*trav)->left);
        return rightRotate(*trav);
    }

    //Right Left Case
    if(balane < -1 && elem < (*trav)->right->elem){
        (*trav)->right = rightRotate((*trav)->right);
        return leftRotate(*trav);
    }
    
}
void preOrder(Tree T){
    if(T != NULL){
        printf("%d ", T->elem);
        preOrder(T->left);
        preOrder(T->right);
    }
}
