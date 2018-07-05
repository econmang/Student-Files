/*
   itemList.c: functions for the hash table of items

   CS411 Lab #:4
   Name: Evan Conley
   Date: March 6, 2017
*/

#include "itemList.h"

// create and return an Item with the indicated values
Item* createItem(int id, const char* name, float price)
{
   Item* newItem = malloc(sizeof(Item));
	if(!newItem){
		printf("ERROR: Unable to allocate memory for new Item.\n");
	}
	else{
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
void printItem(Item* item)
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
//   for a new hash table of size numSlots using chaining 
//   collision resolution.
// assumes the ItemList has never been previously used.
void initializeItemList(ItemList* items, int numSlots)
{
	int i;
	items->m = numSlots;
	items->hashTbl = malloc(sizeof(ItemLL) * items->m);
	for(i = 0; i < items->m; i++){
		initializeLL(&(items->hashTbl[i]));
	}
}

// output all items to stdout, one-per-line
// the output is unordered
void printItemList(ItemList* items)
{
	int i;
	for(i = 0; i < items->m; i++)
	{
		printLL(&(items->hashTbl[i]));
	}
}

// insert theItem into the ItemList, using chaining collision 
//    resolution.
// return 0 if successful, 1 if unsuccessful.
// note that duplicates are allowed
int insert(ItemList* items, Item* theItem)
{
	int cID = theItem->id; //take current ID
	int hID = cID % items->m; // hash function on ID
	int state = insertLL(&(items->hashTbl[hID]),theItem); //Insert into correct bucket
	return state; //state holds success or failure of insert and returns it
}

// find and return the first Item with the specified id in list items.
//   returns a pointer to the Item or NULL if the Item is not found.
Item* find(ItemList* items, int id)
{
	int hID = id % items->m;
	Item* fItem = searchLL(&(items->hashTbl[hID]),id);
	if(!fItem){
		return NULL;
	}
	else{
		return fItem;
	}
}

// remove the first Item with the specified id from list items
//   and deallocate the Item memory.
// if an Item with the specified id does not exist, do nothing.
// THIS FUNCTION NOT IMPLEMENTED FOR LAB 4
void delete(ItemList* items, int id)
{ printf("ERROR: DELETE not implemented.\n"); }

// remove and deallocate all Items in the ItemList
// THIS FUNCTION NOT IMPLEMENTED FOR LAB 4
void clearItemList(ItemList* items)
{ printf("ERROR: CLEARITEMLIST not implemented.\n"); }