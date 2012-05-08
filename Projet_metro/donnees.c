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

ListeArcs suppTete( ListeArcs l )
{
	if (estVide(l))
		return  NULL;
	ListeArcs p = NULL;
	p = l->next;
	free(l);
	return p;
}
/*
void * suppTete( void * l )
{
	if (l == NULL)
		return  NULL;
	void * p = NULL;
	p = l->next;
	free(l);
	return p;
}*/
void suppListeArcs( ListeArcs l)
{
	if (estVide(l))
		return;
	ListeArcs p = l;
	while ( p != NULL )
	{
		p = suppTete(p);
		p = p->next;
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

