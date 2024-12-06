#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {
	char name[24];          // Chocolate name  
	int weight;             // Chocolate weight in grams  
} chocoDesc;

typedef struct {
	char prodID[8];         // Product ID uniquely identifies the products
	chocoDesc prodDesc;     // Product description
	float prodPrice;        // Product price
	int prodQty;            // Product count or quantity
} product;                  // Product record

typedef struct pnode {
	product prod;
	struct pnode *plink;
} *ProdList;               // Linked List implementation

/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
ProdList populateProdList();
void displayProdList(ProdList L);
void makeListToSet(ProdList L);

/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   Follow the instructions in each PROBLEM section to complete the tasks.         *
 ***********************************************************************************/

int main() {
	/*----------------------------------------------------------------------------------
	 * Problem #1 :: 1) Populate the list by calling populateProdList()
	 *               2) Display the product list
	 *               3) Call makeListToSet(), then displayProdList().
	 *---------------------------------------------------------------------------------*/
	printf("\n\n\nProblem #1:: ");
	printf("\n------------");

	ProdList L = populateProdList();
	displayProdList(L);
	makeListToSet(L);
	displayProdList(L);

	return 0;
}

/************************************************************
 *  Problem1   :: Function Definitions                      *
 ************************************************************/

ProdList populateProdList() {
	int count;
	product data[] = {
		{"1701", {"Toblerone", 135}, 150.75, 20}, {"1356", {"Ferrero", 200}, 250.75, 85},
		{"1109", {"Patchi", 50}, 99.75, 35}, {"1550", {"Cadbury", 120}, 200.00, 30},
		{"1807", {"Mars", 100}, 150.75, 20}, {"1201", {"Kitkat", 50}, 97.75, 40},
		{"1201", {"Ferrero", 100}, 150.50, 50}, {"1701", {"Toblerone", 50}, 90.75, 80},
		{"1701", {"Meiji", 75}, 75.50, 60}, {"1310", {"Nestle", 100}, 124.50, 70},
		{"1807", {"Valor", 120}, 149.50, 90}, {"1455", {"Tango", 75}, 49.50, 100},
		{"1703", {"Toblerone", 100}, 125.75, 60}, {"1688", {"Lindt", 100}, 250.75, 15},
		{"1688", {"Guylian", 50}, 99.75, 35}
	};
	count = sizeof(data) / sizeof(data[0]);

	ProdList head = NULL, temp, prev = NULL;

  for(int x = 0; x < count; x++){
    temp = malloc(sizeof(struct pnode));
    temp->prod = data[x];
    temp->plink = NULL;

    if(head == NULL){
      head = temp;
    } else {
      prev->plink = temp;
    }
    prev = temp;
  }

	return head;
}

void displayProdList(ProdList L) {
	printf("\n\nDetails of the List :: ");
	printf("\n---------------------");
	printf("\n\n%-7s%-12s%-15s%-10s%-10s", "ID", "Choco Name", "Choco Weight", "Price", "Qty");
	printf("\n%-7s%-12s%-15s%-10s%-10s", "--", "----------", "------------", "-----", "---");

	int count = 0;
	while (L != NULL) {
		printf("\n%-7s%-12s%-15d%-10.2f%-10d", L->prod.prodID, L->prod.prodDesc.name,
			L->prod.prodDesc.weight, L->prod.prodPrice, L->prod.prodQty);
		L = L->plink;
		count++;
	}

	printf("\n\nNo. of elements :: %d", count);
	printf("\n\n");
	system("Pause");
}

void makeListToSet(ProdList L) {
	ProdList compare = L, Trav, prev;

  while(compare != NULL){
    Trav = compare->plink;
    prev = compare;

    while(Trav != NULL){
      if(strcmp(compare->prod.prodID, Trav->prod.prodID) == 0){
        prev->plink = Trav->plink;
        free(Trav);
        Trav = prev->plink;
      } else {
        prev = Trav;
        Trav = Trav->plink;
      }
    }
    compare = compare->plink;
  }
}
