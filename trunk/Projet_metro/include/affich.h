#ifndef _AFFICH
#define _AFFICH

#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "astar.h"
#include "donnees.h"

#define CHEMIN "annexes/images/png/"
#define NB_IMAGES 25

struct Changement
{
        char ligne[TAILLE_LIGNE];
        double cout;
        char nomDep[TAILLE_NOM];
        char nomArr[TAILLE_NOM];
	struct Changement * next;
	
};
typedef struct Changement * ListeChangement;

enum Type { METRO, TRAM, RER, ORLY };
typedef enum Type Type;

void pause();
int renvoi(char * nomImages[], char * texte);
Type determinerType(char * nom);
void afficherSDL(SDL_Surface **ecran, char ** nomImages, ListeChangement l);

ListeChangement traitementAffichage(ListeRes resultat);

ListeChangement ajoutQueueChangement(ListeChangement liste, char l[], double c, char dep[], char arr[]);
void supprimerChangement(ListeChangement liste);
void afficherChangement(ListeChangement l);
int max(int a, int b);
int SDL_BlitSurfaceSecure(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface **dst, SDL_Rect *dstrect);

char* getLigne(ListeChangement liste, int num);
double getCout(ListeChangement liste, int num);
char* getDep(ListeChangement liste, int num);
char* getArr(ListeChangement liste, int num);


#endif
