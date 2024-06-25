CC = gcc
CFLAGS += -Wall -std=c99 -g
LDLIBS += -lm -lsqlite3

main: main.o flights.o display.o input.o database.o

main.o: main.c flights.h display.h input.h database.h

flights.o: flights.c flights.h

display.o: display.c display.h input.h

input.o: input.c input.h

database.o: database.c database.h

clean : 
	rm -f *.o flight *.gcov *.gcda *.gcno
	rm -f output.txt