
CFLAGS= -g -O2 -Wall -Wextra
LFLAGS= 


test1: donnees.o fichier.o main.o
	gcc -o $@ $^ $(LDFLAGS)

.o: .c
	gcc $(CFLAGS) $<
