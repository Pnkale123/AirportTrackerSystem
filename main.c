/**
*  Responsible for orchestrating the program, 
*  getting user input, and calling functions from other files.
*  @file Main.c 
*  @author Pranav Kale pkale 
*/

#define SUCCESS 0
#define MAX_FLIGHTS 12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "flights.h"

// Function prototype
void loadFlightData(FlightDatabase *fdatab, int maxFlights);

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
    Starting point of program
    @param argv the number of arguments
    @param argc the arguments
*/
int main(int argv, char *argc[]) {
    int shouldQuit = 0;
    int userChoice;

    // struct Flight flights[MAX_FLIGHTS];
    FlightDatabase *fdatab = makeDatabase();

    loadFlightData(fdatab, MAX_FLIGHTS);

    while (!shouldQuit) {
        const char options[4][50] = {"Show Flight Table - Enter 1\n", 
                                     "Show Flight Data - Enter 2\n",
                                     "Show Airports - Enter 3\n", 
                                     "Quit the Application - Enter 4\n"};
        displayMenuOptions(options);

        // Get user input
        printf("Enter your choice: \n");
        scanf("%d", &userChoice);
        clearInputBuffer(); // Clear input buffer

        // Validate user input
        if (userChoice < 1 || userChoice > 4) {
            printf("Invalid Option!\n");
            continue; // Skip processing and re-prompt
        }

        // Process user's choice
        switch (userChoice) {
            case 1:
                // showFlightTable(flights, MAX_FLIGHTS);
                break;
            case 2:
                // showFlightData(flights, MAX_FLIGHTS);
                break;
            case 3:
                // showAirports(flights, MAX_FLIGHTS);
                break;
            case 4:
                shouldQuit = 1;
                break;
            default:
                break;
        }
    }

    printf("Exiting the Flight Information App...\n");
    
    return EXIT_SUCCESS;
}

void loadFlightData(FlightDatabase *fdatab, int maxFlights) {
    for (int i = 0; i < maxFlights; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "flight-%d.txt", i + 1);
        if (getData(filename, *fdatab, maxFlights) != 0) {
            fprintf(stderr, "Error loading data from %s. Exiting...\n", filename);
            exit(EXIT_FAILURE);
        }
    }
}