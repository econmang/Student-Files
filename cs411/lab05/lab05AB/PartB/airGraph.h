/*
   airGraph.h: header file for graph of airport connections

   CS411 Lab #:5
   Name: Evan Conley    
   Date: March 18, 2017
*/

#ifndef AIR_GRAPH_H
#define AIR_GRAPH_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vertex.h"

typedef struct
{
   // array of vertices
   //note that each vertex contains its own adjacency list
   Vertex* vertList;
   int numVerts;

} AirGraph;

/** AirGraph API function prototypes **/

void initializeAirGraph(AirGraph* graph, int numAP);
void insertAirport(AirGraph* graph, Airport* theAP);
int insertRoute(AirGraph* graph, int startAP, int destAP);
void BFS(AirGraph* graph, int startAP);
int printRoute(AirGraph* graph, int startAP, int destAP);

#endif /* AIR_GRAPH_H */