#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "include/donnees.h"
#include "include/fichier.h"
#include "include/astar.h"
#include "include/affich.h"


//#define CHEMIN "annexes/images/png/"

void viderBuffer();

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Surface* ecran = NULL, *texte = NULL;
	//SDL_Surface *ecran2;
	//ecran = SDL_CreateRGBSurface(0,700,700,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
	SDL_Rect position;

	/*TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	police = TTF_OpenFont("annexes/Arial.ttf", 18);
	texte = TTF_RenderText_Blended(police, "Projet d'info !!!!!!!!!!!!!", couleurNoire);
	position.x = 10;
	position.y = 10;
	SDL_BlitSurface(texte, NULL, ecran, &position);*/
	int i;
	
	char * nomImages[NB_IMAGES] = { "M", "M1", "M2", "M3","M3b", "M4", "M5", "M6", "M7", "M7b" ,"M8", "M9", "M10", "M11", "M12", "M13", "M14"}; 
	/*char tmp[TAILLE_NOM] ="";
	SDL_Surface * tabImages[NB_IMAGES];
	for ( i = 0 ; i < NB_IMAGES ; i++ )
	{
		strcat(tmp,CHEMIN);
		strcat(tmp,nomImages[i]);
		strcat(tmp,".png");
		printf("%s\n",tmp);
		tabImages[i] = IMG_Load(tmp);
		strcpy(tmp,"");
	}

	for ( i = 0 ; i < NB_IMAGES ; i++ )
	{
		//position.x=30*i%610;
		//position.y=30*i/610;
		position.x=30*i;
		position.y=30*i;
		SDL_BlitSurfaceSecure(tabImages[i], NULL, ecran, &position);
	}*/
	//tabImage[PIETON]

	int nbStation, numDep, numArr;
	char nomDep[TAILLE_NOM], nomArr[TAILLE_NOM];
	char nom[] =  "graphes/metro2012.csv";
	Station * plan = NULL;
	puts("lecture ...");
	plan = lecture(nom, &nbStation);

	ListeRes resultat = NULL;
	ListeChangement final = NULL;

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
	afficherRes(resultat);

	puts("Changement :");
	final = traitementAffichage(resultat);
	puts("affichage");
	afficherChangement(final);
	puts("fini ...");

	
	ecran =  SDL_SetVideoMode(700, 700, 32, SDL_HWSURFACE);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	afficherSDL(ecran,nomImages, final);
	//ecran2 =  SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	//SDL_BlitSurface(ecran, NULL, ecran2, &position);
	SDL_WM_SetCaption("Metro", NULL);
	SDL_Flip(ecran);
	//SDL_Flip(ecran2);
	pause();
	//TTF_CloseFont(police);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

void viderBuffer()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}
