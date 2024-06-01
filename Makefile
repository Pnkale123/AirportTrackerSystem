CC = gcc
CFLAGS = -Wall -std=c99 -g
LDLIBS = -lm

main: main.o flights.o display.o input.o

main.o: main.c flights.h display.h input.h

flights.o: flights.c flights.h

display.o: display.c display.h

input.o: input.c input.h

clean:
    rm -f *.o flight *.gcov *.gcda *.gcno
    rm -f output.txt
