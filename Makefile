database.o: database.c database.h
	gcc -c database.c

database: database.o
	gcc database.o -o database