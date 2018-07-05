/*
   itemList.c: functions for the list of items

   CS411 Lab #:3
   Name: Evan Conley
   Date: 2/17/2017
*/

#include "itemList.h"


// HELPER FUNCTIONS:

// I didn't know how to do inorder traversal given just the itemList
// so I created this to traverse via the nodes.
void inOrder(Node* currNode, void (*theFunc)(Item*))
{
	if (currNode != NULL){
		inOrder(currNode->left,theFunc);
    	(*theFunc)(currNode->item);
    	inOrder(currNode->right,theFunc);
    }
}

// END OF HELPER FUNCTIONS SECTION

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

// Puts an item on sale
void saleItem(Item* item){
	item->price = item->price - (item->price * 0.10);
}

// deallocate the Item indicated by the handle argument
void destroyItem(Item** item)
{
	free(*item);
	*item = NULL;
}

// sets values in the ItemList to appropriate values
//   for a new BST.
// assumes the ItemList has never been previously used.
void initializeItemList(ItemList* items)
{
	items->root = NULL;
}

// output all items to stdout, one-per-line, in order
// must use visitItemList
void printItemList(ItemList* items)
{
	visitItemList(items,printItem);
}

// puts all items in list on sale
void onSale(ItemList* items)
{
	visitItemList(items,saleItem);
}

// insert theItem into the ItemList.
// return 0 if successful, 1 if unsuccessful.
// note that duplicates are allowed
int insert(ItemList* items, Item* theItem)
{
	Node* node = malloc(sizeof(Node));
	node->item = theItem;
	node->left = NULL;
	node->right = NULL;

	Node* yNode = NULL;
	Node* xNode = items->root;

	while(xNode != NULL)
	{
		yNode = xNode;
		if (node->item->id < xNode->item->id)
			xNode = xNode->left;
		else
			xNode = xNode->right;
	}

	node->parent = yNode;
	if (yNode == NULL){
		items->root = node;
	}
	else if(node->item->id < yNode->item->id)
		yNode->left = node;
	else
		yNode->right = node;
	return 0;
}

// find and return the first Item with the specified id in list items.
//   returns a pointer to the Item or NULL if the Item is not found.
Item* find(ItemList* items, int id)
{
	Node* check = malloc(sizeof(Node));
	check = items->root;
	while(check && check->item->id != id){
		if(check->item->id < id)
			check = check->right;
		else if(check->item->id > id){
			check = check->left;
		}
	}

	if (check)
		return check->item;
	else
		return NULL;
}

// apply the function visitFunc to all of the Items in the ItemList
// must use an inorder traversal
void visitItemList(ItemList* items, void (*visitFunc)(Item*))
{
	inOrder(items->root,visitFunc);
}

// remove the first Item with the specified id from list items
//   and deallocate the Item memory.
// if an Item with the specified id does not exist, do nothing.
// THIS FUNCTION NOT IMPLEMENTED FOR LAB 3
void delete(ItemList* items, int id){
	printf("ERROR: DELETE not implemented.\n");
}

// remove and deallocate all Items in the ItemList
// THIS FUNCTION NOT IMPLEMENTED FOR LAB 3
void clearItemList(ItemList* items){
	printf("ERROR: CLEARITEMLIST not implemented.\n");
}