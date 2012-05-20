#include "affiche.h"

ListeChangement ajoutTete(ListeChangement liste, char l[], double c, char dep[], char arr[])
{
    ListeChangement nouveau = calloc(1, sizeof(*ListeChangement));
    if (nouveau = NULL)
    {
        perror("Problème d'allocation dynamique de mémoire\n;")
        return NULL;
    }
    else
    {
        nouveau->ligne = l;
        nouveau->cout = c;
        nouveau->nomDep = dep;
        nouveau->nomArr = arr;
        nouveau->next = liste;
        return nouveau;
    }
}

void supprimer(ListeChangement liste)
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

    char ligneAvant[TAILLE_LINE] = parcours->line;
    char stationDep[TAILLE_NOM] = parcours->line;
    double compteur = 0;

    while (parcours != NULL) // Tant qu'il y a encore des trucs dans l'astar
    {
        if(strcmp(ligneAvant,parcours->line) == 0) // Si la ligne actuelle est la même que la précédente, ce n'est pas une correspondance
        {
            compteur += parcours->coutIciToSuivant; // On incrémente alors juste le cout du changement.
        }
        else // Sinon c'est une correspondance
        {
            apres = ajoutTete(apres, ligneAvant ,compteur, stationDep, parcours->nom); // On ajoute le chagement a la liste des chagements
            compteur=0; // On remet à 0 le cout du changement
            stationDep=parcours->nom; // On sauvegarde la station de départ du prochain changement
        }
        ligneAvant = parcours->line; // On sauvegarde la ligne actuelle pour comparer avec la ligne suivante
        parcours = parcours->next;
    }
    apres = ajoutTete(apres, ligneAvant ,compteur, stationDep, parcours->nom); //Ajoute le dernier changement
    return apres;
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
