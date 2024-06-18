/**
*  Header file for the Main C program
*  @file main.h 
*  @author Pranav Kale
*/

#ifndef MAIN_H
#define MAIN_H

/** 
*  Enumeration for Class Types
*/
typedef enum {
  FIRST,
  PREMIUM,
  ECONOMY
} Class;

/**
*  Enumeration for any Special Requests for Client
*/
typedef enum {
    NONE,
    ANIMAL,
    XTRAMEAL,
    XTRASEAT,
    VEGETARIAN,
    VEGAN,
    VETERAN,
    OTHER
} SpecialRequest;

/**
*  Struct to define the various elements of a flight booking 
*  Includes name, class, DOB, special requests
*/
typedef struct {
    char first[20];
    char last[20];
    Class userClass;
    char itineraryNumber[7];
    char dateOfBirth[11];
    SpecialRequest specialRequest;
} Booking;


#endif 