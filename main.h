/**
*  Header file for the Main C program
*  @file main.h 
*  @author Pranav Kale
*/

#ifndef MAIN_H
#define MAIN_H

typedef enum {
  FIRST,
  PREMIUM,
  ECONOMY
} Class;

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

typedef struct {
    char first[20];
    char last[20];
    Class userClass;
    char itineraryNumber[7];
    char dateOfBirth[11];
    SpecialRequest specialRequest;
} Booking;


#endif 