#ifndef _ASTAR
#define _ASTAR

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "donnees.h"

#define TAILLE_LISTE_PROPOSITION 5

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
	double lat;
	double lon;
	char nom[TAILLE_NOM];
	char line[TAILLE_LINE];
	double coutIciToSuivant;
	int correspondance;

	struct Res * next;
};
typedef struct Res * ListeRes;

struct SearchName
{
    int prob;
    char nom[TAILLE_NOM];
    int num;
};
typedef struct SearchName SearchName;

ListeRes aStar(int numDep, int numArr, Station * plan);
Data getLowestC(ListeData open);
ListeData removeData(ListeData list ,int num);
ListeRes reconstruire(ListeSouv souv, int numDep, int numArr, Station* plan);
ListeRes completer(ListeRes resultat, Station * plan);
ListeRes simplifier( ListeRes resultat );
double heuristic(int numDep,int numArr,Station * plan);
ListeRes ajouterRes(ListeRes l, int num);
ListeRes setRes(ListeRes l, int num , double lat, double lon, char nom[TAILLE_NOM], char line[TAILLE_LINE], double coutIciToSuivant, int correspondance);
ListeRes suppTeteRes( ListeRes l );
ListeRes suppQueueRes( ListeRes l );
void suppRes(ListeRes list);
ListeSouv ajouterSouv( ListeSouv l, int numFils, int numPere);
void suppSouv(ListeSouv list);
ListeData setData(ListeData l, int num , double a , double h);
void suppData(ListeData list);
int isInListe(ListeData l,int num);
double getCscore(ListeData l,int num);
int getSouv(ListeSouv l, int num);
void afficherRes(ListeRes resultat);
double absDouble( double a);

int nomToNum( char * nom, Station * plan , int nbStation);
void triABulles(SearchName * tab, int taille);
void swap(SearchName * a, SearchName * b);
int sontDifferents(SearchName * best, char * nom);

#endif

