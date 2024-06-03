/**
*  Header file for the Flights C program
*  @file flights.h 
*  @author Pranav Kale
*/

#include <stdbool.h>

#ifndef FLIGHTS_H
#define FLIGHTS_H

#define INITIALCAP 12
#define TABLE_SIZE 100

/** 
    Structure to store the flight details
    Includes information like date, flightID, airports, etc.
*/
typedef struct {
    char date[20];
    char flightID[10];
    char departureAirport[50];
    char departureCountry[50];
    char departTime[10];
    char arrivalTime[10];
    char arrivalAirport[50];
    int seats;
    char aircraftType[50];
    char pilot[50];
    double totalMiles;
    int totalTrips;
    char operatorName[30];
} Flight;

/**
* Structure for Flight Data base 
* Includes the Pointers to flights
* Includes the Count for tracking number of flights
* Includes the Capacity for memory usage
*/
typedef struct {
    Flight **flight;
    int count;
    int capacity;
} FlightDatabase;

/**
* AirportNode is used to store a linked list of all airports
* Includes the airport name 
* Includes a pointer to the next AirportNode
*/
typedef struct AirportNode {
    char airport[50];
    struct AirportNode *next;
} AirportNode;

/** 
* CountryNode is used to store a linked list of all countries 
* Includes the country name
* Includes a pointer to the next CountryNode
* Includes all the airports for X CountryNode
*/
typedef struct CountryNode {
    char country[50];
    AirportNode *airports;
    struct CountryNode *next;
} CountryNode;

/** 
* Hash Table is used to store buckets of Country Nodes 
* size for keeping track bucket size
*/
typedef struct {
    CountryNode **buckets;
    int size;
} HashTable;

/** 
    Creates database to store all the flights in struct
    @return a flight database struct
*/
FlightDatabase *makeDatabase();

/** 
    Get all the data for a flight 
    @param fname to store flights
    @param flight the pointer to flight struct
*/
bool getData(const char fname[], Flight *flight);

unsigned int hash(const char *str);

HashTable *createTable(int size);

void insertAirport(HashTable *table, const char *country, const char *airport);

#endif
