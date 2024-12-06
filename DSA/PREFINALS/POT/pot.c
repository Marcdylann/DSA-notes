#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pot{
  int nodes[MAX];
  int lastIndex;
} *POT;

void init(POT heap);
void display(POT heap);
void insert(POT heap, int elem);
void populate(POT heap,int data[],int size);
void maxHeap(POT heap);
void heapify(POT heap,int parent);
int deleteMax(POT heap);

int main(){
  int arr[] = {5,6,3,8,9,4,0,1};
  int size = sizeof(arr) / sizeof(arr[0]);

  POT T;
  T = (POT)malloc(sizeof(struct pot));
  init(T);

  populate(T, arr, size);

  display(T);

  maxHeap(T);

  display(T);
  
  int elem = deleteMax(T);
  printf("\n%d was removed\n", elem);

  display(T);

  return 0;
}

void init(POT heap){
  heap->lastIndex = -1;
}

void display(POT heap){
  int i;
  for(i = 0; i <= heap->lastIndex; i++){
    printf("%d ", heap->nodes[i]);
  }

  printf("\n");
}

void insert(POT heap, int elem){
  if(heap->lastIndex + 1 < MAX){
    heap->nodes[++heap->lastIndex] = elem;

    int idx;

    for(idx = heap->lastIndex; idx > 0 && heap->nodes[idx] > heap->nodes[(idx-1)/2]; idx = (idx-1)/2){
      int temp = heap->nodes[idx];
      heap->nodes[idx] = heap->nodes[(idx-1)/2];
      heap->nodes[(idx-1)/2] = temp;
    }
  }
}

void populate(POT heap,int data[],int size){
  int i;
  for(i = 0; i < size; i++){
    heap->nodes[i] = data[i];
    heap->lastIndex++;
  }
}

void maxHeap(POT heap){
  int idx = (heap->lastIndex - 1) / 2;

  while(idx >= 0){
    heapify(heap, idx);
    idx--;
  }
}

void heapify(POT heap,int parent){
  int largest = parent;
  int LC = parent * 2 + 1;
  int RC = parent * 2 + 2;

  if(LC <= heap->lastIndex && heap->nodes[largest] < heap->nodes[LC]){
    largest = LC;
  }

  if(RC <= heap->lastIndex && heap->nodes[largest] < heap->nodes[RC]){
    largest = RC;
  }

  if(largest != parent){
    int temp = heap->nodes[largest];
    heap->nodes[largest] = heap->nodes[parent];
    heap->nodes[parent] = temp;

    heapify(heap, largest); 
  }
}

int deleteMax(POT heap){
  if(heap->lastIndex >= 0){
    int temp = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->lastIndex];
    heap->nodes[heap->lastIndex--] = temp;

    heapify(heap,0);

    return temp;
  }
  return -1;
}