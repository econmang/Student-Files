/*
   itemList.h: header file for BST data structure 

   CS411 Lab #:4
   Name: Kevin Sahr     
   Date: February 21, 2017
*/

#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "item.h"
#include "itemLL.h"

#define MAX_ITEM_ID 500

typedef struct
{
   // an array of Linked-Lists
   // this must be dynamically allocated
   ItemLL* hashTbl;
   int m;

} ItemList;

/** function prototypes **/
/* Item prototypes have moved to Item.h */

void initializeItemList(ItemList* items, int numSlots);
void printItemList(ItemList* items); 
int insert(ItemList* items, Item* theItem);
Item* find(ItemList* items, int id);
void delete(ItemList* items, int id); // these are stubs
void clearItemList(ItemList* items);  // these are stubs

#endif /* ITEM_LIST_H */
