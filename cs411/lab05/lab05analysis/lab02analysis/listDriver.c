/*
	listDriver.c: program to test counting sort efficiency on
		ItemList data structure
	
	CS411 Lab 2 Analysis Paper Program
	Name: Evan Conley
	Date: 2/7/2017
*/

#include "itemList.h"

/*
	Defined constants from itemList.h to accomodate for varying listItems sizes
	Also I changed initializeItemList so it would dynamically allocate.
	This allows me to do list sizes over the size of when I statically allocated.
	
	Varied maxID in this progrma to test efficiency based upon varied maxID sizes.
*/

int main(){
	int maxID = 1000; //250,500,1000
	int maxItems;
	int i;

	ItemList theList;
	ItemList* items = &theList;
	initializeItemList(items);

	ItemList sI;
	ItemList* sItems = &sI;


	maxItems = 0;
	clearItemList(sItems);
	while (maxItems <= MAX_ITEMS){
		clock_t startIn = clock();
		for (i = 0; i < maxItems; i++){
			int rID = rand() % maxID;
			Item* it = createItem(rID, "potatoes", 5.50);
			insert(items, it);
		}
		clock_t endIn = clock();

		initializeItemList(sItems);
		sItems->numItems = items->numItems;

		clock_t startSort = clock();
		CSort(items, sItems, maxItems,maxID);
		clock_t endSort = clock();

		double timeIn = 1.0 * (endIn - startIn) / CLOCKS_PER_SEC;
		double timeSort = 1.0 * (endSort - startSort) / CLOCKS_PER_SEC;
		double time = 1000.0 * (timeIn + timeSort);
		printf("With a max ID of %d and %d items, it took %lf milliseconds to insert and sort.\n", maxID, maxItems, time);

		maxItems = maxItems + 250000;
		clearItemList(items);
	}
	
	printf("\n\n");
	return 0;
}
