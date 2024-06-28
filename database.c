#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "database.h"

/**
  Initialize the database for storing bookings
  @return sqlite3 database instance
*/
sqlite3* initializeDatabase() {
    sqlite3 *db;
    int rc = sqlite3_open("flights.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    
    // Create bookings table if it doesn't exist
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS Bookings ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "FirstName TEXT NOT NULL,"
        "LastName TEXT NOT NULL,"
        "Class TEXT NOT NULL,"
        "ItineraryNumber TEXT NOT NULL,"
        "DateOfBirth TEXT NOT NULL,"
        "SpecialRequest TEXT NOT NULL,"
        "FlightID TEXT NOT NULL);";

    char *errMsg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return NULL;
    }
    
    return db;
}

/**
  Insert the booking into the SQL Database
  @param db the database to access
  @param bookingInfo the booking to process
  @param flightID id of the flight
*/
void insertBooking(sqlite3 *db, Booking *bookingInfo, const char *flightID) {
    char *errMsg = 0;
    char sql[512];
    
    snprintf(sql, sizeof(sql), 
        "INSERT INTO Bookings (FirstName, LastName, Class, ItineraryNumber, DateOfBirth, SpecialRequest, FlightID) "
        "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s');", 
        bookingInfo->first, 
        bookingInfo->last, 
        (bookingInfo->userClass == FIRST) ? "First" : (bookingInfo->userClass == PREMIUM) ? "Premium" : "Economy", 
        bookingInfo->itineraryNumber, 
        bookingInfo->dateOfBirth, 
        (bookingInfo->specialRequest == NONE) ? "None" : 
        (bookingInfo->specialRequest == ANIMAL) ? "Animal" : 
        (bookingInfo->specialRequest == XTRAMEAL) ? "Extra Meal" : 
        (bookingInfo->specialRequest == XTRASEAT) ? "Extra Seat" : 
        (bookingInfo->specialRequest == VEGETARIAN) ? "Vegetarian" : 
        (bookingInfo->specialRequest == VEGAN) ? "Vegan" : "Veteran", 
        flightID);
    
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Booking successfully inserted into the database.\n");
    }
}
