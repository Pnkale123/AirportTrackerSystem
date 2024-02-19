/**
*  Contains functions for calculations and operations related to flights. 
*  This could involve calculating distances, updating flight information, etc.
*  @file Flight.c 
*  @author Pranav Kale pkale 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double calculateAverageMilesPerFlight(double miles, int trips) {
    double average = (double) miles / trips;
    return average;
}

/**
* Uses military time value to determine flight time total 
* Arrival minus the Departing Time and return a text about time of flight
* Example: the string for depart is "12:33 PM" the string for arrival is "18:19 PM"
* Take 18:19 PM and 12:33 PM
* Returns a time like this: "5 hours and 14 minutes.""
*/
char* calculateFlightTime(const char departTime[], const char arrivalTime[]) 
{
    int departHour, departMinutes, arrivalHour, arrivalMinutes;
    // if the value is AM then true, if it is PM then false;
    sscanf(departTime, "%d:%d", &departHour, &departMinutes);
    sscanf(arrivalTime, "%d:%d", &arrivalHour, &arrivalMinutes);

    bool isDepartPM = (departTime[strlen(departTime) - 2] == 'P');
    bool isArrivalPM = (arrivalTime[strlen(arrivalTime) - 2] == 'P');

    if (isDepartPM) {
        departHour += 12;
    }

    if (isArrivalPM) {
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
    return time;
}

/**
* Calculate the total revenue of the flight
* Take the number of seats and multiply by fixed price
*/
double calculateTotalRevenue(int numSeats, double pricePerSeat)
{
    double price = numSeats * pricePerSeat;
    return price;
}