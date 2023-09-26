//GeeksforGeeks AVL TREE Practice
#include <stdio.h>
#include <stdlib.h>

//Data Struct def
struct node{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

//utility func to get the height of the tree
int height(struct node *N){
    if(N == NULL)
        return 0;
    return N->height;
}

//utility func to get the maximum of two integers
int max(int a, int b){
    return(a > b) ? a : b;
}
/*
    Helper function that allocates a new node with the given key
    and NULL left and right pointers
*/
struct node* newNode(int key){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; //new node is initially added at leaf
    return(node);
}


// Utility function to right rotate subtree rooted with y
struct node *rightRotate(struct node *y){
    struct node *x = y->left;
    struct node *T2 = x->right;

    //perform rotation
    x->right = y;
    y->left = T2;

    //Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    //return new root
    return x;
}

struct node *leftRotate(struct node *x){
    struct node *y = x->right;
    struct node *T2 = y->left;

    //perform rotationj
    y->left = x;
    x->right = T2;

    //Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    //return new root;
    return y;
}
int getBalance(struct node *N){
    if(N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key){
    //1. perform normal BST insertion
    if(node == NULL){
        return(newNode(key));
    }

    if(key < node->key)
        node->left = insert (node->left, key);
    else if(key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    //2. Update hieght of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    /*
      3. Get the balance factor of this ancestor node
      to check whether this node became unbalanced
    */
   int balance = getBalance(node);

   //If this node becmes unbalanced, then there are 4 cases
   
   //Left Left Case
   if(balance > 1 && key < node->left->key){
    return rightRotate(node);
   }

   //Right Right Case
   if(balance < -1 && key > node->right->key){
    return leftRotate(node);
   }
    // Left Right Case
   if(balance > 1 && key > node->left->key){
    node->left = leftRotate(node->left);
    return rightRotate(node);
   }

   // Right Left Case
   if(balance < -1 && key < node->right->key){
    node->right = rightRotate(node->right);
    return leftRotate(node);
   }

   return node;
}

//utility func to print preorder traversal of tree
//also prints the height of every npde

void preOrder(struct node *root){
    if(root != NULL){
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void main(){
    struct node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the constructed AVl tree is: \n");
    preOrder(root);
}