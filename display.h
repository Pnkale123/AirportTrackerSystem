/**
*  Header file for the Main C program
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
void displaySingleFlightData(FlightDatabase *fdatab, char const *str);
void displayAllAirports(const char * airports[]);

#endif
