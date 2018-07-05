/*
   itemLL.h: header file for linked list data structure 

   CS411 Lab #:4
   Name: Kevin Sahr     
   Date: February 27, 2017
*/

#ifndef ITEM_LL_H
#define ITEM_LL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "item.h"

typedef struct llnode {
   Item* data;
   struct llnode* prev;
   struct llnode* next;
} LLNode;

typedef struct {
   LLNode* head; 
} ItemLL;

/** function prototypes **/
int isEmptyLL(const ItemLL* ll);
void initializeLL(ItemLL* ll);
Item* searchLL(const ItemLL* ll, int id);
int insertLL(ItemLL* ll, Item *it);
void printLL(const ItemLL* ll);

#endif /* ITEM_LL_H */
