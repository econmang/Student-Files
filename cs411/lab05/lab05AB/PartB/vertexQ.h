/*
   vertexQ.h: header file for FIFO queue of vertices vertex structure 

   CS411 Lab #:5
   Name: Evan Conley
   Date: March 18, 2017
*/

#ifndef VERTEX_Q_H
#define VERTEX_Q_H

#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

typedef struct {
   int head; 
   int tail; 
   int nElts;
   int arraySize;
   Vertex** array;
} VertexQ;

/// VertexQ API function prototypes ///
int isEmpty(VertexQ *q);
int isFull(VertexQ *q);
void initialize(VertexQ* q, int maxElts);
int enqueue(VertexQ* q, Vertex *it);
Vertex* dequeue(VertexQ* q);

#endif
