#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct node {
  int value;
  struct node *left;
  struct node *right;
} *Node;

void initTree(Node* root);
void insert(Node* root, int elem);
int isMember(Node root,int elem);
void delete(Node* root, int elem);
void deleteAll(Node* root);

//BST Traversals
void preOrder(Node root);
void inOrder(Node root);
void postOrder(Node root);

int main(){
  Node root;

  initTree(&root);
  insert(&root, 5);
  insert(&root, 2);
  insert(&root, 3);
  insert(&root, 7);
  insert(&root, 9);
  insert(&root, 1);

  preOrder(root);
  printf("\n");
  inOrder(root);
  printf("\n");
  postOrder(root);

  int flag = isMember(root, 2);

  if(flag != 1){
    printf("\nNot a member\n");
  } else {
    printf("\nIs a member\n");
  } 

  delete(&root, 2);

  preOrder(root);

  return 0;
}

void initTree(Node* root){
  *root = NULL;
}

void insert(Node* root, int elem){
  Node *trav;
  for(trav = root; (*trav) != NULL; trav = (*trav)->value > elem ? &(*trav)->left : &(*trav)->right){}

  Node temp = (Node) malloc(sizeof(struct node));

  temp->value = elem;
  temp->left = NULL;
  temp->right = NULL;

  (*trav) = temp;
}

int isMember(Node root,int elem){
  Node trav;

  for(trav = root; trav != NULL && trav->value != elem; trav = trav->value > elem ? trav->left : trav->right){}

  return trav != NULL ? 1 : 0;
}

void delete(Node* root, int elem){
  Node *trav, temp;

  for(trav = root; (*trav)!=NULL && (*trav)->value != elem; trav = (*trav)->value > elem ? &(*trav)->left : &(*trav)->right){}

  if((*trav) != NULL){
      Node *ImSuccesor;
    if((*trav)->left != NULL && (*trav)->right != NULL){
      for(ImSuccesor = &(*trav)->left; (*ImSuccesor)->right != NULL; ImSuccesor = &(*ImSuccesor)->right){}

      (*trav)->value = (*ImSuccesor)->value;
      temp = (*ImSuccesor);
      (*ImSuccesor) = (*ImSuccesor)->left;
    } else {
      temp = (*trav);
      (*trav) = (*trav)->left != NULL ? (*trav)->left : (*trav)->right;
    }

    free(temp);
  }
}

void deleteAll(Node* root){
  if((*root) != NULL){
    deleteAll(&(*root)->left);
    deleteAll(&(*root)->right);

    free(*root);

    *root = NULL;
  }
}

//BST Traversals
void preOrder(Node root){
  if(root != NULL){
    printf("%d ", root->value);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(Node root){
    if(root != NULL){
    inOrder(root->left);
    printf("%d ", root->value);
    inOrder(root->right);
  }
}

void postOrder(Node root){
    if(root != NULL){
    postOrder(root->left);
    postOrder(root->right);  
    printf("%d ", root->value);
  }
}