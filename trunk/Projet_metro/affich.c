#include "include/affich.h"
#define CHEMIN "annexes/images/png/"

void pause()
{
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
             case SDL_QUIT:
                 continuer = 0;
        }
    }
}


ListeChangement ajoutTeteChangement(ListeChangement liste, char l[], double c, char dep[], char arr[])
{
    ListeChangement nouveau = calloc(1, sizeof(*nouveau));
    if (nouveau == NULL)
    {
        perror("Problème d'allocation dynamique de mémoire\n");
        return NULL;
    }
    else
    {
        strcpy(nouveau->ligne,l);
        nouveau->cout = c;
        strcpy(nouveau->nomDep,dep);
        strcpy(nouveau->nomArr,arr);
        nouveau->next = liste;
        return nouveau;
    }
}

void supprimerChangement(ListeChangement liste)
{
    ListeChangement temp;
    while(liste != NULL)
    {
        temp = liste->next;
        free(liste);
        liste = temp;
    }
}

ListeChangement traitementAffichage(ListeRes avant)
{
    ListeChangement apres = NULL;
    ListeRes parcours = avant;
    char ligneAvant[TAILLE_LINE];
    strcpy(ligneAvant,parcours->line);
    char stationDep[TAILLE_NOM];
    strcpy(stationDep, parcours->nom);
    double compteur = 0;
    while (parcours != NULL) // Tant qu'il y a encore des trucs dans l'astar
    {
        if(strcasecmp(ligneAvant,parcours->line) == 0) // Si la ligne actuelle est la même que la précédente, ce n'est pas une correspondance
        {
            compteur += parcours->coutIciToSuivant; // On incrémente alors juste le cout du changement.
		
        }
        else // Sinon c'est une correspondance
        {
            apres = ajoutTeteChangement(apres, ligneAvant ,compteur, stationDep, parcours->nom); // On ajoute le chagement a la liste des chagements
            compteur=parcours->coutIciToSuivant; // On reinitailise le cout du changement
            strcpy(stationDep,parcours->nom); // On sauvegarde la station de départ du prochain changement
        }
        strcpy(ligneAvant,parcours->line); // On sauvegarde la ligne actuelle pour comparer avec la ligne suivant
	if ( parcours->next == NULL )
		break;
	else
        	parcours = parcours->next;
    }	
    apres = ajoutTeteChangement(apres, ligneAvant ,compteur, stationDep, parcours->nom); //Ajoute le dernier changement
    return apres;
}

void afficherChangement(ListeChangement l)
{
	while ( l!= NULL)
	{
		printf("%s\t%lf\t%s\t%s\n",l->ligne, l->cout, l->nomDep, l->nomArr);
		l = l->next;
	}
}

void afficherSDL(SDL_Surface *ecran, char ** nomImages, ListeChangement l)
{
	SDL_Rect position;
	puts("entree SDL");
	int i=0;
	while ( l!= NULL)
	{
		i++;
		position.x=30;
		position.y=30*i;
		char tmp[TAILLE_NOM] ="";
		int num = renvoi(nomImages,l->ligne);
		printf("%i\n", num);
		SDL_Surface * image;
		strcat(tmp,CHEMIN);
		strcat(tmp,nomImages[num]);
		strcat(tmp,".png");
		printf("%s\n",tmp);
		image = IMG_Load(tmp);
		strcpy(tmp,"");
		printf("%s\t%lf\t%s\t%s\n",l->ligne, l->cout, l->nomDep, l->nomArr);
		SDL_BlitSurface(image, NULL, ecran, &position);
		l = l->next;
	}
}

int renvoi(char * nomImages[], char * texte)
{
	int i =0;
	printf("%i", i);
	while ( strcasecmp(texte, nomImages[i]) != 0 )
	{
		printf("%i", i);
		i++;
	}
	return i;
}

int max(int a, int b)
{
	return (a>b ? a : b);
}

int SDL_BlitSurfaceSecure(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect)
{
	return SDL_BlitSurface(src, NULL, dst, dstrect);
	/*SDL_Rect position;
	position.x=0;
	position.y=0;
	SDL_Surface save = *dst;
	//calcul ///
	int w = max(dst->w,dstrect->x + dst->w);
	int h = max(dst->h,dstrect->y + dst->h);
	dst = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);
	SDL_BlitSurface(&save, NULL, dst, &position);
	SDL_BlitSurface(src, NULL, dst, dstrect);*/
}


char* getLigne(ListeChangement liste, int num)
{
    int i;
    for (i=0; i < num-1 ; i++)
        liste = liste->next;
    return liste->ligne;
}

double getCout(ListeChangement liste, int num)
{
    int i;
    for (i=0; i < num-1 ; i++)
        liste = liste->next;
    return liste->cout;
}

char* getDep(ListeChangement liste, int num)
{
    int i;
    for (i=0; i < num-1 ; i++)
        liste = liste->next;
    return liste->nomDep;
}

char* getArr(ListeChangement liste, int num)
{
    int i;
    for (i=0; i < num-1 ; i++)
        liste = liste->next;
    return liste->nomArr;
}

