/*
   itemList.h: header file for list of items data structure 

   CS411 Lab #:2
   Name: Evan Conley
   Date: 1/30/2017
*/

#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS         1000
#define MAX_ITEM_NAME_LEN   30
#define MAX_ITEM_ID        500

typedef struct
{
   int id;
   char name[MAX_ITEM_NAME_LEN + 1];
   float price;
} Item;

typedef struct
{
   int numItems;   // the current number of items in the list
   Item* theItems[MAX_ITEMS];

} ItemList;

/** function prototypes **/

Item* createItem(int id, const char* name, float price);
void printItem(const Item* item);
void destroyItem(Item** item);

void initializeItemList(ItemList* items);
void printItemList(ItemList* items); // const removed for Lab 2
int insert(ItemList* items, Item* theItem);
Item* find(ItemList* items, int id);
void delete(ItemList* items, int id);

/* new Lab 2 prototypes */

void clearItemList(ItemList* items);

#endif /* ITEM_LIST_H */