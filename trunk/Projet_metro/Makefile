
CFLAGS= -g -O2 -Wall -Wextra
LFLAGS= -lSDL -lSDL_ttf -lSDL_image

test2:  test2.o donnees.o fichier.o astar.o
	gcc -o $@ $^

test1:  test1.o donnees.o fichier.o
	gcc -o $@ $^

testSDL:  testSDL.o donnees.o fichier.o astar.o affich.o
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm *.o

.o: .c
	gcc $(CFLAGS) $<
