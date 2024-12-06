/*
Parent Pointer Implementation of Trees

- Utilizes an array of nodes to represent the tree.
- The index of the array represents each node (similar to a bit-vector).
- The value at each index represents the parent of that node.
- root = -1 indicates the root node.
- ne = -2 indicates a nonexistent node.

*/

#include <stdio.h>
#include <stdlib.h>

#define ROOT -1
#define NE -2
#define MAX 10

typedef int tree[MAX];

tree* initializeTree();
void insert(int elem,int parent,tree* T); 
void display(tree T);
int parent(int n, tree T);
int leftmost_child(int n, tree T);
int right_sibling(int n, tree T);
int root(tree T);
void makenull(tree* T);

int main(){
    tree* T = initializeTree();
    insert(0, ROOT, T);
    insert(1, 0, T);
    insert(2, 0, T); 
    insert(3, 1, T); 
    insert(4, 1, T);
    insert(5, 2, T);
    insert(6, 2, T); 
    insert(7, 3, T); 

    printf("Tree structure:\n");
    display(*T);

    printf("\nParent of node 3: %d\n", parent(3, *T));
    printf("Leftmost child of node 1: %d\n", leftmost_child(1, *T));
    printf("Right sibling of node 3: %d\n", right_sibling(3, *T));
    printf("Root of the tree: %d\n", root(*T));

    makenull(T);
    free(T);

    return 0;
}

tree* initializeTree(){
    tree* newTree = (tree*) malloc (sizeof(tree));
    if (newTree != NULL){
        for (int i = 0; i < MAX; i++){
            (*newTree)[i] = NE;
        }
    }
    return newTree;
}

void insert(int elem, int parent, tree* T){
    if ((*T)[elem] == NE){
        (*T)[elem] = parent;
    } else {
        printf("The node %d already exists in the tree.", elem);
    }
}

void display(tree T){
    for (int i = 0; i < MAX; i++) {
        if (T[i] != NE) {
            if (T[i] == ROOT) {
                printf("Node %d is the root.\n", i);
            } else {
                printf("Node %d has parent %d.\n", i, T[i]);
            }
        }
    }
}

int parent(int n, tree T){
    return (T[n] != ROOT) ? T[n] : NE;
}



int leftmost_child(int n, tree T){
    int i;
    for(i = 0; i < MAX && T[i] != n; i++){}
    return (i < MAX) ? i : NE;
}

int right_sibling(int n, tree T){
    int i;
    for(i = n + 1; i < MAX && T[i] != T[n]; i++){}
    return (i < MAX) ? i : NE;
}

int root(tree T){
    int i;
    for(i = 0;i < MAX && T[i] != ROOT;i++){}
    return (i < MAX) ? i : NE;
}

void makenull (tree *T){
    for (int i = 0; i < MAX; i++){
            (*T)[i] = NE;
    }
}
