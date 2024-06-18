/**
*  Header file for the Display C program
*
*  @file display.h 
*  @author Pranav Kale
*/

#include "flights.h"

#ifndef DISPLAY_H
#define DISPLAY_H

/**
    Display flight table Row for each flight stored
    @param fdatab the database of different flights
*/
void displayFlightTableRow(FlightDatabase *fdatab);

/**
    Display the flight table header for labels and information
*/
void displayFlightTableHeader();

/**
    Clear Console after usage or application feature
*/
void clearConsole();

/**
    Display the Menu options for using the Flight Manager Application
    @param options a 2D Array of all possible command options
*/
void displayMenuOptions(const char options[][50]);

/**
* Display the Header for the Airport Information to Console
*/
void dispAirportHeader();

/**
    Display data for a single flight found from flight database
    @param fdatab the database to check
    @param str the flight ID to use for display
*/
void displaySingleFlightData(FlightDatabase *fdatab, char const *str);

/**
    Display all available airports in the current flight database
    @param fdatab the database to check 
*/
void displayAllAirports(FlightDatabase *fdatab); 

/**
    Display App information on Console
*/
void displayApp();

#endif
