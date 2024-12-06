#include <stdio.h>
#include <stdlib.h>

#define MAX 15

typedef struct heap{
  int nodes[MAX];
  int LastIndex;
} *Tree;

void initTree(Tree *T);
void insertNode(Tree T, int elem);
void heapify(Tree T, int parent);
void maxHeap(Tree T);
int deleteMax(Tree T);
void displayTree(Tree T);
void populate(int arr[], int size, Tree T);

int main(){
  Tree T = (Tree)malloc(sizeof(struct heap));
  int arr[] = {23,10,15,70,25,53,12,72,45,2,5,18,6,20,69};
  int size = sizeof(arr) / sizeof(arr[0]);
  initTree(&T);

  populate(arr, size, T);
  displayTree(T);
  maxHeap(T);
  displayTree(T);

  // int i = deleteMax(T);
  // printf("\n%d is deleted\n", i);

  // displayTree(T);

    free(T); // Free allocated memory
    return 0;
}

void initTree(Tree *T) {
    *T = (Tree)malloc(sizeof(struct heap)); // Allocate memory for the entire structure
    (*T)->LastIndex = -1;
}

void insertNode(Tree T, int elem){
  if(T->LastIndex + 1 < MAX){
    T->nodes[++T->LastIndex] = elem;
    int parent = (T->LastIndex - 1)/ 2;

    if(T->nodes[parent] < T->nodes[T->LastIndex]){
      int temp = T->nodes[parent];
      T->nodes[parent] = elem;
      T->nodes[T->LastIndex] = temp;
    }
  } else {
    printf("\nFULL");
  }
}

void heapify(Tree T, int parent){
  if(T->LastIndex != -1){
    int largest = parent;
    int LC = parent * 2 + 1;
    int RC = LC + 1;

    if(LC <= T->LastIndex && T->nodes[LC] > T->nodes[largest]){
      largest = LC;
    }

    if(RC <= T->LastIndex && T->nodes[RC] > T->nodes[largest]){
      largest = RC;
    }

    if(largest != parent){
      int temp = T->nodes[largest];
      T->nodes[largest] = T->nodes[parent];
      T->nodes[parent] = temp;

      heapify(T, largest); 
    }
  }
}

void maxHeap(Tree T){
  if(T->LastIndex != -1){
  for(int i = (T->LastIndex - 1) / 2; i >= 0; i--){
    heapify(T, i);
    }
  } else {
    printf("\nEMPTY");
  }
}

int deleteMax(Tree T){
  if(T->LastIndex != -1){
    int max = T->nodes[0];
    T->nodes[0] = T->nodes[T->LastIndex--];
    T->nodes[T->LastIndex + 1] = max;
    heapify(T, 0);
    return max;
  }
    printf("Heap is EMPTY\n");
    return -1;
}

void displayTree(Tree T) {
    if (T->LastIndex == -1) {
        printf("Heap is EMPTY\n");
    } else {
        int i;
        printf("%-20s%-20s\n", "Index", "Priority");
        for (i = 0; i <= T->LastIndex; i++) {
            printf("%-20d%-20d\n", i, T->nodes[i]);
        }
    }
    printf("\n");
}

void populate(int arr[], int size, Tree T) {
    int i;
    for (i = 0; i < size; i++) {
        T->nodes[i] = arr[i];
    }
    T->LastIndex = size - 1; // Set heap size
}