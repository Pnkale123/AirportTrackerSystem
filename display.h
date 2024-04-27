/**
*  Header file for the Main C program
*  @file display.h 
*  @author Pranav Kale
*/

#ifndef DISPLAY_H
#define DISPLAY_H

void displayFlightTableRow(char flightData[][50], int rowNum);
void displayFlightTableHeader();
void clearConsole();
void displayMenuOptions(const char options[][50]);
void displaySingleFlightData(const char * flight[]);
void displayAllAirports(const char * airports[]);

#endif
