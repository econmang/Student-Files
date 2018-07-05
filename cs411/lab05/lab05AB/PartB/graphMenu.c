/*
   graphMenu.c: interactive graph data structure test program

   CS411 Lab 5
   Name: Evan Conley
   Date: March 18, 2017
*/

#include "airGraph.h"

// read-in an airport graph from inFileName
// note this function is only partially complete
void getGraphInput (AirGraph* graph, const char* inFileName)
{
   //// open the input file to read-in the graph ////
   FILE* inFile = fopen(inFileName, "r");
   if (!inFile) 
   {
      fprintf(stderr, "ERROR: file %s does not exist.\n", inFileName);
      exit(1);
   }

   // read-in the number of airports using fscanf.
   // note that fscanf takes an extra argument, which specifies
   //    the stream to read from
   int numAirports;
   if (fscanf(inFile, "%d", &numAirports) != 1)
   {
      fprintf(stderr, "ERROR: parsing file %s.\n", inFileName);
      exit(1);
   }


   ///// fill-in code to read-in remainder of input here, building 
   ///// the graph as vertices and edges are read-in 
   initializeAirGraph(graph,numAirports);
   int i;
   int tempNum;
   char tempCode[3];
   char tempCity[25];
   char tempState[2];
   char tempCountry[15];

   for(i = 0; i < numAirports; i++){
      fscanf(inFile, "%d %s %s %s %s",&tempNum,tempCode,tempCity,tempState,tempCountry);
      Airport* newAir = createAirport(tempNum, tempCode, tempCity,tempState, tempCountry);
      insertAirport(graph,newAir);
   }

   int numFlights;
   if (fscanf(inFile, "%d", &numFlights) != 1){
      fprintf(stderr, "ERROR: parsing file %s.\n", inFileName);
      exit(1);
   }
   int fliNum;
   int start;
   int end;
   for(i = 0; i < numFlights; i++){
      fscanf(inFile, "%d %d %d", &fliNum, &start, &end);
      insertRoute(graph,start,end);
   }

   // close the open file after finished reading
   fclose(inFile);
}

// helper function
int getAirportNum (const char* prompt)
{
   int id;
   printf("%s: ", prompt);
   while (!scanf("%d", &id))
   {
      printf("ERROR: please enter an integer id: ");
      scanf("%*s");
   }

   return id;
}

int main (int argc, char* argv[])
{
   // first check for correct number of cla's
   // argv[1] should be the input file name
   if (argc != 2)
   {
      fprintf(stderr, "usage: %s airGraphInputFile\n", argv[0]);
      exit(1);
   }

   ///// fill-in remainder of main function here /////
   AirGraph newG;
   AirGraph* graph = &newG;
   getGraphInput (graph, argv[1]);

   int airStart;
   int again = 1;
   do {

      printf("\n** AIRPORT GRAPH MENU **\n");
      printf("1. Enter Starting Airport\n");
      printf("2. Enter Destination Airport\n");
      printf("3. Quit\n");
      printf("* Enter your choice (1-3):  \n");

      int choice = -1;
      while (!scanf("%d", &choice))
      {
         scanf("%*s");
         printf("ERROR: please enter a number (1-3): \n");
      }

      switch (choice)
      {
         case 1: // Input Start Airport 
         {
            printf("Enter vertex number of starting airport: ");
            if(scanf("%d",&airStart) != 1){
               printf("ERROR: invalid vertex value.\n");
               exit(1);
            }
            else{
               BFS(graph,airStart);
            }
         }   
         case 2: // Input Destination
            if(airStart){
               printRoute(graph,airStart,getAirportNum("Enter Vertex Number of Destination Airport: "));
            }
            else{
               printf("ERROR: give a valid starting airport.");
            }
            break;

         case 3: // Quit
         {
           printf("You have chosen QUIT\n");
           again = 0;
           break;
         }

         default:
            printf("ERROR: only choices 1-3 are valid.\n");
            break;
      }

   } while (again);
   
   return 0;
}