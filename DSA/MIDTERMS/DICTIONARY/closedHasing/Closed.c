#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef int Dictionary[MAX];

typedef enum {
    EMPTY = -1,
    DELETED = -2
} DictStatus;

void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, int data);
bool inDict(Dictionary D, int data);
void delete(Dictionary D, int data);
void printDict(Dictionary D);

int main() {
    Dictionary D;

    initDict(D);

    insert(D, 1);
    insert(D, 2);
    insert(D, 3);
    insert(D, 5);
    insert(D, 15);
    insert(D, 25);
    insert(D, 35);
    insert(D, 45);
    insert(D, 55);

    int find = 3;
    printf("The element %d %s in the Dictionary\n", find, (inDict(D, find) == true) ? "IS" : "IS NOT");

    delete(D, find);

    insert(D, 65); // replaced number 3 
    insert(D, 75);
    insert(D, 85); // make dictionary full

    printDict(D);

    return 0;
}

void initDict(Dictionary D){
  int i;
  for(i = 0; i < MAX; i++){
    D[i] = EMPTY;
  }
}

int hash(int data){
  return data % MAX;
}

void insert(Dictionary D, int data) {
  int start = hash(data); 
  int index = start;      
  int avail = -1;         
  bool isfull = false;

  while (D[index] != EMPTY && D[index] != data && !isfull) {
    if (avail == -1 && D[index] == DELETED) {
      avail = index; 
    }

    index = (index + 1) % MAX; 

    if (index == start) {
      printf("\nDictionary is full!\n");
      isfull = true;
    }

  }

  if (D[index] == data) {
    printf("\nElement %d is already in the dictionary!\n", data);
  } else {
    D[avail != -1 ? avail : index] = data;
  }
}


bool inDict(Dictionary D, int data){
  int start = hash(data);
  int index = start;
  bool isFull = false;

  while(D[index] != data && !isFull && D[index] != EMPTY){

    index = (index + 1) % MAX;

    if(index == start) {
      isFull = true;
    }

  }

  return (!isFull) ? true : false;
}

void delete(Dictionary D, int data){
  int start = hash(data);
  int index = start;
  bool isFull = false;

  while(D[index] != data && !isFull && D[index] != EMPTY){

    index = (index + 1) % MAX;

    if(index == start) {
      isFull = true;
    }
  }

  if(D[index] == data){
    D[index] = DELETED;
  }

}

void printDict(Dictionary D) {
    for(int i = 0; i < MAX; i++) {
        if(D[i] == EMPTY) {
            printf("EMPTY\n");
        }
        else if(D[i] == DELETED) {
            printf("DELETED\n");
        }
        else {
            printf("%d\n", D[i]);
        }
    }
}