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

void getData(const char fname[], struct Flight flights[], int maxFlights) {
    FILE *input = fopen(fname, "r");
    if (input == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    for (int i = 0; i < maxFlights; i++) {
        fscanf(input, "Current Date: %s", flights[i].date);
        fscanf(input, "Flight ID: %s", flights[i].flightID);
        fscanf(input, "Flight Departure Airport: %[^\n]", flights[i].departureAirport);
        fscanf(input, "Flight Departure Country: %[^\n]", flights[i].departureCountry);
        fscanf(input, "Flight Departure Time: %s", flights[i].departTime);
        fscanf(input, "Flight Arrival Time: %s", flights[i].arrivalTime);
        fscanf(input, "Flight Arrival Airport: %[^\n]", flights[i].arrivalAirport);
        fscanf(input, "Seats: %d", &flights[i].seats);
        fscanf(input, "Aircraft Type: %[^\n]", flights[i].aircraftType);
        fscanf(input, "Pilot: %[^\n]", flights[i].pilot);
        fscanf(input, "Total Miles on Plane: %lf", &flights[i].totalMiles);
        fscanf(input, "Total Trips by Plane: %d", &flights[i].totalTrips);
        fscanf(input, "Operator: %[^\n]", flights[i].operator);

        // Consume the newline character after each block
        fgetc(input);
    }

    fclose(input);
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
    // practicce comment
} 