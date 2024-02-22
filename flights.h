/**
*  Header file for the Flights C program
*  @file flights.h 
*  @author Pranav Kale
*/
#include "flights.c"
#ifndef FLIGHT_H
#define FLIGHT_H

struct Flight {
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
    char operator[50];
};

void getData(const char fname[], struct Flight flights[], int maxFlights);

#endif

