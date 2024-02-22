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
#include "Display.h"
#include "Flight.h"

// Function prototypes
void loadFlightData(struct Flight flights[], int maxFlights);

int main() {
    int shouldQuit = 0;
    int userChoice;

    struct Flight flights[MAX_FLIGHTS];
    loadFlightData(flights, MAX_FLIGHTS);

    while (!shouldQuit) {
        const char options[4][50] = {"Show Flight Table - Enter 1\n", 
                                     "Show Flight Data - Enter 2\n",
                                     "Show Airports - Enter 3\n", 
                                     "Quit the Application - Enter 4\n"};
        displayMenuOptions();

        // Get user input
        printf("Enter your choice: \n");
        scanf("%d", &userChoice);
        int countFails = 0;
        while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4 ) {
            if (countFails > 4) {
                printf("You have failed options more than four times!\n");
                shouldQuit = 1;
                break;
            }
            printf("Invalid Option!\n");
            printf("Please Re Enter: \n");
            scanf("%d", &userChoice);
            countFails++;
        }
        // Process user's choice
        switch (userChoice) {
            case 1:
                showFlightTable(flights, MAX_FLIGHTS);
                break;
            case 2:
                showFlightData(flights, MAX_FLIGHTS);
                break;
            case 3:
                showAirports(flights, MAX_FLIGHTS);
                break;
            case 4:
                shouldQuit = 1;
                break;
            default:
                break;
        }

        // Check if the user wants to quit
        if (userChoice == 4) {
            shouldQuit = 1;
        }
    }

    printf("Exiting the Flight Information App...\n");

    exit(SUCCESS);
}

void loadFlightData(struct Flight flights[], int maxFlights) {
    for (int i = 1; i <= 12; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "flight-%d.txt", i);
        if (getData(filename, flights, maxFlights) != 0) {
            fprintf(stderr, "Error loading data from %s. Exiting...\n", filename);
            exit(EXIT_FAILURE);
        }
    }
}