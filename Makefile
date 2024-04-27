CC = gcc
CFLAGS += -Wall -std=c99 -g
LDLIBS += -lcov

main: main.o flights.o display.o input.o
	$(CC) $(CFLAGS) -o flight main.o flights.o display.o input.o $(LDLIBS)
main.o: main.c flights.h display.h input.h
	$(CC) $(CFLAGS) -c main.c
flights.o : flights.c flights.h
display.o : display.c display.h
input.o : input.c input.h
	
clean : 
	rm -f *.o flight *.gcov *.gcda *.gcno
	rm -f output.txt