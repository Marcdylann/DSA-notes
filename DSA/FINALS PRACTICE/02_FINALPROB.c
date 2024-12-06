//! Author: 		Fabiola C. Villanueva
//! Description:	
//! Date: 			

/************************************************************************
 * Prim's Algorithm : It grows a spanning tree, one edge at a time.     *
 * Given:                                                               *
 *   1)  Graph G = (V, E)                                               *
 *   2)  V = {0, 1, 2, 3, 4}                                            *
 *                                                                      *
 * Steps of Prim�s Algorithm:                                           *
 *   1) Initialize set U to contain { 0 }                               *
 *      //In the program, starting vertex will be inputted by the user  *
 *   2) While (U != V)                                                  *
 *       a) Find the minimum cost edge (u, v) such that                 *
 *          u is an element  U and   v is not yet in U                  *
 *       b)  Add v to U                                                 *
 ************************************************************************/
 
#include <unistd.h>    // for sleep(), to add in code if display leaves blank screen  
#include <stdio.h> 
#include <string.h>   

                 
#define MAX  6              // Number of vertices in the graph  
#define INFINITY  0XFFFF    
   
/***** Data Structure Definition *****/  
typedef int graphType[MAX][MAX];    // A[x][y] = INFINITY  if there is not edge ;  A[x][y] = weight of the edge (x,y)
typedef int set[MAX];               // Bit-vector implementation of Set

typedef struct {
	int u, v;     // (u,v) represents the edge  
	int weight;   // weight of the edge
}edgetype;

typedef struct {
    edgetype edges[MAX];
    int edgeCount;   //actual number of edges
	int minCost;	 //Cost of the MST
}primMST;

/***** Function Prototypes *****/

void populateGraph(graphType G);
primMST primAlgo(graphType graph, int startVertex);
void displayPrimMST(primMST tree);

int main() { 
     /*---------------------------------------------------------------------------------
    * 	Problem #2 ::  a) Allows user to input from keyboard the starting vertex      *
    *                  b) Calls populateGraph() to populate the given graph           *
    *                  c) Calls primAlgo() and displayPrimMST()                       *
    *                                                                                 *
    * printf("\n\n\nProblem #2:: ");                                                  *  
    * printf("\n------------");                                                       *
    *---------------------------------------------------------------------------------*/
 	printf("\n\n\nProblem #2:: "); 
    printf("\n------------"); 
    
    //Write code here
    graphType G;
    primMST MST;
    populateGraph(G);

    int startV;
    printf("Enter starting vertex: ");
    scanf("%d", &startV);

    MST = primAlgo(G, startV);

    displayPrimMST(MST);

    return 0; 
} 

/************************************************************
 * Function Definitions                                     *
 ************************************************************/
void populateGraph(graphType G) {
	graphType graph = {  INFINITY, 1, 5, 4, 6, 5, 1, INFINITY, 5, INFINITY, INFINITY, 6, 5, 5, INFINITY, 2, INFINITY, INFINITY, 4,
                             INFINITY, 2, INFINITY, 1, INFINITY, 6, INFINITY,INFINITY, 1, INFINITY, 3, 5, 6, INFINITY, INFINITY, 3, INFINITY} ;   //5

	memcpy(G, graph, sizeof(graph));
}

 

primMST primAlgo(graphType graph, int startVertex) {
	 set visited = {0};
   primMST MST = {.edgeCount = 0, .minCost = 0};

   visited[startVertex] = 1;

   int i, j;

   while(MST.edgeCount < MAX - 1){
    edgetype minEdge = {.weight = INFINITY};
    int minIdx = -1;

    for(i = 0; i < MAX; i++){
      if(visited[i]){
        for(j = 0; j < MAX; j++){
          if(!visited[j] && graph[i][j] < minEdge.weight){
            minEdge.u = i;
            minEdge.v = j;
            minEdge.weight = graph[i][j];

            minIdx = j;
          }
        }
      }
    }

    visited[minIdx] = 1;
    MST.edges[MST.edgeCount++] = minEdge;
    MST.minCost += minEdge.weight;
   }

   return MST;
}

void displayPrimMST(primMST T) {
	int x;
		
	printf("\n%5s%5s", "Edge", "Cost");
 
   for(x = 0; x < MAX - 1; x++){
    printf("\n");
    printf("{%d, %d} %d | ", T.edges[x].u, T.edges[x].v, T.edges[x].weight);
   }
	
  printf("\nTotal cost %d", T.minCost);
}