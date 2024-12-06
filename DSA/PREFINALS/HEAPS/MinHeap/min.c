#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct heap {
    int node[MAX];
    int indx;
} * POT;

void initHeap(POT T);
void populate(int arr[], POT T, int size);
void insert(POT T, int num);
void heapify(POT T, int index);
void minHeap(POT T);
int deleteMin(POT T);
void displayTree(POT T);

int main() {
    POT T = (POT)malloc(sizeof(struct heap)); // Initialize the heap
    initHeap(T);

    int arr[] = {4, 3, 1, 5, 6, 8, 7, 9, 0};
    int size = sizeof(arr) / sizeof(arr[0]);

    populate(arr, T, size);
    minHeap(T);
    displayTree(T);

    printf("Deleted min: %d\n", deleteMin(T));
    displayTree(T);

    free(T); // Free allocated memory
    return 0;
}

void initHeap(POT T) {
    T->indx = -1;
}

void populate(int arr[], POT T, int size) {
    int i;
    for (i = 0; i < size; i++) {
        T->node[i] = arr[i];
    }
    T->indx = size - 1; // Set heap size
}

void insert(POT T, int num) {
    if (T->indx + 1 < MAX) {
        T->node[++T->indx] = num;
        int index;
        for (index = T->indx; index > 0 && T->node[(index - 1) / 2] > T->node[index]; index = (index - 1) / 2) {
            int temp = T->node[(index - 1) / 2];
            T->node[(index - 1) / 2] = T->node[index];
            T->node[index] = temp;
        }
    }
}

void heapify(POT T, int index) {
    if (T != NULL) {
        int smallest = index;
        int LC = index * 2 + 1;
        int RC = LC + 1;

        if (LC <= T->indx && T->node[LC] < T->node[smallest]) {
            smallest = LC;
        }

        if (RC <= T->indx && T->node[RC] < T->node[smallest]) {
            smallest = RC;
        }

        if (smallest != index) {
            int temp = T->node[smallest];
            T->node[smallest] = T->node[index];
            T->node[index] = temp;

            heapify(T, smallest);
        }
    }
}

void minHeap(POT T) {
    int i = (T->indx - 1) / 2;
    for (; i >= 0; i--) {
        heapify(T, i);
    }
}

int deleteMin(POT T) {
    if (T->indx != -1) {
        int elem = T->node[0];
        T->node[0] = T->node[T->indx--];

        heapify(T, 0);
        return elem;
    }
    return -1; // Return -1 if heap is empty
}

void displayTree(POT T) {
    if (T->indx == -1) {
        printf("Heap is EMPTY\n");
    } else {
        int i;
        printf("%-20s%-20s\n", "Index", "Priority");
        for (i = 0; i <= T->indx; i++) {
            printf("%-20d%-20d\n", i, T->node[i]);
        }
    }
    printf("\n");
}
