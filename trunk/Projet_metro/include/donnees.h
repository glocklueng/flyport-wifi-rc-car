#ifndef _DONNEES
#define _DONNEES

#include <stdlib.h>
#include <stdio.h>

#define TAILLE_NOM 512
#define TAILLE_LIGNE 16
#define TAILLE_LINE 1000


struct Arc
{
	int num;
	double cout;
	struct Arc * next;
};
typedef struct Arc Arc;
typedef struct Arc * ListeArcs;

struct Station
{
	int num;
	double lat;
	double lon;
	char nom[TAILLE_NOM];
	char line[TAILLE_LINE];
	ListeArcs arcs;
};
typedef struct Station Station;


ListeArcs ajoutTete( ListeArcs l, Arc arc);
void suppListeArcs( ListeArcs l);
void suppStation( Station * plan, int nbStation);
int estVide(ListeArcs l);
void afficherListeArcs( ListeArcs graphe );
void afficherStation( Station station );
void afficher( Station * plan , int nbStation);

#endif
