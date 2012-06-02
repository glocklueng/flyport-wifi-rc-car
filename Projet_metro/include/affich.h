/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : affich.h (Type : Header - Release)                                                *
 * Prototypes des fonctions du fichier source "affich.c"                                       *
 *                                                                                             *
 ***********************************************************************************************/

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

enum Type { METRO, TRAM, RER, ORLY, FUNI, CORRES };
typedef enum Type Type;

/* Fonctions de structure de ListeChangement */
ListeChangement ajoutQueueChangement(ListeChangement liste, char l[], double c, char dep[], char arr[]);
void supprimerChangement(ListeChangement liste);
void afficherChangement(ListeChangement l);

/* Fonction d'adaptation du rendu A* */
ListeChangement traitementAffichage(ListeRes resultat); // Fonctionne qui convertit le rendu AStar (itinéraire point à point) en un itinéraire "ligne à ligne"

/* Fonctions SDL */
void afficherSDL(SDL_Surface **ecran, char ** nomImages, ListeChangement l); // Fonction principale d'affichage
void pause(); // Fonction d'attente de fermeture de la fenêtre principale
Type determinerType(char * nom); // Fonction qui détermine le type de ligne associé à la chaîne ligne du CSV
int renvoi(char * nomImages[], char * texte); // ??
int SDL_BlitSurfaceSecure(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface **dst, SDL_Rect *dstrect); // Fonction qui fait l'équivalent de la fonction SDL éponyme mais en s'assurant que l'image destination peut accueillir l'image source (en l'agrandissant si tel n'est pas le cas)

/* Accesseurs éléments de la ListeChangement*/
char* getLigne(ListeChangement liste, int num);
double getCout(ListeChangement liste, int num);
char* getDep(ListeChangement liste, int num);
char* getArr(ListeChangement liste, int num);

/* Divers */
int arrondi(double d);
int max(int a, int b);

#endif
