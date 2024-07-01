/**
*  Responsible for orchestrating the program, 
*  getting user input, and calling functions from other files.

*  @file Main.c 
*  @author Pranav Kale pkale 
*/

#define SUCCESS 0
#define MAX_FLIGHTS 19
#define MATCHES2 2
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "flights.h"
#include "display.h"
#include "input.h"
#include "main.h"
#include "database.h"


// Function prototypes for functions declared after main() for compilation
void loadFlightData(const char *filename, FlightDatabase *fdatab);
void collectData(const char *booking, Booking *bookingInfo);
void bookFlight(FlightDatabase *fdatab, sqlite3 *db);

/**
* Prints a message when program is given invalid arguments 
*/
static void usage()
{
    fprintf( stderr, "usage: main flight-file+\n" );
    exit(EXIT_FAILURE);
}

/**
    Starting point of program
    @param argv the number of arguments
    @param argc the arguments
*/
int main(int argc, char *argv[]) {
    printf("%d", argc - 1);
    printf(" flights uploaded to application!\n");

    if (argc < MATCHES2 || argc > MAX_FLIGHTS + 1) {
        usage();
    }
    printf("Debug1");
    FlightDatabase *fdatab = makeDatabase();

    
    for (int i = 1; i < argc; i++) {
        loadFlightData(argv[i], fdatab);
    }
    
    sqlite3 *db = initializeDatabase();
    if (db == NULL) {
        return EXIT_FAILURE;
    }
    printf("Debug2");
    char *command;

    displayApp();
    
    const char options[6][50] = {"Show Flight Table - Enter -> list \n", 
                                     "Show Flight Data - Enter -> status <flight ID>\n",
                                     "Show Airports - Enter -> list airports \n",
                                     "Book your flight - Enter -> book \n", 
                                     "Quit the Application - Enter -> quit \n",
                                     "For Help - Enter -> help commands \n"};  
printf("Debug3");
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
            free(command);
        } else if (sscanf(command, "status %s[^\n]", flightIdentifier) == 1) {
            printf("status %s\n", flightIdentifier);
            putchar('\n');
            displaySingleFlightData(fdatab, flightIdentifier);
            free(command);
        } else if (strcmp(command, "book") == 0) {
            printf("booking your flight...\n\n");
            bookFlight(fdatab, db);
            free(command);
        } else if (strcmp(command, "list airports") == 0) {
            printf("%s\n\n", command);
            displayAllAirports(fdatab);
            free(command);
        } else if (strcmp(command, "help commands") == 0) {
            printf("\n\n");
            displayMenuOptions(options);
            free(command);
        } else if (strcmp(command, "quit") == 0) { 
            putchar('\n');
            free(command);
            break;
        } else if (strcmp(command, "") == 0) {
            free(command);
        } else {
            printf("\n.------------------.\n");
            printf("| Invalid command! |\n");
            printf(".------------------.\n\n");
      
            printf("\nPlease Try Again or Enter \" help commands \" for commands.\n");
            free(command);
        }
        printf("\n");
        
    }
    sqlite3_close(db);
    freeFlightDatabase(fdatab);
    clearConsole();
    printf("Exiting the Flight Manager Application...\n\n");
        
    return EXIT_SUCCESS;
}

/**
    Load the necessary flight data into the provided database using the given file
    @param filename the file to read
    @param fdatab the database to add flight information into
*/
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

/**
  Function to convert a string to uppercase
  @param str the string to make upper case 
*/
void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

/**
  Function to get a random itinerary number
  @param itineraryNumber pointer for generation
*/
void generateItineraryNumber(char *itineraryNumber) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    itineraryNumber[0] = '#';
    for (int i = 1; i < 6; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        itineraryNumber[i] = charset[key];
    }
    itineraryNumber[6] = '\0';
}

/**
    Checks if the date string is valid
    @param date the date to check
    @return true or false if the string is valid or not
*/
bool isValidDate(const char *date) {
    int year, month, day;
    if (sscanf(date, "%4d/%2d/%2d", &year, &month, &day) != 3) {
        return false;
    }
    if (year < 1900 || year > 2050 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    return true;
}
/**
    Collects booking data from the user
    @param booking the flight ID to book
    @param bookingInfo the struct to store booking information
*/
void collectData(const char *booking, Booking *bookingInfo) {
    printf("\nHello, please Enter your First Name: \n\n");
    printf("cmd> ");
    scanf("%s[^\n]", bookingInfo->first);
    printf("Please Enter your Last Name: \n\n");
    printf("cmd> ");
    scanf("%s[^\n]", bookingInfo->last);

    printf("\nWhich Class Seat would you like? (First, Premium, or Economy) \n\n");
    printf("cmd> ");
    char classInput[10];
    scanf("%s[^\n]", classInput);
    toUpperCase(classInput);

    if (strcmp(classInput, "FIRST") == 0) {
        bookingInfo->userClass = FIRST;
    } else if (strcmp(classInput, "PREMIUM") == 0) {
        bookingInfo->userClass = PREMIUM;
    } else {
        bookingInfo->userClass = ECONOMY;
    }

    generateItineraryNumber(bookingInfo->itineraryNumber);

    do {
        printf("\nEnter your Date of Birth (YYYY/MM/DD): ");
        scanf("%s[^\n]", bookingInfo->dateOfBirth);
    } while (!isValidDate(bookingInfo->dateOfBirth));

    printf("\nAny special requests? (None, Animal, ExtraMeal, ExtraSeat, Vegetarian, Vegan, Veteran):  \n\n");
    printf("cmd> ");
    char requestInput[12];
    scanf("%s[^\n]", requestInput);
    toUpperCase(requestInput);

    if (strcmp(requestInput, "ANIMAL") == 0) {
        bookingInfo->specialRequest = ANIMAL;
    } else if (strcmp(requestInput, "EXTRAMEAL") == 0) {
        bookingInfo->specialRequest = XTRAMEAL;
    } else if (strcmp(requestInput, "EXTRASEAT") == 0) {
        bookingInfo->specialRequest = XTRASEAT;
    } else if (strcmp(requestInput, "VEGETARIAN") == 0) {
        bookingInfo->specialRequest = VEGETARIAN;
    } else if (strcmp(requestInput, "VEGAN") == 0) {
        bookingInfo->specialRequest = VEGAN;
    } else if (strcmp(requestInput, "VETERAN") == 0) {
        bookingInfo->specialRequest = VETERAN;
    } else if (strcmp(requestInput, "OTHER") == 0) {
        bookingInfo->specialRequest = OTHER;
    } else {
        bookingInfo->specialRequest = NONE;
    }
}


/**
    Books a flight for the user
    @param fdatab the flight database
    @param db the SQL Database to store inside
*/
void bookFlight(FlightDatabase *fdatab, sqlite3 *db) {
    Booking bookingInfo;
    char *flightID;

    printf("Enter the Flight ID to book: ");
    flightID = readLine(stdin);

    bool found = false;
    for (int i = 0; i < fdatab->count; i++) {
        Flight *flight = fdatab->flight[i];
        if (strcmp(flight->flightID, flightID) == 0) {
            found = true;
        }
    }
    if (!found) {
        printf("Oops! This flight was not found in our database. Try again!\n");
    } else {
        collectData(flightID, &bookingInfo);
        insertBooking(db, &bookingInfo, flightID);
        printf("\n+----------------------------------------------------+\n");
        printf("Booking confirmed for %s %s on flight %s\n", bookingInfo.first, bookingInfo.last, flightID);
        printf("Itinerary Number: %s\n", bookingInfo.itineraryNumber);
        printf("Class: %s\n", (bookingInfo.userClass == FIRST) ? "First" : (bookingInfo.userClass == PREMIUM) ? "Premium" : "Economy");
        printf("Date of Birth: %s\n", bookingInfo.dateOfBirth);
        printf("Special Request: %s\n", 
            (bookingInfo.specialRequest == NONE) ? "None" : 
            (bookingInfo.specialRequest == ANIMAL) ? "Animal" : 
            (bookingInfo.specialRequest == XTRAMEAL) ? "Extra Meal" : 
            (bookingInfo.specialRequest == XTRASEAT) ? "Extra Seat" : 
            (bookingInfo.specialRequest == VEGETARIAN) ? "Vegetarian" : 
            (bookingInfo.specialRequest == VEGAN) ? "Vegan" : "Veteran"
        );
        printf("+----------------------------------------------------+\n");
       
    }
}