#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int elem;
  struct node *LC;
  struct node *RC;
} *Node;

Node createNode(int data);
void insert(Node *node, int data);
void preOrder(Node node);
void inOrder(Node node);
void postOrder(Node node);
int sum(Node root);
bool isMember(Node root, int target);
int min(Node root);
int max(Node root);
void delete(Node *root, int target);

int main(void) {
  Node tree = NULL;
  insert(&tree, 4);
  insert(&tree, 2);
  insert(&tree, 5);
  insert(&tree, 1);
  insert(&tree, 3);
  preOrder(tree);
  printf("\n");
  inOrder(tree);
  printf("\n");
  postOrder(tree);
  printf("\n");
  printf("Sum = %d\n", sum(tree));
  printf("isMember(1) = %d\n", isMember(tree, 1));
  printf("isMember(4) = %d\n", isMember(tree, 4));
  printf("isMember(3) = %d\n", isMember(tree, 3));
  printf("isMember(99) = %d\n", isMember(tree, 99));
  printf("max() = %d\n", max(tree));
  printf("min() = %d\n", min(tree));
  delete (&tree, 2);
  preOrder(tree);
}

Node createNode(int data){
  Node newNode = (Node)malloc(sizeof(struct node));

  if(newNode != NULL){
  newNode->elem = data;
  newNode->LC = NULL;
  newNode->RC = NULL;
  }

  return newNode;
}

void insert(Node *node, int data){
  Node* trav = node;
  if((*trav) == NULL){
    (*trav) = createNode(data);
  } else {
    for(;(*trav) != NULL; trav = (data < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC){}

    if((*trav) == NULL){
      (*trav) = createNode(data);
    }
  }
}

void preOrder(Node node){
  if(node != NULL){
    printf("%d ", node->elem);
    preOrder(node->LC);
    preOrder(node->RC);
  }
}

void inOrder(Node node){
   if(node != NULL){
    inOrder(node->LC);
    printf("%d ", node->elem);
    inOrder(node->RC);
  }
}

void postOrder(Node node){
     if(node != NULL){
    postOrder(node->LC);
    postOrder(node->RC);
    printf("%d ", node->elem);
  }
}

int sum(Node root){
  if(root == NULL){
    return 0;
  } 

  return root->elem + sum(root->LC) + sum(root->RC);
}

bool isMember(Node root, int target){
  if(root != NULL){
    Node trav;
    for(trav = root; trav != NULL && trav->elem != target; trav = (target < trav->elem) ? trav->LC : trav->RC){}

    return (trav == NULL) ? false : true;
  } else {
    return false;
  }
}

int min(Node root){
  Node trav;
  for(trav = root; trav->LC != NULL; trav = trav->LC);

  return (trav != NULL) ? trav->elem : 0;
}

int max(Node root){
    Node trav;
  for(trav = root; trav->RC != NULL; trav = trav->RC);

  return (trav != NULL) ? trav->elem : 0;
}

void delete(Node *root, int target){
  if(root != NULL){
    Node *trav;
    for(trav = root; (*trav) != NULL && (*trav)->elem != target; trav = ((*trav)->elem < target) ? &(*trav)->RC : &(*trav)->LC){}

    if((*trav) != NULL){
      if((*trav)->LC != NULL && (*trav)->RC != NULL){
        Node *temp;
        for(temp = &(*trav)->RC; (*temp)->LC != NULL; temp = &(*temp)->LC){}

        (*trav)->elem = (*temp)->elem;

        Node temp2 = (*temp);
        (*temp) = NULL;
        free(temp2);
      } else if((*trav)->LC == NULL && (*trav)->RC == NULL){
        Node trav2 = (*trav);
        *trav = NULL;
        free(trav2);
      } else if ((*trav)->LC != NULL) {
        Node temp2 = *trav;
        *trav = (*trav)->LC;  // Move the left child up
        free(temp2);
      } 
      else if ((*trav)->RC != NULL) {
        Node temp2 = *trav;
        *trav = (*trav)->RC;  // Move the right child up
        free(temp2);
      } 
    }
  }
}
