CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lm

all: jeu

jeu: main.o joueur.o jeu.o carte.o gestionjeu.o
	$(CC) $(CFLAGS) -o jeu main.o joueur.o jeu.o carte.o gestionjeu.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

joueur.o: joueur.c
	$(CC) $(CFLAGS) -c joueur.c

jeu.o: jeu.c
	$(CC) $(CFLAGS) -c jeu.c

carte.o: carte.c
	$(CC) $(CFLAGS) -c carte.c

gestionjeu.o: gestionjeu.c
	$(CC) $(CFLAGS) -c gestionjeu.c

clean:
	rm -f *.o jeu
