#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOSE_DSIZE 0XF    //size of Close Hash Table
#define SET_SIZE   0XC    //size of the array implementation of Set
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  
	char name[24];          // Chocolate name  
 	int  weight;            // Chocolate weight in grams  
}chocoDesc;
 
typedef struct {
   char prodID[8];          //  product ID uniquely identifies the products; EMPTY or DELETED   
  	chocoDesc prodDesc;      //  product description 
 	float prodPrice;         //  product price 
  	int prodQty;             //  product count or quantity   
}product;                   //  product record  

typedef struct pSet {
	product prod[SET_SIZE];
	int last;          //index of the last element; -1 if list is empty	
}ProdSet;

/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY   "empty"         // stored in product ID field  
#define DELETED  "deleted"      // stored in product ID field * 
 
typedef product closeDic[CLOSE_DSIZE];   //Definition of the closed hash dictionary
  
/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
ProdSet populateProdSet();

int closeHash(char *ID);     
void initCloseDict(closeDic CD);
closeDic * createCloseDict(ProdSet S);	
void displayCloseDict(closeDic CD);

/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *   4)  Uncomment or copy the print statement in each PROBLEM#  if the task is     *
 *       completed.                                                                 *
 ***********************************************************************************/
 int main( ) 
 {	
 /*------------------------------------------------------------------------------------
 * 	Problem #2  :: 1) Populate the set by calling populateProdSet                  *
 *                   2) Calls createCloseDict()                                     *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #2 :: ");
   printf("\n------------");
    
   ProdSet S = populateProdSet();
    closeDic *D = createCloseDict(S);
    displayCloseDict(*D);

    // Free dynamically allocated memory
    free(D);

	return 0;
}

/************************************************************
 *  Problem  :: Function Definitions                          *
 ************************************************************/
ProdSet populateProdSet()
{ 
 	product data[] = { 	{"1701", {"Toblerone", 135}, 150.75, 20}, {"1356", {"Ferrero", 200}, 250.75, 85},
						{"1109", {"Patchi", 50}, 99.75, 35}, {"1550", {"Cadbury", 120}, 200.00, 30},
						{"1807", {"Mars", 100}, 150.75, 20}, {"1201", {"Kitkat", 50}, 97.75, 40},
						{"1450", {"Ferrero", 100},150.50, 50}, {"1601", {"Meiji", 75}, 75.50, 60},
						{"1310", {"Nestle", 100}, 124.50, 70}, {"1455", {"Tango", 75}, 49.50, 100},
						{"1703", {"Toblerone", 100}, 125.75, 60}, {"1284", {"Lindt", 100}, 250.75, 15},
						{"1688", {"Guylian", 50}, 99.75, 35}, {"1107", {"Valor", 120}, 149.50, 90}
					     };
   int count = sizeof(data)/sizeof(data[0]);
   
   ProdSet Set = {.last = SET_SIZE - 1};
	memcpy(Set.prod, data, sizeof(data[0]) * SET_SIZE);
 	
   return Set;  
}
 
int closeHash(char *ID)
{
    int sum = 0;
    int i;
    for(i = 0; ID[i] != '\0'; i++){
      sum += ID[i];
    }

    return sum % CLOSE_DSIZE;
} 
 
void initCloseDict(closeDic CD)
{
    int i;
    for(i = 0; i < CLOSE_DSIZE; i++){
      strcpy(CD[i].prodID, EMPTY);
    }
}


closeDic * createCloseDict(ProdSet L)
{
	// Uncomment these lines and put before a call to displayCloseDict()
      //  printf("\n\n----- Empty Dictionary ------");
      //  printf("\n\n----- Dictionary without the Synonyms ------");
 	   // printf("\n\n----- Dictionary with ALL the Synonyms -----");
 		 
	//Write your code here 
		closeDic *DC = (closeDic *) malloc(sizeof(closeDic));
    initCloseDict(*DC);

    int i;
    for(i = 0; i < L.last; i++){
      int index = closeHash(L.prod[i].prodID);
      while(strcmp((*DC)->prodID, EMPTY) != 0 && strcmp((*DC)->prodID, DELETED) != 0){
        index = (index + 1) % CLOSE_DSIZE;
      }

      (*DC)[index] = L.prod[i];
    }
	 
    return DC;
}	

void displayCloseDict(closeDic CD)
{
	printf("\n\n%-6s", "Index");
	printf("%-10s", "ChocoID");
	printf("%-15s", "Choco Name");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------"); 
	
	 for (int i = 0; i < CLOSE_DSIZE; i++) {
        if (strcmp(CD[i].prodID, EMPTY) != 0 && strcmp(CD[i].prodID, DELETED) != 0) {
            printf("\n%-6d%-10s%-15s", i, CD[i].prodID, CD[i].prodDesc.name);
        } else {
            printf("\n%-6d%-10s%-15s", i, CD[i].prodID, "-");
        }
    }
	 
	printf("\n\n"); system("Pause");  //keep this statement
 
}
 