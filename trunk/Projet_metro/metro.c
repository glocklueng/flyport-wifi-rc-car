#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "include/donnees.h"
#include "include/fichier.h"
#include "include/astar.h"
#include "include/affich.h"


void viderBuffer();

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Surface* ecran = NULL, *ecranSurface = NULL, *titre = NULL;
	TTF_Font *policeTitre = NULL;
	SDL_Color couleurNoire = {0, 0, 0, 0};
	policeTitre = TTF_OpenFont("annexes/ETHNOCEN.TTF", 18);
	if (policeTitre == NULL) puts("ttf ETHNOCEN.TTF manquante");

	SDL_Rect origine;
	origine.x = 0;
	origine.y = 0;

	char * nomImages[NB_IMAGES] = { "M", "M1", "M2", "M3","M3bis", "M4", "M5", "M6", "M7", "M7bis" ,"M8", "M9", "M10", "M11", "M12", "M13", "M14", "T1", "T2", "T3", "RA", "RB", "RC", "RD", "RE", "Val", "pieton"}; 
	
	int nbStation, numDep, numArr;
	char nomDep[TAILLE_NOM], nomArr[TAILLE_NOM];
	char nom[] =  "graphes/metro2012.csv";
	Station * plan = NULL;
	ListeRes resultat = NULL;
	ListeChangement final = NULL;

	/* lecture fichier */
	puts("lecture ...");
	plan = lecture(nom, &nbStation);

	/* demande station à l'utilisateur*/
    	puts("Choix de la station de départ :");
	fgets(nomDep,TAILLE_NOM,stdin);
	nomDep[strlen(nomDep)-1]='\0';
    	numDep = nomToNum(nomDep, plan, nbStation);

	viderBuffer();

    	puts("Choix de la station d'arrivée :");
    	fgets(nomArr,TAILLE_NOM,stdin);
	nomArr[strlen(nomArr)-1]='\0';
    	numArr = nomToNum(nomArr, plan, nbStation);

    	puts("aStar ...");
	resultat = aStar(numDep, numArr, plan);
	if (resultat == NULL)
	{
		puts("Pas de chemin possible !!!!!");
		return  0;
	}
	//afficherRes(resultat);

	puts("Changement :");
	final = traitementAffichage(resultat);
	//puts("affichage");
	//afficherChangement(final);
	puts("fini ...");

	/* surface pour l'affichage */
	ecranSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 0, 0, 32, 0, 0, 0, 0); // On créer notre surface de départ : un rectangle de taille nulle !

	/* titre */
	titre = TTF_RenderUTF8_Blended(policeTitre, "    MÉTRO Finder   ", couleurNoire);
	SDL_BlitSurfaceSecure(titre, NULL, &ecranSurface, &origine);

	/* affichage graphique du resultat */
	afficherSDL(&ecranSurface,nomImages, final);

	/* écran final */
	ecran = SDL_SetVideoMode(ecranSurface->w, ecranSurface->h, 32, SDL_HWSURFACE); // On créer la fenetre de rendu aux bonnes dimensions
	SDL_BlitSurface(ecranSurface, NULL, ecran, &origine);
	SDL_WM_SetCaption("Metro", NULL);
	SDL_Flip(ecran);
	SDL_FreeSurface(ecranSurface);
	SDL_FreeSurface(titre);
	TTF_CloseFont(policeTitre);
	pause();
	
	TTF_Quit();
	SDL_Quit();
	return 0;
}

void viderBuffer()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}
