/**
*  Contains functions for calculations and operations related to flights. 
*  This could involve calculating distances, updating flight information, etc.
*  @file Flight.c 
*  @author Pranav Kale pkale 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "flights.h"

/**
* Constructs an Inventory Structure 
* Dynamically Allocates Memory
* @return recordInventory the newly allocated inventory
*/
FlightDatabase *makeDatabase() 
{
    FlightDatabase *flightdb = (FlightDatabase *) malloc(sizeof(FlightDatabase));
    flightdb->flight = (Flight **) malloc(INITIALCAP * sizeof(Flight *));
    flightdb->count = 0;
    flightdb->capacity = INITIALCAP;
    return flightdb;
}

bool getData(const char fname[], Flight *flight) {
    FILE *input = fopen(fname, "r");
    printf("filename: 2 %s", fname);
    if (input == NULL) {
        perror("Error opening file");
        return false;
    }

    fscanf(input, "Current Date: %[^\n]\n", flight->date);
    fscanf(input, "Flight ID: %[^\n]\n", flight->flightID);
    fscanf(input, "Flight Departure Airport: %[^\n]\n", flight->departureAirport);
    fscanf(input, "Flight Departure Country: %[^\n]\n", flight->departureCountry);
    fscanf(input, "Flight Departure Time: %[^\n]\n", flight->departTime);
    fscanf(input, "Flight Arrival Time: %[^\n]\n", flight->arrivalTime);
    fscanf(input, "Flight Arrival Airport: %[^\n]\n", flight->arrivalAirport);
    fscanf(input, "Seats: %d\n", &flight->seats);
    fscanf(input, "Aircraft Type: %[^\n]\n", flight->aircraftType);
    fscanf(input, "Pilot: %[^\n]\n", flight->pilot);
    fscanf(input, "Total Miles on Plane: %lf\n", &flight->totalMiles);
    fscanf(input, "Total Trips by Plane: %d\n", &flight->totalTrips);
    fscanf(input, "Operator: %[^\n]\n", flight->operator);

    fclose(input);


    return true;
}


double calculateAverageMilesPerFlight(double miles, int trips) {
    double average = (double) miles / trips;
    return average;
}

/**
* Uses military time value to determine flight time total 
* Arrival minus the Departing Time and return a text about time of flight
* Example: the string for depart is "12:33 PM" the string for arrival is "03:19 PM"
* Take 03:19 PM and 12:33 PM
* Returns a time like this: "2 hours and 52 minutes.""
*/
char* calculateFlightTime(const char departTime[], const char arrivalTime[]) 
{
    int departHour, departMinutes, arrivalHour, arrivalMinutes;
    char departFormat[3], arrivalFormat[3];

    sscanf(departTime, "%d:%d %2s", &departHour, &departMinutes, departFormat);
    sscanf(arrivalTime, "%d:%d %2s", &arrivalHour, &arrivalMinutes, arrivalFormat);

    // Convert to 24-hour format if needed
    if (strcmp(departFormat, "PM") == 0 && departHour < 12) {
        departHour += 12;
    }

    if (strcmp(arrivalFormat, "PM") == 0 && arrivalHour < 12) {
        arrivalHour += 12;
    }
    
    int totalMinutes = (arrivalHour * 60 + arrivalMinutes) - (departHour * 60 + departMinutes);

    if (totalMinutes < 0) {
        totalMinutes += 24 * 60;
    }

    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;

    char* time = (char*)malloc(30);
    // Format the result
    sprintf(time, "%d hours and %d minutes", hours, minutes);
    free(time);
    return time;
}

/**
* Calculate the total revenue of the flight
* Take the number of seats and multiply by fixed price
*/
double calculateTotalRevenue(int numSeats, double pricePerSeat)
{
    // Calculate price of seats using fixed price
    double price = numSeats * pricePerSeat;
    return price;
} 

/**
 * Calculate the number of remaining seats on a flight.
 * Takes the total number of seats and the number of seats booked.
 * Returns the remaining number of seats.
 */
int calculateRemainingSeats(int totalSeats, int seatsBooked) {
    int remainingSeats = totalSeats - seatsBooked;
    return (remainingSeats >= 0) ? remainingSeats : 0;
}