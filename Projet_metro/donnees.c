/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : donnees.c (Type : Source - Release)                                               *
 * Ce fichier regroupe toutes les fonctions assurant la gestion des structures de données      *
 * représentant le graphe des stations de métro                                                *
 ***********************************************************************************************/

#include "include/donnees.h"


ListeArcs ajoutTete( ListeArcs l, Arc arc)
{
	ListeArcs p = malloc(sizeof(*p));
	if (p == NULL)
		return p;
	p->num = arc.num;
	p->cout = arc.cout;
	p->next = l;

	return p;
}


void suppListeArcs( ListeArcs list)
{
	ListeArcs buff;
    while(list != NULL)
    {
        buff = list->next;
        free(list);
        list = buff;
    }
}

void suppStation( Station * plan, int nbStation)
{
	int i;
	
	for ( i = 0 ; i < nbStation ; i++ )
	{
		suppListeArcs(plan[i].arcs);
	}
}

int estVide(ListeArcs l)
{
	if (l == NULL)
		return 1;
	else
		return 0;
}

void afficherListeArcs( ListeArcs graphe )
{
	if (estVide(graphe))
		return;
	ListeArcs p = graphe;
	while ( !estVide(p) )
	{
		printf("	%i   %lf\n",p->num,p->cout);
		p=p->next;
	}
}
void afficherStation( Station station )
{
	printf("%i  %lf   %lf   %s   %s\n",station.num, station.lat, station.lon, station.nom, station.line);
	afficherListeArcs(station.arcs);
}

void afficher( Station * plan , int nbStation)
{
	int i;
	for ( i = 0 ; i < nbStation ; i++ )
	{
		afficherStation(plan[i]);
	}
}

