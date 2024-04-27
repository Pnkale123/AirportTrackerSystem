/**
* Input File reads input from file stream
* Used for Reading Commands from Input 
* @file input.c
* @author Pranav Kale pkale
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

/** Maximum Capacity of Line Read */
#define CAPTY 5
/** Doubling Capacity Number */
#define DOUBLE 2

/**
* Reads the input for commands, allocating space and copying lines
* @param fp the filename to read from
*/
char *readLine(FILE * fp) {
    int cap = CAPTY;
    int len = 0;
    char *line = (char *)malloc(cap * sizeof(char));
    int ch;
    // Loop through all characters in command
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        // Doubling Capacity as needed
        if (len >= cap - 1 ) {
            cap *= DOUBLE;
            char *newLine = (char *)malloc(cap * sizeof(char));
            memcpy(newLine, line, len * sizeof(char));
            free(line);
            line = newLine;
        }
        line[len++] = ch;
    }
    if (len == 0 && ch == EOF) {
        free(line);
        return NULL;
    }
    line[len] = '\0';
    return line;
}