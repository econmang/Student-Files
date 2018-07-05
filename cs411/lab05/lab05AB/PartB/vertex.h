/*
   vertex.h: header file for airport graph vertex

   CS411 Lab #:5
   Name: Evan Conley
   Date: March 18, 2017
*/

#ifndef VERTEX_H
#define VERTEX_H

#include "airport.h"

typedef enum { WHITE, GRAY, BLACK } Color;

struct vertexLL;

typedef struct vertex {

   // the data
   Airport* airport;

   // adjacency list; a VertexLL that must be
   // dynamically allocated
   struct vertexLL* adjList;

   // BFS fields
   int d;
   struct vertex* parent;
   Color color;

} Vertex;

#endif