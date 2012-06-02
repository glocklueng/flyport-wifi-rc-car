/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : affich.c (Type : Source - Release)                                                *
 * Ce fichier regroupe toutes les fonctions assurant le rendu visuel de l'application aussi    *
 * bien sur la console qu'en SDL                                                               *
 ***********************************************************************************************/

#include "include/affich.h"

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

ListeChangement ajoutQueueChangement(ListeChangement liste, char l[], double c, char dep[], char arr[])
{
     ListeChangement nouveau = calloc(1, sizeof(*nouveau));
     ListeChangement p = liste;
     if (nouveau == NULL)
     {
         perror("Problème d'allocation dynamique de mémoire\n");
         return NULL;
     }
	strcpy(nouveau->ligne,l);
     nouveau->cout = c;
     strcpy(nouveau->nomDep,dep);
     strcpy(nouveau->nomArr,arr);
	if ( liste == NULL )
	{
		nouveau->next = NULL;
		return nouveau;
	}
	while ( p->next != NULL )
	{
		p = p->next;
	}
     
	p->next = nouveau;
	nouveau->next = NULL;
     return liste;
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
            apres = ajoutQueueChangement(apres, ligneAvant ,compteur-360, stationDep, parcours->nom); // On ajoute le chagement a la liste des chagements
		  apres = ajoutQueueChangement(apres, "pieton" ,360, ligneAvant, parcours->line); //la corespondance
            compteur=parcours->coutIciToSuivant; // On reinitailise le cout du changement
            strcpy(stationDep,parcours->nom); // On sauvegarde la station de départ du prochain changement
		  
        }
        strcpy(ligneAvant,parcours->line); // On sauvegarde la ligne actuelle pour comparer avec la ligne suivant
	if ( parcours->next == NULL )
		break;
	else
        	parcours = parcours->next;
    }	
    apres = ajoutQueueChangement(apres, ligneAvant ,compteur, stationDep, parcours->nom); //Ajoute le dernier changement
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

void afficherSDL(SDL_Surface **ecran, char ** nomImages, ListeChangement l)
{
	SDL_Rect position, position2, posTexte2;
	SDL_Surface *texte = NULL;
	SDL_Surface * image = NULL;

	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0, 0};
	police = TTF_OpenFont("annexes/DejaVuSans.ttf", 18);
	if (police == NULL) puts("ttf DejaVuSans.ttf manquante");

	int i=0;
	char tmp[TAILLE_NOM] ="";
	char tcout[10] ="";
	int num;
	Type type;
	double coutTotal = 0;
	while ( l!= NULL)
	{
		i++;
		coutTotal =coutTotal + l->cout;
		position.x=1;
		position.y=30*(i-1) + 110;
		position2.x=28;
		position2.y=30*(i-1) +110;
		posTexte2.x=60;
		posTexte2.y=30*(i-1) + 3 + 110; 
		type = determinerType(l->ligne);
		if ( type == RER )
		{
			strcpy(tmp,"R0");
			tmp[1] = l->ligne[0];
			num = renvoi(nomImages,tmp);
			strcpy(tmp,"");
		}
		else
			num = renvoi(nomImages,l->ligne);

		/* Icône de type */
		strcat(tmp,CHEMIN);
		if ( type == METRO )
			strcat(tmp,"M");
		else if (type == TRAM)
			strcat(tmp,"T");
		else if (type == RER)
			strcat(tmp,"R");
		else if (type == ORLY)
			strcat(tmp,"Val");
		else if (type == FUNI)
			strcat(tmp,"funi");
		else
			strcat(tmp,"pieton");

		strcat(tmp,".png");
		image = IMG_Load(tmp);
		if ( image == NULL ) printf("Erreur à l'ouvertue de %s\n",tmp);
		strcpy(tmp,"");
		SDL_BlitSurfaceSecure(image, NULL, ecran, &position);
		SDL_FreeSurface(image);

		/* Icône numéro */
		if ( type != ORLY && type != FUNI && type != CORRES)
		{
			strcat(tmp,CHEMIN);
			strcat(tmp,nomImages[num]);
			strcat(tmp,".png");
			image = IMG_Load(tmp);
			if ( image == NULL ) printf("Erreur à l'ouvertue de %s\n",tmp);
			strcpy(tmp,"");
			
			SDL_BlitSurfaceSecure(image, NULL, ecran, &position2);
			SDL_FreeSurface(image);

		}

		/* Texte */
		if ( type != CORRES )
		{
			strcat(tmp," Prendre le ");
			if (type == RER)
				strcat(tmp,"RER ");
			else if (type == ORLY)
				strcat(tmp,"Orly");
			strcat(tmp,l->ligne);
			if (type == FUNI)
				strcat(tmp,"culaire");
			strcat(tmp," de ");
			strcat(tmp,l->nomDep);
			strcat(tmp," à ");
			strcat(tmp,l->nomArr);
			strcat(tmp,". Temps estimé : environ ");
			sprintf(tcout, "%i",arrondi(l->cout/60));
			strcat(tmp,tcout);
			strcat(tmp," minutes ");
			printf("Prendre la ligne %s pendant %i min, de %s à %s\n",l->ligne, arrondi(l->cout/60), l->nomDep, l->nomArr);
		}
		else
		{
			strcat(tmp," Correspondance pour ligne ");
			if (strcasecmp(l->nomArr,"Val") == 0)
				strcat(tmp,"Orly");
			strcat(tmp,l->nomArr);
			strcat(tmp," environ ");
			sprintf(tcout, "%i",arrondi(l->cout/60));
			strcat(tmp,tcout);
			strcat(tmp," minutes ");
			printf("Correspondance pour ligne %s pendant %i min\n",l->nomArr, arrondi(l->cout/60));
		}

		texte = TTF_RenderUTF8_Blended(police, tmp, couleurNoire);
		SDL_BlitSurfaceSecure(texte, NULL, ecran, &posTexte2);
		SDL_FreeSurface(texte);
		strcpy(tmp,"");
		strcpy(tcout,"");

		l = l->next;
	}

	posTexte2.x += 30;
	posTexte2.y += 30; 
	strcat(tmp," Temps total : ");
	strcpy(tcout,"");
	sprintf(tcout, "%i",arrondi(coutTotal/60));
	strcat(tmp,tcout);
	strcat(tmp," minutes ");
	TTF_SetFontStyle(police, TTF_STYLE_BOLD);
	texte = TTF_RenderUTF8_Blended(police, tmp, couleurNoire);
	SDL_BlitSurfaceSecure(texte, NULL, ecran, &posTexte2);
	SDL_FreeSurface(texte);
	TTF_CloseFont(police);
}

int renvoi(char * nomImages[], char * texte)
{
	int i =0;
	while ( strcasecmp(texte, nomImages[i]) != 0 )
	{
		i++;
		if ( i > NB_IMAGES-1 ) return NB_IMAGES-1;
	}
	return i;
}

Type determinerType(char * nom)
{
	if ( nom[0] == 'M' )
		return METRO;
	else if ( nom[0] == 'T')
		return TRAM;
	else if ( nom[0] == 'A' || nom[0] == 'B' || nom[0] == 'C'|| nom[0] == 'D'|| nom[0] == 'E' )
		return RER;
	else if ( nom[0] == 'V')
		return ORLY;
	else if (strcasecmp(nom,"funi") == 0)
		return FUNI;
	else
		return CORRES;

}

int arrondi(double d)
{
	return (((double)(d-(int)d) > 0.5)?(int)d+1:(int)d);
}


int max(int a, int b)
{
        return ( a>b ? a : b );
}

int SDL_BlitSurfaceSecure(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface **dst, SDL_Rect *dstrect)
{
        SDL_Surface *nouveau = NULL;
        SDL_Rect origine;
        int w,h;
        int output;

        origine.x=0;
        origine.y=0;
        w=max((*dst)->w, dstrect->x+src->w);
        h=max((*dst)->h, dstrect->y+src->h);

        nouveau = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);
        SDL_FillRect(nouveau, NULL, SDL_MapRGB(nouveau->format, 255, 255, 255));
        output=SDL_BlitSurface(*dst, NULL, nouveau, &origine);
        output*=SDL_BlitSurface(src, NULL, nouveau, dstrect);

        SDL_FreeSurface(*dst);
        *dst = nouveau; 
        return output;
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

