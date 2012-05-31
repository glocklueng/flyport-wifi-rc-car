DIRSDL=/users/prog1a/C/librairie/2011

CFLAGS=-g -O2 -Wall -Wextra -I$(DIRSDL)/include 
LFLAGS=$(LFLMAC) -g -L$(DIRSDL)/lib -L/usr/local/lib -lSDL -lSDL_ttf -lSDL_image

metro:  metro.o donnees.o fichier.o astar.o affich.o
	gcc -o $@ $^ $(LFLAGS)

test2:  test2.o donnees.o fichier.o astar.o
	gcc -o $@ $^

test1:  test1.o donnees.o fichier.o
	gcc -o $@ $^

testSDL:  testSDL.o donnees.o fichier.o astar.o affich.o
	gcc -o $@ $^ $(LFLAGS)

clean:
	rm *.o

.o: .c
	gcc -c $(CFLAGS) $<
