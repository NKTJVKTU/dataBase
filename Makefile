database.o: database.c database.h
	gcc -c database.c

database: database.o
	gcc -std=c99 database.o -o database