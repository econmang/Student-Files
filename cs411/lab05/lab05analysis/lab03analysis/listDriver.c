/*
	listDriver.c: program to test counting sort efficiency on
		ItemList data structure
	
	CS411 Lab 3  Analysis Paper Program
	Name: Evan Conley
	Date: 2/7/2017
*/

#include "itemList.h"

/*
 * Varied maxID and then just did a loop to insert randomly created
 * items into the BST.
 *
 * As delete/clearItemList not implemented, I had to vary the maxID
 * and maxItems each run through as I couldn't iterate through a loop.
*/

int main(){
	//int maxID = 250;
	//int maxID = 500;
	int maxID = 1000;

	//int maxItems = 0; //Ranged from 0 to 5000000
	//int maxItems = 250000;
	//int maxItems = 500000;
	int maxItems = 750000;

	int i;
	ItemList theList;
	ItemList* items = &theList;
	initializeItemList(items);

	clock_t startIn = clock();
	for (i = 0; i < maxItems; i++){
		int rID = rand() % maxID;
		Item* it = createItem(rID, "potatoes", 5.50);
		insert(items, it);
	}
	clock_t endIn = clock();

	double timeIn = 1.0 * (endIn - startIn) / CLOCKS_PER_SEC;
	double time = 1000.0 * (timeIn);
	printf("With a max ID of %d and %d items, it took %lf milliseconds to insert.\n", maxID, maxItems, time);

	return 0;
}
