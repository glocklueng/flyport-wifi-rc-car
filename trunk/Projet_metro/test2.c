#include <stdio.h>
#include <stdlib.h>

#include "include/donnees.h"
#include "include/fichier.h"
#include "include/astar.h"

int main()
{
	int nbStation;
	char nom[] =  "graphes/metro2012.csv";
	Station * plan = NULL;
	puts("lecture ...");
	plan = lecture(nom, &nbStation);
	puts("affichage :");
	afficher(plan, nbStation);

	ListeRes resultat = NULL;
	puts("aStar ...");
	resultat = aStar(122, 508, plan);
	afficherRes(resultat,plan);

	return 0; 
}
