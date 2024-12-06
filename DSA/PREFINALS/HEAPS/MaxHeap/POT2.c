#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct heap {
    int nodes[MAX];
    int LastIndex;
} * Tree;

void initTree(Tree *T);
void insertNode(Tree T, int elem);
void heapify(Tree T, int parent);
void maxHeap(Tree T);
int deleteMax(Tree T);
void displayTree(Tree T);
void populate(int arr[], int size, Tree T);

int main() {
    Tree T = (Tree)malloc(sizeof(struct heap));
    int arr[] = {5, 3, 6, 7, 4, 9, 1, 2, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    initTree(&T);

    populate(arr, size, T);
    displayTree(T);
    maxHeap(T);
    displayTree(T);

    int i = deleteMax(T);
    printf("\n%d is deleted\n", i);
    displayTree(T);

    free(T); // Free allocated memory
    return 0;
}

void initTree(Tree *T) {
    (*T)->LastIndex = -1;
}

void insertNode(Tree T, int elem) {
    if (T->LastIndex + 1 < MAX) {
        T->nodes[++T->LastIndex] = elem;
        int current = T->LastIndex;
        while (current > 0) {
            int parent = (current - 1) / 2;
            if (T->nodes[parent] < T->nodes[current]) {
                int temp = T->nodes[parent];
                T->nodes[parent] = T->nodes[current];
                T->nodes[current] = temp;
                current = parent;
            } else {
                break;
            }
        }
    } else {
        printf("\nHeap is FULL\n");
    }
}

void heapify(Tree T, int parent) {
    if (T->LastIndex != -1) {
        int largest = parent;
        int LC = parent * 2 + 1;
        int RC = LC + 1;

        if (LC <= T->LastIndex && T->nodes[LC] > T->nodes[largest]) {
            largest = LC;
        }

        if (RC <= T->LastIndex && T->nodes[RC] > T->nodes[largest]) {
            largest = RC;
        }

        if (largest != parent) {
            int temp = T->nodes[largest];
            T->nodes[largest] = T->nodes[parent];
            T->nodes[parent] = temp;

            heapify(T, largest);
        }
    }
}

void maxHeap(Tree T) {
    if (T->LastIndex != -1) {
        for (int i = (T->LastIndex - 1) / 2; i >= 0; i--) {
            heapify(T, i);
        }
    } else {
        printf("\nHeap is EMPTY\n");
    }
}

int deleteMax(Tree T) {
    if (T->LastIndex != -1) {
        int max = T->nodes[0];
        T->nodes[0] = T->nodes[T->LastIndex--];
        heapify(T, 0); // Restore heap property
        return max;
    }
    printf("Heap is EMPTY\n");
    return -1;
}

void displayTree(Tree T) {
    if (T->LastIndex == -1) {
        printf("Heap is EMPTY\n");
    } else {
        printf("%-20s%-20s\n", "Index", "Priority");
        for (int i = 0; i <= T->LastIndex; i++) {
            printf("%-20d%-20d\n", i, T->nodes[i]);
        }
    }
    printf("\n");
}

void populate(int arr[], int size, Tree T) {
    for (int i = 0; i < size; i++) {
        T->nodes[i] = arr[i];
    }
    T->LastIndex = size - 1; // Set heap size
    maxHeap(T); // Ensure max-heap property
}
