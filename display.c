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

/**
* Display all the flights as a row in the table based on given 2d array
* 
*/
void displayFlightTableRow(FlightDatabase *fdatab)
{
  for (int i = 0; i < fdatab->count; i++) {
        Flight *flight = fdatab->flight[i];
        printf("| %-21s | %-5s | %-21s | %-10s | %-9s | %-20s |\n",
               flight->operator,
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
            printf("Flight found:\n");
            printf("Flight ID: %s\n", flight->flightID);
            printf("Departure Airport: %s\n", flight->departureAirport);
            // Add other flight data here if needed
            break;
        }
    }
    if (!exists) {
        printf("Unknown Flight ID, please Re-Enter.\n\n");
    }
}

/**
* Displays a table of all airports currently hosted on Application
* Includes Name of Airport, City, Country
*/
void displayAllAirports(const char * airports[])
{
    
}