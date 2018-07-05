/*
   vertexLL.h: header file for linked list data structure 

   CS411 Lab #:5
   Name: Evan Conley
   Date: March 18, 2017
*/

#ifndef VERTEX_LL_H
#define VERTEX_LL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vertex.h"

typedef struct llnode {
   Vertex* data;
   struct llnode* prev;
   struct llnode* next;
} LLNode;

typedef struct vertexLL {
   LLNode* head; 
} VertexLL;

/** function prototypes **/
int isEmptyLL(const VertexLL* ll);
void initializeLL(VertexLL* ll);
int insertLL(VertexLL* ll, Vertex *it);
void printLL(const VertexLL* ll);

#endif /* ITEM_LL_H */