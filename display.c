/**
*  Handles functions related to displaying information on the console.
*  This could include functions for printing tables and data information.
*  @file Display.c 
*  @author Pranav Kale pkale 
*/
#include <stdio.h>
#include <stdlib.h>

/**
* Display all the flights as a row in the table based on given 2d array
* 
*/
void displayFlightTableRow(char flightData[rowNum][50], int rowNum)
{

}

/**
* Displays the Table Header for all flights
* Includes: Airline of flight, flight ID, Origin, Depart time, Arrival, Flight Total
*/
void displayFlightTableHeader() 
{
    printf("|--- Airline --- | --- ID --- | ---- Origin ---- | --- Depart Time --- | --- Arrival Time --- | --- Flight Duration --- |\n");
    printf("|----------------+------------+------------------+---------------------+----------------------+-------------------------+\n");
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
void displayMenuOptions(const char * options[]) 
{
    for (int i = 0; i < 4; i++) {
        printf("%s\n", options[i]);
    }
}

/**
*  Display specific information for One Flight (NOT A TABLE)
*  Includes ID, # of seats, engine type, Plane (Ex. Boeing 777), Pilot, 
*  Total miles, Total trips, and Operator (Ex.American Airlines)
*/
void displaySingleFlightData(const char * flight[])
{

}

/**
* Displays a table of all airports currently hosted on Application
* Includes Name of Airport, City, Country
*/
void displayAllAirports(const char * airports[])
{
    
}