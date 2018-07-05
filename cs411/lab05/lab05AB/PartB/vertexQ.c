/*
   vertexQ.c: functions for FIFO queue of vertexes 

   CS411 Lab #:5
   Name: Evan Conley
   Date: March 18, 2017
*/

#include "vertexQ.h"

int isEmpty(VertexQ *q) { return (q->head == q->tail); }

int isFull(VertexQ *q) { return (q->nElts == q->arraySize - 1); }

void initialize(VertexQ* q, int maxElts)             
{  
   q->arraySize = maxElts + 1; // n elts requires n+1 elt array 
   q->array = malloc(sizeof(Vertex*) * q->arraySize);
   q->head = 0; 
   q->tail = 0; 
   q->nElts = 0; 
}

int enqueue(VertexQ* q, Vertex *it)  
{  
   if (isFull(q)) return 1; // error  
   q->array[q->tail] = it;
   if (q->tail == q->arraySize - 1)
      q->tail = 0;
   else
      q->tail++;
   q->nElts++; // so we know when full
   return 0;
}

Vertex* dequeue(VertexQ* q)  
{  
   if (isEmpty(q)) return NULL; // error  
   Vertex* elt = q->array[q->head];
   if (q->head == q->arraySize - 1)
      q->head = 0;
   else
      q->head++;
   q->nElts--; // so we know when full
   return elt;
}

