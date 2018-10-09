#CFLAGS=-Wall -ansi -pedantic



bin/Labyrinthe : menu.o affichage.o new_laby.o saisie.o aleatoire.o
	gcc $^ -o $@

affichage.o: src/affichage.c
	gcc -c $^

menu.o: src/menu.c include/head.h
	gcc -c src/menu.c

new_laby.o: src/new_laby.c include/head.h
	gcc -c src/new_laby.c

saisie.o: src/saisie.c
	gcc -c $^

aleatoire.o : src/aleatoire.c
	gcc -c $^

clean:
	rm -rf *.o