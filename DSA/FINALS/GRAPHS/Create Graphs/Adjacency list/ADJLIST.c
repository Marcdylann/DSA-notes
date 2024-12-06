#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX 6
#define SENTINEL 0XFFFF

typedef char vertexType;
typedef int labelType;

typedef struct {
  vertexType tail;
  vertexType head;
  int weight;
} edgeType;

typedef struct {
  vertexType adjVertex;
  int weight;
} adjType;

typedef struct adjNode{
  adjType info;
  struct adjNode *link;
} *AdjList;

typedef struct {
  AdjList head[MAX_VERTEX];
  int edgeCount;
} directedAdjList;

typedef struct {
  labelType matrix[MAX_VERTEX][MAX_VERTEX];
  int edgeCount;
} labeledAdjMatrix;

void initDirectedAdjList(directedAdjList *L);
directedAdjList populateDirectedAdjList();
void displayAdjList(directedAdjList L);

int main( ) {	
	system("cls");
 /*------------------------------------------------------------------------------------
 * 	Problem #1 ::  a) Creates a Labeled Adjacency List via populateDirectedAdjList()  *
 *                 b) Calls displayAdjList().                                         *
 *------------------------------------------------------------------------------------*/
  	printf("\n\n\nProblem #1:: "); 
   	printf("\n------------"); 
   
   	//Write the code for main here
	directedAdjList mDL = populateDirectedAdjList();
	displayAdjList (mDL);
	
 	return 0;
}

void initDirectedAdjList(directedAdjList *L){
  int x;
  for(x = 0; x < MAX_VERTEX; x++){
    L->head[x] = NULL;

  }
  L->edgeCount = 0;
}

directedAdjList populateDirectedAdjList() {											//insert the given arcs into the adjacency list
	directedAdjList DL;
	initDirectedAdjList (&DL);

	const int COUNT = 14;
    edgeType data[] =     {  {'A', 'E', 6}, {'C', 'A', 4}, { 'E', 'C' , 6 },
                             {'A', 'F', 3}, {'C', 'D', 6}, { 'E', 'F' , 6 },
                             {'B', 'A', 4}, {'D', 'A', 8}, { 'F', 'B' , 3 },
                             {'B', 'C', 3}, {'D', 'B', 6}, { 'D', 'E' , 3 }, 
							 {'B', 'E', 6}, {'F', 'D' ,3 },{ 'B', 'F' , 10 }, 
						};

  //write code here
  AdjList *trav, temp;

  int x;
  for(x = 0; x <= 14; x++){
    for(trav = &(DL.head[data[x].tail - 'A']); (*trav) != NULL && (*trav)->info.adjVertex <= data[x].head; trav = &(*trav)->link){}
    if((*trav) != NULL && (*trav)->info.adjVertex == data[x].head){
      (*trav)->info.weight = ((*trav)->info.weight < data[x].weight) ? (*trav)->info.weight : data[x].weight;
    } else {
      temp = malloc(sizeof(struct adjNode));

      if(temp != NULL){
        temp->info.adjVertex = data[x].head;
        temp->info.weight = data[x].weight;
        temp->link = *trav;

        *trav = temp;
        
      }

      DL.edgeCount++;
    }
  }

  
  

  return DL;

}

void displayAdjList(directedAdjList L) {
 	int x;
	AdjList temp;
		
	printf("\n\nTHE ADJACENCY LIST ::");
	printf("\n%-8s", "VERTEX");
	printf("%-20s", "Adjacent vertices");
	printf("\n%-8s", "------");
	printf("%-19s", "-----------------");
   printf("\n");
	//Write your code here 
  for(x = 0 ; x < MAX_VERTEX ; x++){
  printf("%c :: ", 'A' + x);
  for(temp = L.head[x]; temp != NULL; temp = temp->link){
    printf("%c (%d) ", temp->info.adjVertex, temp->info.weight);
  }
  printf("\n");
  }

  printf("Number of edges: %d", L.edgeCount);
	
}