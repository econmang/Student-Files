/*
   vertexLL.c: functions for the linked list of vertices

   CS411 Lab #:5
   Name: Evan Conley
   Date: March 18, 2017
*/

#include "vertexLL.h"

int isEmptyLL(const VertexLL* ll)
{
   return !(ll->head); // head is NULL when empty
}

void initializeLL(VertexLL* ll)             
{ ll->head = NULL; }


int insertLL(VertexLL* ll, Vertex *it)  
{  
   LLNode* node = malloc(sizeof(LLNode));
   if (!node)
   {
      printf("ERROR: unable to allocate memory for Vertex.\n");
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

void printLL(const VertexLL* ll)
{
   if (!isEmptyLL(ll))
   {
      const LLNode* node = ll->head;
      while (node)
      {
         printAirport(node->data->airport);
         node = node->next;
      }
   }
}