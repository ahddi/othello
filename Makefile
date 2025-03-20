##
# Othello
CC = gcc
CFLAGS = -ansi -W -Wall -pedantic -O2

othello: main.o jeu.o ui_term.o plateau.o
	gcc build/main.o build/jeu.o build/ui_term.o build/plateau.o -o bin/othello

main.o:
	$(CC) $(CFLAGS) src/main.c -o build/main.o -c

jeu.o:
	$(CC) $(CFLAGS) src/jeu.c -o build/jeu.o -c

ui_term.o:
	$(CC) $(CFLAGS) src/ui_term.c -o build/ui_term.o -c

plateau.o:
	$(CC) $(CFLAGS) src/plateau.c -o build/plateau.o -c


# end
