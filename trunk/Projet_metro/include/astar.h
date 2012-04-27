#ifndef _ASTAR
#define _ASTAR

#include <stdlib.h>
#include "include/donnees.h"

struct Data
{
	int num;
	int a;
	int h;
	int c;
	struct Data * suiv;
};
typedef struct Data Data;
typedef struct Data * ListeData;

struct Souvenir
{
	int num;
	int numPere;
	//
	struct Souvenir * suiv;
};
typedef struct Souvenir * ListeSouv;

struct Res
{
	int num;
	//
	struct Res * suiv;
};
typedef struct Res * ListeRes;

#endif
