/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : fichier.h (Type : Header - Release)                                               *
 * Prototypes des fonctions du fichier source "fichier.c"                                      *
 *                                                                                             *
 ***********************************************************************************************/


#ifndef _FICHIER
#define _FICHIER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "donnees.h"

enum POSITION { DEBUT, STATION, ARC, FIN };
typedef enum POSITION POSITION;

Station* lecture( char* nomFichier , int* nbStation); // Fonction principale de lecture du fichier
Station lireStation( FILE * fichier ); // Fonction qui lit une ligne du fichier correspondant a une station
Arc lireArc( FILE * fichier, int* numArc ); // Fonction qui lit une ligne du fichier correspondant a un arc
void sePlacer( FILE * fichier, POSITION pos , int nbStation, int nbArcs); // Fonction qui permet de se placer a des endroits stratégiques du fichier pour une lecture plus rapide

#endif
