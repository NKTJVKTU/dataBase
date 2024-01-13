main.o: main.c include/main.h
	gcc -o version/main.o -c main.c

database.o: database.c include/database.h
	gcc -o version/database.o -c database.c

menu.o: menu.c include/menu.h
	gcc -o version/menu.o -c menu.c

main: main.o menu.o database.o
	gcc -std=c99 version/main.o version/database.o version/menu.o -o main