#include <stdio.h>
#include <stdlib.h>

#define MAX 6

typedef char circularArr[MAX];

typedef enum {TRUE, FALSE} BOOLEAN;

typedef struct queue{
  int rear;
  int front;
  circularArr Queue;
} CQ;

void initQueue(CQ *Q);
BOOLEAN isEmpty(CQ Q);
BOOLEAN isFull(CQ Q);
char front(CQ Q);
void enQueue(CQ *Q, char elem);
void deQueue(CQ *Q);

int main(){
  CQ Queue;
  initQueue(&Queue);

  BOOLEAN status = isEmpty(Queue);
  (!status) ? printf("\nIs empty") : printf("\nis not empty");

  enQueue(&Queue,'A');
  enQueue(&Queue, 'B');
  enQueue(&Queue,'C');

  char elem = front(Queue);

  printf("\nFront is %c ", elem);

  deQueue(&Queue);
  printf("\nDequeued successfuly!");

  elem = front(Queue);

  printf("\nFront is %c ", elem);

  deQueue(&Queue);
  printf("\nDequeued successfuly!");

  elem = front(Queue);

  printf("\nFront is %c ", elem);
  deQueue(&Queue);
  deQueue(&Queue);

  enQueue(&Queue,'A');
  enQueue(&Queue, 'B');
  enQueue(&Queue,'C');
  enQueue(&Queue,'A');
  enQueue(&Queue, 'B');
  enQueue(&Queue,'C');

  return 0;
}

void initQueue(CQ *Q){
  Q->rear = MAX-1;
  Q->front = 0;
}

BOOLEAN isEmpty(CQ Q){
  return ((Q.rear + 1) % MAX == Q.front) ? TRUE : FALSE;
}

BOOLEAN isFull(CQ Q){
  return ((Q.rear + 2) % MAX == Q.front) ? TRUE : FALSE;
}

char front(CQ Q){
  if((Q.rear + 1) % MAX != Q.rear){
  return Q.Queue[Q.front];
  } else {
    return '\0';
  }
}

void enQueue(CQ *Q, char elem){
  if((Q->rear + 2) % MAX != Q->front){
    Q->rear = (Q->rear + 1) % MAX;

    Q->Queue[Q->rear] = elem;
  } else {
    printf("\nFULL QUEUE");
  }
}

void deQueue(CQ *Q){
  if((Q->rear + 1) % MAX != Q->front){
    Q->front = (Q->front + 1) % MAX;
  } else {
    printf("\nEMPTY QUEUE");
  }
}