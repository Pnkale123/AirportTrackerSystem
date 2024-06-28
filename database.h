#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include "flights.h"
#include "input.h"
#include "main.h"

/**
  Initialize the database for storing bookings
  @return sqlite3 database instance
*/
sqlite3* initializeDatabase();

/**
  Insert the booking into the SQL Database
  @param db the database to access
  @param bookingInfo the booking to process
  @param flightID id of the flight
*/
void insertBooking(sqlite3 *db, Booking *bookingInfo, const char *flightID);

#endif
