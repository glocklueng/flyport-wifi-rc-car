/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : test2.c (Type : Source - Test)                                                    *
 * Ce fichier est un exemple de programme test (lecture des stations & A*)                     *
 *                                                                                             *
 ***********************************************************************************************/



#include <stdio.h>
#include <stdlib.h>

#include "include/donnees.h"
#include "include/fichier.h"
#include "include/astar.h"

int main()
{
	int nbStation, numDep, numArr;
	char nomDep[TAILLE_NOM], nomArr[TAILLE_NOM];
	char nom[] =  "graphes/metro2012.csv";
	//char nom[] = "graphes/graphe1_2012.csv";
	Station * plan = NULL;
	puts("lecture ...");
	plan = lecture(nom, &nbStation);
	puts("affichage :");
	afficher(plan, nbStation);

	ListeRes resultat = NULL;
	ListeRes resultat2 = NULL;
    	puts("Choix de la station de départ :");
	gets(nomDep);
    	numDep = nomToNum(nomDep, plan, nbStation);
    	puts("Choix de la station d'arrivée :");
    	gets(nomArr);
	gets(nomArr);
    	numArr = nomToNum(nomArr, plan, nbStation);
    	puts("aStar ...");
	//resultat = aStar(121, 236, plan);
	//resultat = aStar(61, 17,plan);
	resultat = aStar(numDep, numArr, plan);
	//resultat2 = resultat->next;
	afficherRes(resultat);
	puts("fini ...");
	return 0;
}
