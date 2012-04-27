#include "include/fichier.h"

Station * lecture( char* nomFichier , int* nbStation)
{
	int nbArcs, numArc;
	int i;
	Arc arc;
	/* OUVERTURE DU FICHIER */
	FILE* fichier=fopen(nomFichier,"r");
	if (fichier==NULL)
	{
		perror("Erreur d'ouverture du fichier source");
		return NULL;
	}
	/* LECTURE DU NOMBRE DE STATIONS ET DU NOMBRE D'ARCS*/
	rewind(fichier);
	fscanf(fichier, "%d %d", nbStation, &nbArcs);
	/* CREATION DU GRAPHE */
	Station* plan = calloc(*nbStation,sizeof(Station));
	/* LECTURE DES STATIONS*/
	sePlacer(fichier, STATION, *nbStation, nbArcs);
	for(i=0; i<*nbStation; i++)
	{
		plan[i]=lireStation(fichier);
	}
	/* LECTURE DES ARCS */
	sePlacer(fichier, ARC, *nbStation, nbArcs);
	for(i=0; i<nbArcs; i++)
	{
		arc = lireArc(fichier,&numArc);
		plan[numArc].arcs=ajoutTete(plan[numArc].arcs,arc);
	}
	/* FERMETURE DU FICHIER */
	fclose(fichier);
	return plan;
}
Station lireStation( FILE * fichier )
{
	Station station;
	fscanf(fichier, "%d %lf %lf %s", &(station.num), &(station.lat), &(station.lon), (station.line));
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
