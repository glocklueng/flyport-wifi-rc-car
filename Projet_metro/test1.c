/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : test1.c (Type : Source - Test)                                                    *
 * Ce fichier est un exemple de programme test (lecture des stations)                          *
 *                                                                                             *
 ***********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "include/donnees.h"
#include "include/fichier.h"

int main()
{
	int nbStation;
	char nom[] =  "graphes/metro2012.csv";
	Station * plan = NULL;
	puts("lecture ...");
	plan = lecture(nom, &nbStation);
	puts("affichage :");
	afficher(plan, nbStation);

	return 0; 
}
