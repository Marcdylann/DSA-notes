#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 5

void dfs(int graph[MAX_SIZE][MAX_SIZE], int node, bool visited[]);
void bfs(int graph[MAX_SIZE][MAX_SIZE], int start);
int *dijkstra(int graph[MAX_SIZE][MAX_SIZE], int start);
void displayShortestPaths(int *shortest_distances);

int main() {
    system("cls");

    int graph[MAX_SIZE][MAX_SIZE] = {
        {INT_MAX, 6, INT_MAX, 1, INT_MAX},
        {6, INT_MAX, 5, 2, 4},
        {INT_MAX, 5, INT_MAX, INT_MAX, 5},
        {1, 2, INT_MAX, INT_MAX, 1},
        {INT_MAX, 4, 5, 1, INT_MAX}
    };
    int *shortest_distances[MAX_SIZE];
    bool visited[MAX_SIZE] = {false};

    printf("DFS Traversal: ");
    dfs(graph, 0, visited);
    printf("\n");

    printf("BFS Traversal: ");
    bfs(graph, 0);
    printf("\n");

    printf("Dijkstra Shortest-Path:");
    shortest_distances[0] = dijkstra(graph, 0);
    displayShortestPaths(shortest_distances[0]);

    printf("\nFloyd-Warshall Shortest-Path: ");
    for(int x = 1; x < MAX_SIZE; x++) {
        shortest_distances[x] = dijkstra(graph, x);
        displayShortestPaths(shortest_distances[x]);
    }

    for(int x = 0; x < MAX_SIZE; x++) {
        free(shortest_distances[x]);
    }
    return 0;
}

// Function to perform Depth-First Search (DFS)
void dfs(int graph[MAX_SIZE][MAX_SIZE], int node, bool visited[]) {
  visited[node] = true;
  printf("%c ", node + 'A');

  int i;
  for(i = 0; i < MAX_SIZE; i++){
    if(graph[node][i] != INT_MAX && visited[i] != true){
      dfs(graph, i, visited);
    }
  }
}

// Function to perform Breadth-First Search (BFS) with minimum weight priority
void bfs(int graph[MAX_SIZE][MAX_SIZE], int start) {
    bool visited[MAX_SIZE] = {false};
    int queue[MAX_SIZE];
    int rear = 0;  // Points to the next position to insert
    int front = 0; // Points to the current position to dequeue

    visited[start] = true;
    queue[rear] = start;  // Enqueue the start node
    rear = (rear + 1) % MAX_SIZE;  // Update rear

    while (front != rear) {  // While the queue is not empty
        int node = queue[front];  // Dequeue the front node
        front = (front + 1) % MAX_SIZE;  // Update front pointer

        printf("%c ", 'A' + node);  // Process the current node

        for (int i = 0; i < MAX_SIZE; i++) {  // Visit all neighbors
            if (graph[node][i] && !visited[i]) {
                visited[i] = true;  // Mark the neighbor as visited
                queue[rear] = i;  // Enqueue the neighbor
                rear = (rear + 1) % MAX_SIZE;  // Update rear pointer

                // Check if the queue is full (optional safety check)
                if (rear == front) {
                    printf("\nError: Queue is full! Increase MAX_SIZE.\n");
                    return;
                }
            }
        }
    }
}


// Function to perform Dijkstra's algorithm on an adjacency matrix
int *dijkstra(int graph[MAX_SIZE][MAX_SIZE], int start) {

    int *sp = (int*) calloc(MAX_SIZE, sizeof(int));             //array to return
    bool visited[MAX_SIZE] = {false};                                           //initialize visited boolean array to unvisited

    for(int i = 0; i < MAX_SIZE; i++){
      sp[i] = INT_MAX;
    }

    sp[start] = 0;


    for(int i = 0; i < MAX_SIZE; i++){
      int min = INT_MAX, minIdx = -1;

      for(int j = 0; j < MAX_SIZE; j++){
        if(visited[j] == false && min > sp[j]){
          min = sp[j];
          minIdx = j;
        }
      }

      visited[minIdx] = true;

      for(int k = 0; k < MAX_SIZE; k++){
        if(!visited[k] && graph[minIdx][k] != INT_MAX && graph[minIdx][k] + sp[minIdx] < sp[k]){
          sp[k] = graph[minIdx][k] + sp[minIdx];
        }
      }
    }

    return sp;
}

// Function to display the shortest paths
void displayShortestPaths(int *shortest_distances) {
  printf("\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (shortest_distances[i] == INT_MAX) {
            printf("%c: INFINITY\n", 'A' + i);
        } else {
            printf("%c: %d\n", 'A' + i, shortest_distances[i]);
        }
    }
}