/*
   itemLL.c: functions for the linked list of items

   CS411 Lab #:4
   Name: Kevin Sahr
   Date: February 27, 2017
*/

#include "itemLL.h"

int isEmptyLL(const ItemLL* ll)
{
   return !(ll->head); // head is NULL when empty
}

void initializeLL(ItemLL* ll)             
{  
   ll->head = NULL;
}

Item* searchLL(const ItemLL* ll, int id)
{  
   const LLNode* node = ll->head;
   while (node && node->data->id != id)
      node = node->next;

   if (node)
      return node->data;
   else
      return NULL;
}

int insertLL(ItemLL* ll, Item *it)  
{  
   LLNode* node = malloc(sizeof(LLNode));
   if (!node)
   {
      printf("ERROR: unable to allocate memory for Item.\n");
      return 1;
   }

   node->data = it;
   node->next = ll->head;
   if (ll->head)
      ll->head->prev = node;
   ll->head = node;
   node->prev = NULL;

   return 0;
}

void printLL(const ItemLL* ll)
{
   if (!isEmptyLL(ll))
   {
      const LLNode* node = ll->head;
      while (node)
      {
         printItem(node->data);
         node = node->next;
      }
   }
}
