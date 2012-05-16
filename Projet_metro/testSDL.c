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
	Station * plan = NULL;
	puts("lecture ...");
	plan = lecture(nom, &nbStation);

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
	resultat = aStar(numDep, numArr, plan);
	afficherRes(resultat);
	puts("fini ...");

	

	return 0;
}
