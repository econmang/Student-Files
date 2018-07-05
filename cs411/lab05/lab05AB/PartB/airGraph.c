/*
   airGraph.c: functions for the airport connection graph

   CS411 Lab #:5
   Name: Evan Conley
   Date: March 18, 2017
*/

#include "airGraph.h"
#include "vertexLL.h"
#include "vertexQ.h"
#include <limits.h>

// create and return an Airport with the indicated values
Airport* createAirport(int number, const char* code, const char* city,
            const char* state, const char* country)
{
	Airport* newAir = malloc(sizeof(Airport));
	if(!newAir){
		printf("ERROR: Unable to allocate memory for new Airport.\n");
	}
	else{
		if(strlen(code) > AIRPORT_CODE_LEN){
			printf("Error: Code may not exceed %d characters.\n",AIRPORT_CODE_LEN);
		}
		else if(strlen(city) > MAX_AIRPORT_STR_LEN){
			printf("Error: City name may not exceed %d characters.\n",MAX_AIRPORT_STR_LEN);
		}
		else if(strlen(state) > STATE_LEN){
			printf("Error: State Code may not exceed %d characters.\n",STATE_LEN);
		}
		else if(strlen(country) > MAX_AIRPORT_STR_LEN){
			printf("Error: Country name may not exceed %d characters.\n",MAX_AIRPORT_STR_LEN);
		}
		else{
			newAir->number = number;
			strcpy(newAir->code,code);
   			strcpy(newAir->city,city);
   			strcpy(newAir->state,state);
   			strcpy(newAir->country,country);
		}
	}
	return newAir;
}

// output all fields of the airport to stdout
void printAirport(const Airport* airport)
{
   printf("Number: %d, Code: %s, City: %s, State: %s, Country: %s\n", airport->number,airport->code,airport->city,airport->state,airport->country);
}

// sets values in the AirGraph to appropriate values
//   for a new graph with numAP vertices.
void initializeAirGraph(AirGraph* graph, int numAP)
{
	graph->numVerts = numAP;
	graph->vertList = malloc(sizeof(Vertex) * graph->numVerts);
	int i;
	for(i = 0; i < numAP; i++){
		graph->vertList[i].airport = NULL;
		initializeLL(graph->vertList[i].adjList);
		graph->vertList[i].d = 0;
		graph->vertList[i].parent = NULL;
		graph->vertList[i].color = WHITE;
	}
}

// add the indicated airport to the graph vertex 
// indicated by the airport number
void insertAirport(AirGraph* graph, Airport* theAP)
{
	graph->vertList[theAP->number].airport = theAP;
}

// add the indicated route to the graph
//    return 0 if successful and 1 if unsuccessful
int insertRoute(AirGraph* graph, int startAP, int destAP)
{
	VertexLL* adj = graph->vertList[startAP].adjList;
	Vertex* newVert = &(graph->vertList[destAP]);
	if(!(insertLL(adj,newVert))){
		return 0;
	}
	else{
		return 1;
	}
}

// perform a BFS on the graph, using startAP as the source vertex
void BFS(AirGraph* graph, int startAP)
{
	int i;
	for(i = 0; i < graph->numVerts; i++){
		graph->vertList[i].d = INT_MAX;
		graph->vertList[i].parent = NULL;
		graph->vertList[i].color = WHITE;
	}
	graph->vertList[startAP].color = GRAY;
    graph->vertList[startAP].d = 0;
    graph->vertList[startAP].parent = NULL;
    VertexQ Qnew;
    VertexQ* Q = &Qnew;
    initialize(Q,graph->numVerts);
    enqueue(Q,&(graph->vertList[startAP]));
    while(!(isEmpty(Q))){
    	Vertex* u = dequeue(Q);
    	LLNode* temp = u->adjList->head;
    	while(temp != NULL){
    		if(graph->vertList[temp->data->airport->number].color == WHITE){
    			graph->vertList[temp->data->airport->number].color = GRAY;
    			graph->vertList[temp->data->airport->number].d = graph->vertList[u->airport->number].d + 1;
    			graph->vertList[temp->data->airport->number].parent = u;
    			enqueue(Q,temp->data);
    		}
    	}
    	graph->vertList[u->airport->number].color = BLACK;
    }
}

// output the airports in the shortest path from startAP to destAP
//    return 0 if successful, and 1 if an error occurs of if no such 
//    path exists
int printRoute(AirGraph* graph, int startAP, int destAP)
{
	int visits[graph->vertList[destAP].d];
	int count = 0;
	int temp = destAP;
	visits[0] = startAP;
	visits[graph->vertList[destAP].d - 1] = destAP;
	while (temp != startAP){
		temp = graph->vertList[temp].parent->airport->number;
		count++;
		visits[graph->vertList[destAP].d - 1 - count] = temp;
	}
	int i;
	for(i = 0; i < graph->vertList[destAP].d; i++){
		printAirport(graph->vertList[i].airport);
	}
	return 0;
}