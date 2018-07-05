/*
   airport.h: header file for an airport

   CS411 Lab #:5
   Name: Evan Conley   
   Date: March 18, 2017
*/

#ifndef AIRPORT_H
#define AIRPORT_H

#define MAX_AIRPORT_STR_LEN   50
#define AIRPORT_CODE_LEN      3
#define STATE_LEN             2

typedef struct
{
   int number;
   char code[AIRPORT_CODE_LEN + 1];
   char city[MAX_AIRPORT_STR_LEN + 1];
   char state[STATE_LEN + 1];
   char country[MAX_AIRPORT_STR_LEN + 1];

} Airport;

/*** Airport function prototypes ***/
Airport* createAirport(int number, const char* code, const char* city, 
            const char* state, const char* country);
void printAirport(const Airport* airport);

#endif /* AIRPORT_H */