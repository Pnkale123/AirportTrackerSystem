/**
*  Responsible for orchestrating the program, 
*  getting user input, and calling functions from other files.
*  @file Main.c 
*  @author Pranav Kale pkale 
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    while (!shouldQuit) {
        const char options[4][50] = {"Show Flight Table - 1", 
                                     "Show Flight Data - 2",
                                     "Show Airports - 3", 
                                     "Quit the Application - 4"};
        displayMenuOptions();

        // Get user input
        printf("Enter your choice: ");
        scanf("%s", userChoice);

        // Process user's choice
       

        // Check if the user wants to quit
        if (strcmp(userChoice, "4") == 0) {
            shouldQuit = 1;
        }
    }

    printf("Exiting the Flight Information App...\n");

    exit(SUCCESS);
}