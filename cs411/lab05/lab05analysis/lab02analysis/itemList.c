/*
   itemList.c: functions for the list of items

   CS411 Lab #:2
   Name: Evan Conley
   Date: 1/30/2017
*/

#include "itemList.h"

// create and return an Item with the indicated values
Item* createItem(int id, const char* name, float price) {
	Item* newItem = malloc(sizeof(Item));
	if (!newItem)
	{
		printf("ERROR: Unable to allocate memory for Item.\n");
	}
	else
	{
		if(strlen(name) > MAX_ITEM_NAME_LEN){
			printf("ERROR: Item name cannot exceed %d characters.\n", MAX_ITEM_NAME_LEN);
			destroyItem(&newItem);
		}
		else if(id < 0 || id > MAX_ITEM_ID){
			printf("ERROR: Item ID cannot be greater than %d.\n", MAX_ITEM_ID);
			destroyItem(&newItem);
		}
		else{
			newItem->id = id;
			strcpy(newItem->name,name);
			newItem->price = price;
		}
	}
	
	return newItem;
}

// output the item to stdout
void printItem(const Item* item)
{
	printf("ID: %d, Name: %s, Price: %.2f\n", item->id,item->name,item->price);
}

// deallocate the Item indicated by the handle argument
void destroyItem(Item** item)
{
	free(*item);
	*item = NULL;
}

// sets values in the ItemList to appropriate values
//   for a new empty item list.
// assumes the ItemList has never been previously used.
void initializeItemList(ItemList* items)
{
	items->numItems = 0;

	items->theItems = malloc(sizeof(Item) * MAX_ITEMS);
	/*int i;
	for(i = 0; i < MAX_ITEMS; i++)
	{
		items->theItems[i] = NULL;
	}*/
}


// CSort is a helper function of printItemList to
// sort all input in ItemList in a new array using Counting Sort
ItemList* CSort(ItemList* items,ItemList* sItems, int n, int bigID){
	int count[bigID+1]; //Count array up to biggest ID
	int i,j;

	//initialize array with all 0's
	for (i=0; i<=bigID; i++)
		count[i] = 0;
	for (i = 0; i <=bigID; i++){
	}
    //increment each elt as the value associated with it is found
    for (j = 0; j < n; j++){
    	count[items->theItems[j]->id]=count[items->theItems[j]->id] + 1;
    }
    //find number of values less than each elt
    for (i = 1; i <= bigID; i++){
    	count[i] = count[i] + count[i-1];
    }

    for (j = n-1; j >= 0; j--){
    	sItems->theItems[count[items->theItems[j]->id]-1] = items->theItems[j];
    	count[items->theItems[j]->id] = count[items->theItems[j]->id] - 1;
    }
    for (i = 0; i < items->numItems; i++){
    	items->theItems[i] = sItems->theItems[i];
    }
    return items;
}

// sort the Items using a Counting Sort, and then output all items 
// in the list to stdout, one-per-line, in order
void printItemList(ItemList* items)
{
	int i;
	int maxID = 0;

	ItemList sI;
	ItemList* sItems = &sI;
	initializeItemList(sItems);
	sItems->numItems = items->numItems;

	//Gets maxID for Counting Sort parameter
	for(i = 0; i < items->numItems; i++){
		if(items->theItems[i]->id > maxID){
			maxID = items->theItems[i]->id;
		}
	}
	CSort(items, sItems, items->numItems,maxID);

	printf("THE CURRENT ITEM LIST:\n\n");
	for(i = 0; i < sItems->numItems; i++){
		printItem(items->theItems[i]);
	}

}

// insert theItem into the ItemList.
// return 0 if successful, 1 if unsuccessful.
// note that the ItemList is unordered and duplicates
//   are allowed
int insert(ItemList* items, Item* theItem)
{
	if (items->numItems == MAX_ITEMS){
		printf("ERROR: Cannot add another item. Item List is full.\n");
		return 1;
	}
	else{
		items->theItems[items->numItems] = theItem;
		items->numItems++;
	}
	return 0;
}

// find and return the first Item with the specified id in list items.
//   returns a pointer to the Item or NULL if the Item is not found.
// must use a linear search
Item* find(ItemList* items, int id)
{
	int i;
	for(i = 0; i < items->numItems; i++){
		if(id == items->theItems[i]->id)
			return items->theItems[i];
	}
	return NULL;
}

// remove the first Item with the specified id from list items
//   and deallocate the Item memory.
// if an Item with the specified id does not exist, do nothing.
void delete(ItemList* items, int id)
{
	int found = 0;
	int i;
	for (i = 0; i < items->numItems; i++)
	{
		if(items->theItems[i]->id == id)
		{
			found = 1;
			break;
		}
	}

	if (found)
	{
		destroyItem(&(items->theItems[i]));

		for(; i < items->numItems-1; i++)
			items->theItems[i] = items->theItems[i+1];
		items->numItems--;
	}
	else
		printf("ERROR: Item with ID: %d does not exist.", id);
}

// remove and deallocate all Items in the ItemList
void clearItemList(ItemList* items)
{
	int i;
	for(i = 0; i < items->numItems; i++)
	{
		destroyItem(&(items->theItems[i]));
	}
	items->numItems = 0;
}
