#ifndef _ASTAR
#define _ASTAR

#include <stdlib.h>
#include <stdio.h>
#include "donnees.h"

/* amélioration : faire une liste triée par c*/
struct Data
{
	int num;
	double a;
	double h;
	double c;
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
Data getLowestC(ListeData open);
ListeData removeData(ListeData list ,int num);
ListeRes reconstruire(ListeSouv souv, int numDep, int numArr);
double heuristic(int numDep,int numArr,Station * plan);
ListeRes ajouterRes( ListeRes l, int num);
void suppRes(ListeRes list);
ListeSouv ajouterSouv( ListeSouv l, int numFils, int numPere);
void suppSouv(ListeSouv list);
ListeData setData(ListeData l, int num , double a , double h);
void suppData(ListeData list);
int isInListe(ListeData l,int num);
double getCscore(ListeData l,int num);
int getSouv(ListeSouv l, int num);
void afficherRes(ListeRes resultat, Station * plan);
double absDouble( double a);

#endif

