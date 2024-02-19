/**
*  Responsible for orchestrating the program, 
*  getting user input, and calling functions from other files.
*  @file Main.c 
*  @author Pranav Kale pkale 
*/

#define SUCCESS 0

#include <stdio.h>
#include <stdlib.h>
#include "Display.h"
#include "Flight.h"

int main() {
    int shouldQuit = 0;
    int userChoice;

    while (!shouldQuit) {
        const char options[4][50] = {"Show Flight Table - Enter 1", 
                                     "Show Flight Data - Enter 2",
                                     "Show Airports - Enter 3", 
                                     "Quit the Application - Enter 4"};
        displayMenuOptions();

        // Get user input
        printf("Enter your choice: \n");
        scanf("%d", userChoice);
        int countFails = 0;
        while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4 ) {
            if (countFails > 4) {
                printf("You have failed options more than four times!");
                shouldQuit = 1;
                break;
            }
            printf("Invalid Option!\n");
            printf("Please Re Enter: \n");
            scanf("%d", &userChoice);
            countFails++;
        }
        // Process user's choice
       

        // Check if the user wants to quit
        if (userChoice == 4) {
            shouldQuit = 1;
        }
    }

    printf("Exiting the Flight Information App...\n");

    exit(SUCCESS);
}