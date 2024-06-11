/**
*  Header file for the Main C program
*
*  @file display.h 
*  @author Pranav Kale
*/

#include "flights.h"

#ifndef DISPLAY_H
#define DISPLAY_H

void displayFlightTableRow(FlightDatabase *fdatab);
void displayFlightTableHeader();
void clearConsole();
void displayMenuOptions(const char options[][50]);
/**
* Display the Header for the Airport Information to Console
*/
void dispAirportHeader();
void displaySingleFlightData(FlightDatabase *fdatab, char const *str);
/**
    Display all available airports in the current flight database
    @param fdatab the database to check 
*/
void displayAllAirports(FlightDatabase *fdatab); 
void displayApp();

#endif
