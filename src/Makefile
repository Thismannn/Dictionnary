# -*- Makefile -*-

all: run

run: dico
	./dico pg31469.txt WITH

dico: dico.o lire.o arbre.o recherche.o chrono.o
	gcc dico.o lire.o arbre.o recherche.o chrono.o -o dico -l m
	
dico.o: dico.c lire.h arbre.h recherche.h chrono.h
	gcc -c dico.c
	
lire.o: lire.c lire.h
	gcc -c lire.c
	
arbre.o: arbre.c arbre.h recherche.h
	gcc -c arbre.c
	
recherche.o: recherche.c recherche.h arbre.h
	gcc -c recherche.c
	
chrono.o: chrono.c chrono.h
	gcc -c chrono.c
	
clean:
	rm -f *.o dico

.PHONY: all run