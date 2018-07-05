/*
   item.h: header file for the Item

   CS411 Lab #:4
   Name: Kevin Sahr     
   Date: February 21, 2017
*/

#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM_NAME_LEN   30

typedef struct
{
   int id;
   char name[MAX_ITEM_NAME_LEN + 1];
   float price;
} Item;

/*** Item function prototypes ***/
Item* createItem(int id, const char* name, float price);
void printItem(Item* item);
void destroyItem(Item** item);

#endif /* ITEM_H */
