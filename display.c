/**
*  Handles functions related to displaying information on the console.
*  This could include functions for printing tables and data information.
*  @file Display.c 
*  @author Pranav Kale pkale 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h> 
#include "display.h"
#include "flights.h"
#include "input.h"

int compareCountries(const void *a, const void *b) {
    return strcmp((*(CountryNode **)a)->country, (*(CountryNode **)b)->country);
}

/**
* Display all the flights as a row in the table based on given 2d array
* 
*/
void displayFlightTableRow(FlightDatabase *fdatab)
{
  for (int i = 0; i < fdatab->count; i++) {
        Flight *flight = fdatab->flight[i];
        printf("| %-21s | %-5s | %-21s | %-10s | %-9s | %-20s |\n",
               flight->operatorName,
               flight->flightID,
               flight->departureAirport,
               flight->departTime,
               flight->arrivalTime,
               flight->arrivalAirport);
  }
}

/**
* Displays the Table Header for all flights
* Includes: Airline of flight, flight ID, Origin, Depart time, Arrival, Flight Total
*/
void displayFlightTableHeader() 
{
    printf("|        Airline        |   ID  |        Origin         |  Departed  |  Arrival  |      Destination     |\n");
    printf("|-----------------------+-------+-----------------------+------------+-----------+----------------------+\n");
}

/**
* Clears the console for the user 
* This is called every time user runs one of the show methdos 
* Called after show flight table option, show flight data option, show airports
*/
void clearConsole()
{
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif
}

/**
* Display's all the menu options to user
*/
void displayMenuOptions(const char options[][50]) 
{
    for (int i = 0; i < 6; i++) {
        printf("%s\n", options[i]);
    }
}

/**
*  Display specific information for One Flight (NOT A TABLE)
*  Includes ID, # of seats, engine type, Plane (Ex. Boeing 777), Pilot, 
*  Total miles, Total trips, and Operator (Ex.American Airlines)
*/
void displaySingleFlightData(FlightDatabase *fdatab, char const *str) {
    bool exists = false;
    for (int i = 0; i < fdatab->count; i++) {
        Flight *flight = fdatab->flight[i];
        if (strcmp(flight->flightID, str) == 0) {
            exists = true;
            printf("Flight found!\n\n");
            printf("[FLIGHT DATE]: %s\n", flight->date);
            printf("\n.------------------------------------------------------.\n");
            int val = 25 - strlen(flight->operatorName) - strlen(flight->flightID);
            printf("|%s %s", flight->operatorName, flight->flightID);
            for (int i = 0; i < val; i++) {
                putchar(' ');
            }
            printf("|                           |\n");
            printf("|                          |                           |\n");
            printf("|                        .-'-.                         |\n");
            printf("|                       ' === '                        |\n");
            printf("|                \\-----'  .-.  '-----/                 |\n");
            printf("|    ——————————————————'  '-'  '————————————————————   |\n");
            printf("|      '''''-|--/   \\==^'--T--'^==//   \\--|-'''''      |\n");
            printf("|               \\___/      O       \\___/               |\n");
            printf("|                                                      |\n");
            printf(".------------------------------------------------------.\n");
            printf("\nFlight Departing At: %s\n", flight->departTime);
            printf("Flight Arriving At: %s\n", flight->arrivalTime);
            printf("-------------------------\n");
            printf("Departure Airport: %s\n", flight->departureAirport);
            printf("Arrival Airport: %s\n", flight->arrivalAirport);
            printf("-------------------------\n");
            printf("Pilot Name: %s\n", flight->pilot);
            printf("Seats Available: %d\n", flight->seats);
            printf("Aircraft Type: %s\n", flight->aircraftType);
            printf("-------------------------\n");
            printf("\nEnter \" more data \" for additional information.\n\n");
            while (true) {
                printf("cmd> ");
                char * adding;
                adding = readLine(stdin);
                if (strcmp(adding, "more data") == 0) {
                   
                    double avgMile = calculateAverageMilesPerFlight(flight->totalMiles, flight->totalTrips);
                    char *fTime = calculateFlightTime(flight->departTime, flight->arrivalTime);
                    printf("\nThis plane's average miles per trip: %.2f miles\n", avgMile);
                    printf("Total Travel Duration is %s\n", fTime);
                    free(fTime); // Freeing the allocated memory
                }
                break;
            }

            break;
        }
    }
    if (!exists) {
        printf("Unknown Flight ID, please Re-Enter.\n\n");
    }
}

void dispAirportHeader() 
{
    printf("|     Country     |        Airport        |\n");
    printf("|-----------------+-----------------------+\n");
}

void displayAllAirports(FlightDatabase *fdatab) {
    HashTable *table = createTable(TABLE_SIZE);

    for (int i = 0; i < fdatab->count; i++) {
        Flight *flight = fdatab->flight[i];
        insertAirport(table, flight->departureCountry, flight->departureAirport);
    }

    // Collect all countries into an array for sorting
    CountryNode *countryArray[table->size];
    int countryCount = 0;

    for (int i = 0; i < table->size; i++) {
        CountryNode *node = table->buckets[i];
        while (node != NULL) {
            countryArray[countryCount++] = node;
            node = node->next;
        }
    }

    // Sort the array of countries
    qsort(countryArray, countryCount, sizeof(CountryNode *), compareCountries);

    // Print the sorted list of countries and their airports
    dispAirportHeader();
    for (int i = 0; i < countryCount; i++) {
        CountryNode *countryNode = countryArray[i];
        AirportNode *airportNode = countryNode->airports;
        while (airportNode != NULL) {
            printf("| %-15s | %-21s |\n",
                   countryNode->country,
                   airportNode->airport);
            airportNode = airportNode->next;
        }
    }

    freeHashTable(table);
}

void displayApp() {
    printf("\n.————————————————————————————————————————————————————————————————.\n");
        printf("|  __       __     __                         __                 |\n");
        printf("|  \\ \\     / /___ | | __  ___  _ __   ___    | |_  ___           |\n");
        printf("|   \\ \\//\\/ // -_)| |/ _|/ _ \\| '  \\ / -_)   |  _|/ _ \\          |\n");
        printf("|    \\_//\\_/ \\___||_|\\__|\\___/|_|_|_|\\___|    \\__|\\___/          |\n");
        printf("|                                 _____                          |\n");
        printf("|   ___  _  _        _    _       |  \\                           |\n");
        printf("|  | __|| |(_) __ _ | |_ | |_     |   \\_________________         |\n");
        printf("|  | _| | || |/ _` || ' \\|  _|    |______         \\_____\\___     |\n");
        printf("|  |_|  |_||_|\\__, ||_||_|\\__|     \\____/__,-------,________)    |\n");
        printf("|              |___/                      \\     /                |\n");
        printf("|   __  __                                |____/__               |\n");
        printf("|  |  \\/  | __ _  _ _   __ _  __ _  ___  _ _                     |\n");
        printf("|  | |\\/| |/ _` || ' \\ / _` |/ _` |/ -_)| '_|                    |\n");
        printf("|  |_|  |_|\\__,_||_||_|\\__,_|\\__, |\\___||_|                      |\n");
        printf("|                             |___/                              |\n");
        printf(".————————————————————————————————————————————————————————————————.\n");
        printf("License and Copyright @ 2024 - Pranav Kale - pkale@ncsu.edu\n\n");
}
