#ifndef _FICHIER
#define _FICHIER

#include "donnees.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum POSITION { DEBUT, STATION, ARC, FIN };
typedef enum POSITION POSITION;

Station* lecture( char* nomFichier , int* nbStation);
Station lireStation( FILE * fichier );
Arc lireArc( FILE * fichier, int* numArc );
void sePlacer( FILE * fichier, POSITION pos , int nbStation, int nbArcs);



#endif
