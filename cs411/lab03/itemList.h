/*
   itemList.h: header file for BST data structure 

   CS411 Lab #:3
   Name: Evan Conley
   Date: 2/17/2017
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

typedef struct node {
   Item* item;
   struct node* left;
   struct node* right;
   struct node* parent;
} Node;

typedef struct
{
   Node* root;

} ItemList;

/**Helper functions**/
void inOrder(Node* currNode, void(*theFunc)(Item*));

/** function prototypes **/

Item* createItem(int id, const char* name, float price);
void printItem(Item* item);
void saleItem(Item* item);
void destroyItem(Item** item);

void initializeItemList(ItemList* items);
void printItemList(ItemList* items); // const removed for Lab 2
void onSale(ItemList* items);
int insert(ItemList* items, Item* theItem);
Item* find(ItemList* items, int id);
void delete(ItemList* items, int id);
void clearItemList(ItemList* items);

/* new Lab 3 prototypes */
void visitItemList(ItemList* items, void (*visitFunc)(Item*));

#endif /* ITEM_LIST_H */
