#include <stdio.h>
#include <stdlib.h>

#define MAX 6
#define MAX_SIZE 20
#define infinity 999

typedef int Vertex;

typedef int LabelAdjMat[MAX][MAX];

typedef struct {
    int u, v; //representing edge(u,v);
    int weight;
} edgeType;

typedef struct {
    edgeType edges[MAX_SIZE];
    int lastNdx;
} minHeapOrList;

typedef struct {
    minHeapOrList eList;
    int cost;
} MST;

//for Adjancency Matrix
void displayAdjMatrix(LabelAdjMat M);

//for edge list and edges
minHeapOrList insertMinHeap(LabelAdjMat M);
edgeType createEdge(LabelAdjMat M, int i, int j);
void displayEdgeList(minHeapOrList List);

//for minHeap
void initMinHeap(minHeapOrList *L);
edgeType deleteMinHeap(minHeapOrList *L);

//Heapify functions
void heapifyTree(minHeapOrList *L);
void minHeapifySubTree(minHeapOrList *L, int parent);

//Prims and Kruskals algorithms
void printMST(MST *T);
MST Prims(minHeapOrList *L);
MST Kruskals(minHeapOrList *L);

int main() {
    LabelAdjMat M = {  infinity, 1, 5, 4, 6, 5, 1, infinity, 5, infinity, infinity, 6, 5, 5, infinity, 2, infinity, infinity, 4,
                             infinity, 2, infinity, 1, infinity, 6, infinity,infinity, 1, infinity, 3, 5, 6, infinity, infinity, 3, infinity} ;

    displayAdjMatrix(M);
    minHeapOrList L;
    initMinHeap(&L);
    L = insertMinHeap(M);  // Insert edges into the heap
    printf("\n");
    displayEdgeList(L);

    heapifyTree(&L);
    printf("\nHeapified Tree: ");
    displayEdgeList(L);

    printf("\nPrims Algorithm MST: ");
    MST T = Kruskals(&L);
    printMST(&T);
    printf("\n%d", T.eList.lastNdx);

    return 0;
}

//for Adjancency Matrix
void displayAdjMatrix(LabelAdjMat M){
    int i, j;
    
    printf("\nAdjacency Matrix:\n");
    printf("  ");
    for(i = 0; i < MAX; i++){
        printf(" %c ", i + 'A');
    }
    for(i = 0; i < MAX; i++){
        printf("\n");
        for(j = -1; j < MAX; j++){
          if(j == -1){
            printf("%c ", 'A' + i);
          } else {
         (M[i][j] == infinity) ? printf(" ~ ") : printf(" %d ", M[i][j]);
          }
        }
    }
}

//for minHeap
void initMinHeap(minHeapOrList *L){
  L->lastNdx = -1;
}

edgeType createEdge(LabelAdjMat M, int i, int j){
  edgeType Edge;
  Edge.u = i;
  Edge.v = j;
  Edge.weight = M[i][j];

  return Edge;
}

minHeapOrList insertMinHeap(LabelAdjMat M){
  minHeapOrList L;
  initMinHeap(&L);

  int i, j;

  for(i = 0; i < MAX; i++){
    for(j = i + 1; j < MAX; j++){
      if(M[i][j] != infinity){
        L.edges[++L.lastNdx] = createEdge(M, i, j);
      }
    }
  }

  return L;
}

edgeType deleteMinHeap(minHeapOrList *L){
  edgeType temp = {-1,-1,-1};

  if(L->lastNdx != -1){
    temp = L->edges[0];
    L->edges[0] = L->edges[L->lastNdx];
    L->edges[L->lastNdx--] = temp;
    
    minHeapifySubTree(L, 0);
  }

  return temp;
}

//Heapify functions
void minHeapifySubTree(minHeapOrList *L, int parent){
  if(L->lastNdx != -1){
    int min = parent;
    int LC = parent * 2 + 1;
    int RC = LC + 1;

    if(LC <= L->lastNdx && L->edges[LC].weight < L->edges[min].weight){
      min = LC;
    }

    if(RC <= L->lastNdx && L->edges[RC].weight < L->edges[min].weight){
      min = RC;
    }

    if(min != parent){
      edgeType temp = L->edges[parent];
      L->edges[parent] = L->edges[min];
      L->edges[min] = temp;

      minHeapifySubTree(L, min);
    }
  }
}

void heapifyTree(minHeapOrList *L){
  int i;
  for(i = L->lastNdx / 2; i >= 0; i--){
    minHeapifySubTree(L, i);
  }
}

void displayEdgeList(minHeapOrList List){
  if(List.lastNdx != -1){
    int i;
    printf("List of edges: ");
    for(i = 0; i <= List.lastNdx; i++){
      printf("{%d, %d} %d | ", List.edges[i].u, List.edges[i].v, List.edges[i].weight);
    }
  }
  printf("\n");
}

//Prims algorithm
MST Prims(minHeapOrList *L) {
    MST T;
    T.eList.lastNdx = -1; 
    T.cost = 0;           

    heapifyTree(L);     
    int visited[MAX] = {0};

  
    while (T.eList.lastNdx != 4 && L->lastNdx >= 0) {
        edgeType temp = deleteMinHeap(L);

        if ((visited[temp.v] && !visited[temp.u]) || (visited[temp.u] && !visited[temp.v]) || (!visited[temp.v] && !visited[temp.u])) {
            T.eList.edges[++T.eList.lastNdx] = temp; 
            T.cost += temp.weight;                   

            visited[temp.u] = 1;
            visited[temp.v] = 1;
        }
    }

    return T;
}

void printMST(MST *T) {
    if (T == NULL) {
        printf("Error: Null MST pointer.\n");
        return;
    }

    if (T->eList.lastNdx >= 0) { // Check if there are edges in the MST
        printf("\nMinimum Cost Spanning Tree:\n");
        
        for (int i = 0; i <= T->eList.lastNdx; i++) {
            printf("{%d, %d} %d | ", 
                   T->eList.edges[i].u, 
                   T->eList.edges[i].v, 
                   T->eList.edges[i].weight);
        }
        
        printf("\nTotal cost: %d\n", T->cost);
    } else {
        printf("The MST is empty. No edges to display.\n");
    }
}


MST Kruskals(minHeapOrList *L){
  Vertex treeGroup[MAX];

  int i ;
  for(i = 0; i < MAX; i++){
    treeGroup[i] = i;
  }

  MST T = {.cost = 0};
  T.eList.lastNdx = -1;

  heapifyTree(L);

  while(T.eList.lastNdx < MAX - 2){
    edgeType edge = deleteMinHeap(L);

    int u = edge.u;
    int v = edge.v;

    if(treeGroup[u] != treeGroup[v]){
      int change = u;
    }

    for(int i = 0; i < MAX; i++){
      if(treeGroup[i] == v){
        treeGroup[i] = u;
      }
    }

    T.cost += edge.weight;
    T.eList.edges[++T.eList.lastNdx] = edge;
  }

  return T;

}