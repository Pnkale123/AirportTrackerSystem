#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include "flights.h"
#include "input.h"
#include "main.h"

sqlite3* initializeDatabase();
void insertBooking(sqlite3 *db, Booking *bookingInfo, const char *flightID);

#endif
