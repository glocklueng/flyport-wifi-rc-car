/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : fichier.c (Type : Source - Release)                                               *
 * Ce fichier regroupe toutes les fonctions assurant la lecture des fichiers CSV               *
 *                                                                                             *
 ***********************************************************************************************/

#include "include/fichier.h"

Station * lecture( char* nomFichier , int* nbStation)
{
	int nbArcs, numArc;
	int i;
	Arc arc;
	/* Ouverture du fichier */
	FILE* fichier=fopen(nomFichier,"r");
	if (fichier==NULL)
	{
		perror("Erreur d'ouverture du fichier source");
		return NULL;
	}
	/* Lecture du nombre de stations et du nombre d'arcs */
	rewind(fichier);
	fscanf(fichier, "%d %d", nbStation, &nbArcs);
	/* Creation du graphe */
	Station* plan = calloc(*nbStation,sizeof(Station));
	/* Initialisation des arcs de plan */
	for (i=0; i<*nbStation; i++)
		plan[i].arcs = NULL;
	/* Lecture des stations */
	sePlacer(fichier, STATION, *nbStation, nbArcs);
	for(i=0; i<*nbStation; i++)
	{
		plan[i]=lireStation(fichier);
	}
	/* Lecture des arcs */
	sePlacer(fichier, ARC, *nbStation, nbArcs);
	for(i=0; i<nbArcs; i++)
	{
		arc = lireArc(fichier,&numArc);
		plan[numArc].arcs=ajoutTete(plan[numArc].arcs,arc);
	}
	/* Fermeture du fichier */
	fclose(fichier);
	return plan;
}
Station lireStation( FILE * fichier )
{
	Station station;
	fscanf(fichier, "%d	%lf	%lf\t%s\t", &(station.num), &(station.lat), &(station.lon), (station.line));
	fgets(station.nom, TAILLE_NOM, fichier);
	if (station.nom[strlen(station.nom)-1]<32)
		station.nom[strlen(station.nom)-1]=0;
	return station;
}

Arc lireArc( FILE * fichier, int* numArc )
{
	Arc arc;
	fscanf(fichier, "%d %d %lf", numArc, &arc.num, &arc.cout);
	return arc;
}

void sePlacer( FILE * fichier, POSITION pos , int nbStation, int nbArcs)
{
	int i;
	char chaine[TAILLE_LINE]="";
	switch(pos)
	{
		case DEBUT:
			rewind(fichier);
			break;
		case STATION:
			rewind(fichier);
			for(i=0; i<2; i++)
				fgets(chaine, TAILLE_LINE, fichier);
			break;
		case ARC:
			rewind(fichier);
			for(i=0; i<3+nbStation; i++)
				fgets(chaine, TAILLE_LINE, fichier);
			break;
		case FIN:
			rewind(fichier);
			for(i=0; i<3+nbStation+nbArcs; i++)
				fgets(chaine, TAILLE_LINE, fichier);
			break;

	}


}
