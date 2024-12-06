#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node{
  int data;
  struct node *link;
} *SET;

typedef SET Dictionary[MAX];

typedef enum {TRUE, FALSE} Boolean;

int hashIndx(int elem);
void initDictionary(Dictionary D);
void displayDictionary(Dictionary D);
Boolean isMember(Dictionary D, int elem);
void insertUnique(Dictionary D, int elem);
void deleteMem(Dictionary D, int num);

int main(){
  Dictionary D;
  initDictionary(D);

  displayDictionary(D);

  insertUnique(D, 5);
  insertUnique(D, 23);
  insertUnique(D, 10);
  insertUnique(D, 25);
  insertUnique(D, 33);
  insertUnique(D, 54);
  insertUnique(D, 2);
  insertUnique(D, 1);
  insertUnique(D, 11);

  displayDictionary(D);

  deleteMem(D, 23);
  displayDictionary(D);

  return 0;

}

int hashIndx(int elem){

  return elem % MAX;
}

void initDictionary(Dictionary D){
  int i;
  for(i = 0; i < MAX; i++){
    D[i] = NULL;
  }
}

void displayDictionary(Dictionary D){
  int i;
  printf("\n");
  for( i = 0; i < MAX; i++){
    SET trav;
    printf("%d -> ", i);
    if(D[i] == NULL){
      printf("EMPTY");
    } else {
      for(trav = D[i]; trav != NULL; trav = trav->link){
      printf("[%d] ", trav->data);
      }
    }
    printf("\n");
  }
}

Boolean isMember(Dictionary D, int elem){
  int hash = hashIndx(elem);

  SET trav;
  for(trav = D[hash]; trav != NULL && trav->data != elem; trav = trav->link){}

  return (trav == NULL) ? FALSE : TRUE;
}

void insertUnique(Dictionary D, int elem){
  int key = hashIndx(elem);

  SET *trav, temp;
  for((trav) = &D[key]; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link){}

  if((*trav) != NULL && (*trav)->data == elem){
    printf("\nElement is already in the set");
  } else {
    temp = (SET)malloc(sizeof(struct node));
    temp->data = elem;
    temp->link = (*trav);

    (*trav) = temp;
  }
}

void deleteMem(Dictionary D, int num){
  int key = hashIndx(num);
  SET *trav, temp;

  for(trav = &D[key]; (*trav) != NULL && (*trav)->data != num; trav = &(*trav)->link){}

  if((*trav) != NULL){
    temp = (*trav);
    (*trav) = temp->link;
    free(temp);
  } else {
    printf("Element does not exist");
  }
}
