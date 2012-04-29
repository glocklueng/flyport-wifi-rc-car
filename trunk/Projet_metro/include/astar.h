#ifndef _ASTAR
#define _ASTAR

#include <stdlib.h>
#include "donnees.h"

/* amélioration : faire une liste triée par c*/
struct Data
{
	int num;
	int a;
	int h;
	int c;
	struct Data * next;
};
typedef struct Data Data;
typedef struct Data * ListeData;

struct Souvenir
{
	int num;
	int numPere;
	//truc en plus à voir
	struct Souvenir * next;
};
typedef struct Souvenir * ListeSouv;

struct Res
{
	int num;
	//truc en plus à voir
	struct Res * next;
};
typedef struct Res * ListeRes;

ListeRes aStar(int numDep, int numArr, Station * plan);
ListeRes reconstruire(ListeSouv souv, int numDep, int numArr);
int heuristic(int numDep,int numArr,Station * plan);
ListeRes ajouterRes( ListeRes l, int num);
ListeSouv ajouterSouv( ListeSouv l, int numFils, int numPere);
ListeData setData(ListeData l, int num , int a , int h);
int isInListe(ListeData l,int num);
int getCscore(ListeData l,int num);

#endif
