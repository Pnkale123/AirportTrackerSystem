/**
*  Responsible for orchestrating the program, 
*  getting user input, and calling functions from other files.
*  @file Main.c 
*  @author Pranav Kale pkale 
*/

#define SUCCESS 0
#define MAX_FLIGHTS 12
#define MATCHES2 2
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flights.h"
#include "display.h"
#include "input.h"

// Function prototype
void loadFlightData(const char *filename, FlightDatabase *fdatab);

void displayFlightData(Flight *flight) {
    printf("Flight ID: %s\n", flight->flightID);
    printf("Departure Airport: %s\n", flight->departureAirport);
}
/**
* Prints a message when program is given invalid arguments 
*/
static void usage()
{
    fprintf( stderr, "usage: main flight-file+\n" );
    exit(EXIT_FAILURE);
}

void displayApp() {
    printf("\n.————————————————————————————————————————————————————————————————.\n");
        printf("|  __       __     __                         __                 |\n");
        printf("|  \\ \\     / /___ | | __  ___  _ __   ___    | |_  ___           |\n");
        printf("|   \\ \\//\\/ // -_)| |/ _|/ _ \\| '  \\ / -_)   |  _|/ _ \\          |\n");
        printf("|    \\_//\\_/ \\___||_|\\__|\\___/|_|_|_|\\___|    \\__|\\___/          |\n");
        printf("|                                 _____                          |\n");
        printf("|   ___  _  _        _    _       |  \\                           |\n");
        printf("|  | __|| |(_) __ _ | |_ | |_     |   \\_________________         |\n");
        printf("|  | _| | || |/ _` || ' \\|  _|    |______         \\_____\\___     |\n");
        printf("|  |_|  |_||_|\\__, ||_||_|\\__|     \\____/__,-------,________)    |\n");
        printf("|              |___/                      \\     /                |\n");
        printf("|   __  __                                |____/__               |\n");
        printf("|  |  \\/  | __ _  _ _   __ _  __ _  ___  _ _                     |\n");
        printf("|  | |\\/| |/ _` || ' \\ / _` |/ _` |/ -_)| '_|                    |\n");
        printf("|  |_|  |_|\\__,_||_||_|\\__,_|\\__, |\\___||_|                      |\n");
        printf("|                             |___/                              |\n");
        printf(".————————————————————————————————————————————————————————————————.\n");
        printf("License and Copyright @ 2024 - Pranav Kale - pkale@ncsu.edu\n\n");
}
/**
    Starting point of program
    @param argv the number of arguments
    @param argc the arguments
*/
int main(int argc, char *argv[]) {

    if (argc < MATCHES2 || argc > MAX_FLIGHTS) {
        usage();
    }

    FlightDatabase *fdatab = makeDatabase();

    // Debugging
    for (int i = 1; i < argc; i++) {
        loadFlightData(argv[i], fdatab);
    }
    
    char *command;

    const char options[6][50] = {"Show Flight Table - Enter -> list \n", 
                                     "Show Flight Data - Enter -> status <flight ID>\n",
                                     "Show Airports - Enter -> list airports \n",
                                     "Book your flight - Enter -> book <flight ID> \n", 
                                     "Quit the Application - Enter -> quit \n",
                                     "For Help - Enter -> help commands \n"};  
    displayApp();

    displayMenuOptions(options);
    while (true) {
       
        printf("cmd> ");

        command = readLine(stdin);
        if (command == NULL) {
            break;
        } 
        
        char flightIdentifier[10];

        if (strcmp(command, "list") == 0) {
            printf("%s", command);
            printf("ing all flight information : \n\n");
            displayFlightTableHeader();
            displayFlightTableRow(fdatab);
        } else if (sscanf(command, "status %s[^\n]", flightIdentifier) == 1) {
            printf("status %s\n", flightIdentifier);
            putchar('\n');
            displaySingleFlightData(fdatab, flightIdentifier);
            free(command);
        } else if (strcmp(command, "list airports") == 0) {
            printf("%s\n\n", command);
            displayAllAirports(fdatab);
        } else if (strcmp(command, "help commands") == 0) {
            printf("%s\n\n", command);
            displayMenuOptions(options);
        } else if (strcmp(command, "quit") == 0) { 
            putchar('\n');
            free(command);
            break;
        } else {
            printf(".------------------.\n");
            printf("| Invalid command! |\n");
            printf(".------------------.\n\n");
      
            printf("\nPlease Try Again or Enter \" help commands \" for commands.\n");
            free(command);
        }
        printf("\n");
        

        // switch () {
        //     case 1:
        //         // showFlightTable(flights, MAX_FLIGHTS);
        //         break;
        //     case 2:
        //         // showFlightData(flights, MAX_FLIGHTS);
        //         break;
        //     case 3:
        //         // showAirports(flights, MAX_FLIGHTS);
        //         break;
        //     case 4:
        //         shouldQuit = 1;
        //         break;
        //     default:
        //         break;
        // }
    }

    printf("Exiting the Flight Manager Application...\n\n");
        
    return EXIT_SUCCESS;
}

void loadFlightData(const char *filename, FlightDatabase *fdatab) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    Flight *newFlight = (Flight *)malloc(sizeof(Flight)); 
    if (!getData(filename, newFlight)) {
        fprintf(stderr, "Error reading flight data from %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fdatab->flight[fdatab->count++] = newFlight;
    fclose(fp);
}