
bin/Labyrinthe : affichage.o aleatoire.o file.o load_laby.o menu.o new_laby.o saisie.o memoire.o play.o
	gcc $^ -o $@ -lm

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

file.o : src/file.c include/head.h
	gcc -c src/file.c 
	
load_laby.o : src/load_laby.c 
	gcc -c $^

memoire.o : src/memoire.c
	gcc -c $^

play.o : src/play.c
	gcc -c $^

clean:
	rm -rf *.o