
bin/Labyrinthe : affichage.o aleatoire.o file.o menu.o new_laby.o saisie.o
	gcc $^ -o $@ ; make clean

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

file.o : src/file.c
	gcc -c $^ 

clean:
	rm -rf *.o