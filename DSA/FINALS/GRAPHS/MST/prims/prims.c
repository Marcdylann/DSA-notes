#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define INF 99999

typedef int Graph[MAX][MAX];

typedef int Set[MAX];

void init(Graph G);
void addEdge(Graph G, int src, int dest, int weight);
bool edgeExists(Graph G, int src, int dest);
void display(Graph G);
void prims(Graph G, Graph MST);

int main(void) {
  Graph G, MST;
  init(G);
  init(MST);
  addEdge(G, 0, 1, 4);
  addEdge(G, 1, 2, 3);
  addEdge(G, 2, 3, 5);
  addEdge(G, 1, 4, 2);
  addEdge(G, 4, 3, 7);
  display(G);
  prims(G, MST);
  display(MST);
}

bool isFull(Set S) {
  bool isFull = 1;
  for (int i = 0; i < MAX && isFull; i++) {
    if (S[i] == 0) {
      isFull = 0;
    }
  }
  return isFull;
}

void prims(Graph G, Graph MST) {
  int numEdges = 0;
  Set visited = {0};
  visited[0] = 1;

  int x, y;
  while(numEdges < MAX-1){
    int min = INF;
    x=0; y = 0;

    for(int i = 0; i < MAX; i++){
      if(visited[i]){
        for(int j = 0; j < MAX; j++){
          if(!visited[j] && G[i][j]){
            if(min > G[i][j]){
              min = G[i][j];
              x = i; 
              y = j;
            }
          }
        }
      }
    }

    MST[x][y] = min;
    numEdges++;
    visited[y] = true;
  }
}

void init(Graph G) {
  for (int row = 0; row < MAX; row++) {
    for (int col = 0; col < MAX; col++) {
      if(row != col){
         G[row][col] = INF;
      } else {
         G[row][col] = 0;
      }
    }
  }
}

void addEdge(Graph G, int src, int dest, int weight) { G[src][dest] = weight; }

bool edgeExists(Graph G, int src, int dest) {
  return G[src][dest] == 1 ? true : false;
}

void display(Graph G) {
  printf("    ");
  for (int row = 0; row < MAX; row++) {
    printf("%d ", row);
  }
  puts("");
  for (int row = 0; row < MAX; row++) {
    printf("%d [ ", row);
    for (int col = 0; col < MAX; col++) {
      if( G[row][col] == INF){
        printf("~ ");
      } else {
        printf("%d ", G[row][col]);
      }
    }
    printf("]\n");
  }
  puts("");
}