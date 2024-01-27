CC = g++
CFLAGS = -std=c++2a -Wall -Wextra -pedantic -g 

main: main.o helper.o 
	$(CC) -o main main.o helper.o 

main.o: main.cpp helper.h
	$(CC) $(CFLAGS) -c main.cpp

helper.o: helper.cpp helper.h
	$(CC) $(CFLAGS) -c helper.cpp

clean :
	rm -f main depend.mak *.o
	rm -r -f *.dSYM