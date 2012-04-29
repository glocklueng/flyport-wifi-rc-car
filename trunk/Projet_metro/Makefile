
CFLAGS= -g -O2 -Wall -Wextra
LFLAGS= 

test2:  test2.o donnees.o fichier.o astar.o
	gcc -o $@ $^ $(LDFLAGS)

test1:  test1.o donnees.o fichier.o
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm *.o

.o: .c
	gcc $(CFLAGS) $<
