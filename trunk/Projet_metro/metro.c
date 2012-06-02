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
	SDL_Surface* ecran = NULL, *ecranSurface = NULL, *titre = NULL, *itineraire;
	TTF_Font *policeTitre = NULL, *policeItineraire = NULL;
	SDL_Color couleurNoire = {0, 0, 0, 0};
	policeTitre = TTF_OpenFont("annexes/ETHNOCEN.TTF", 45);
	policeItineraire = TTF_OpenFont("annexes/DejaVuSans.ttf", 18);
	TTF_SetFontStyle(policeItineraire, TTF_STYLE_BOLD);
	if (policeTitre == NULL) puts("ttf ETHNOCEN.TTF manquante");
	if (policeItineraire == NULL) puts("ttf DejaVuSans.ttf manquante");

	SDL_Rect origine, posTitre, posItineraire;
	origine.x = 0;
	origine.y = 0;

	char * nomImages[NB_IMAGES] = { "M", "M1", "M2", "M3","M3bis", "M4", "M5", "M6", "M7", "M7bis" ,"M8", "M9", "M10", "M11", "M12", "M13", "M14", "T1", "T2", "T3", "RA", "RB", "RC", "RD", "RE"}; 
	
	int nbStation, numDep, numArr;
	char nomDep[TAILLE_NOM], nomArr[TAILLE_NOM], tmp[TAILLE_NOM*2];
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

	/* surface pour l'affichage */
	ecranSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 0, 0, 32, 0, 0, 0, 0); // On créer notre surface de départ : un rectangle de taille nulle !

	strcpy(tmp,"");
	if (resultat != NULL)
	{
		
		//afficherRes(resultat);

		puts("Changement :");
		final = traitementAffichage(resultat);
		//puts("affichage");
		//afficherChangement(final);
		puts("fini ...");

		/* affichage graphique du resultat */
		afficherSDL(&ecranSurface,nomImages, final);

		/* titre */
		titre = TTF_RenderUTF8_Blended(policeTitre, "Métro", couleurNoire);
		posTitre.y = 0;
		posTitre.x = abs(ecranSurface->w - titre->w)/2;
		SDL_BlitSurfaceSecure(titre, NULL, &ecranSurface, &posTitre);
		sprintf(tmp,"Itinéraire de %s à %s",plan[numDep].nom,plan[numArr].nom);
		itineraire = TTF_RenderUTF8_Blended(policeItineraire, tmp, couleurNoire);
		posItineraire.y = 80;
		posItineraire.x = 90;
		SDL_BlitSurfaceSecure(itineraire, NULL, &ecranSurface, &posItineraire);


	}
	else
	{
		/* titre */
		SDL_Color couleurRouge = {255, 0, 0, 0};
		sprintf(tmp,"Métro : %s à %s ",plan[numDep].nom,plan[numArr].nom);
		titre = TTF_RenderUTF8_Blended(policeTitre, tmp, couleurNoire);
		SDL_BlitSurfaceSecure(titre, NULL, &ecranSurface, &origine);	
		posTitre.x = 0;
		posTitre.y = titre->h;
		titre = TTF_RenderUTF8_Blended(policeTitre,"Il n'y a pas de resultat : Chemin impossible !!!", couleurRouge);
		SDL_BlitSurfaceSecure(titre, NULL, &ecranSurface, &posTitre);	


	}

	/* écran final */
	ecran = SDL_SetVideoMode(ecranSurface->w, ecranSurface->h, 32, SDL_HWSURFACE); // On créer la fenetre de rendu aux bonnes dimensions
	SDL_BlitSurface(ecranSurface, NULL, ecran, &origine);
	SDL_WM_SetCaption("Metro", NULL);
	SDL_Flip(ecran);
	SDL_FreeSurface(ecranSurface);
	SDL_FreeSurface(titre);
	TTF_CloseFont(policeTitre);
	TTF_CloseFont(policeItineraire);
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
