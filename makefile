#CFLAGS=-Wall -ansi -pedantic

Labyrinthe : menu.o affichage.o new_laby.o saisie.o 
	gcc $^ -o $@

affichage.o: affichage.c
	gcc -c $^

menu.o: menu.c head.h
	gcc -c menu.c

new_laby.o: new_laby.c head.h
	gcc -c $^

saisie.o: saisie.c
	gcc -c $^

clean:
	rm -rf *.o