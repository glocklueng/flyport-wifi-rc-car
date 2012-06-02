/***********************************************************************************************
 * Projet Métro                                                                                *
 * Grenoble INP - Phelma 2011/2012 - PET C                                                     *
 * Florian TAVARES & Jérémy FANGUEDE                                                           *
 *                                                                                             *
 * Fichier : astar.c (Type : Source - Realease)                                                *
 * Ce fichier regroupe toutes les fonctions nécéssaires au calcul du trajet en utilisant       *
 * l'algorithme astar                                                                          *
 ***********************************************************************************************/

#include "include/astar.h"

ListeRes aStar(int numDep, int numArr, Station * plan)
{
	ListeData open = NULL, close = NULL;
	Data k;
	ListeArcs s = NULL;
	ListeRes res = NULL;
	ListeSouv souvenir = NULL;
	double tentativeCscore;
	int tentativeIsBetter;

	/* On ajoute le premier point à la liste ouverte, a est donc nul */
	open = setData(open, numDep, 0, heuristic(numDep,numArr,plan));

	/* Tant que la liste ouverte n'est pas nulle, on prend le point qui a le meilleur cout */
	while (open != NULL)
	{
		k  = getLowestC(open);

		if (k.num == numArr) //Si on est arrivé
		{

			res = reconstruire(souvenir, numDep, numArr,plan); //Reconstruction du chemin grace a la liste souv
			suppData(open);
			suppData(close);
			suppSouv(souvenir);
			return res;
		}
		open = removeData(open,k.num); //Inutile ou pas, suivant ce que fait getLowestC()

		/* On ajoute ce point dans la liste fermée */
		close = setData(close, k.num, k.a, k.h); 

		/* Pour tout les fils s de k */
		for (s = plan[k.num].arcs ; s != NULL ; s = s->next)
		{
			if (isInListe(close,s->num))
				continue; //On passe au fis suivant

			tentativeCscore = k.c + s->cout;

			if (!isInListe(open,s->num))
			{
				tentativeIsBetter = 1;
			}
			else if (tentativeCscore < getCscore(open,s->num))
			{
				tentativeIsBetter = 1;
			}
			else
			{
				tentativeIsBetter = 0;
			}

			if (tentativeIsBetter)
			{
				souvenir = ajouterSouv(souvenir, s->num, k.num);
				open = setData(open, s->num, tentativeCscore, heuristic(s->num, numArr, plan));
			}
		}
	}
	return NULL;
}

Data getLowestC(ListeData open)
{
    ListeData p = open;
    Data dataMin = *p;
    double cMin = p->c;
    while (p != NULL)
    {
        if ( p->c < cMin)
        {
			cMin = p->c;
			dataMin = *p;
	}
        p = p->next;
    }
    return dataMin;
}

ListeData removeData(ListeData list ,int num)
{
	if(list == NULL)
        return NULL;

    	if(list->num == num)
    	{
      	ListeData  tmp = list->next;
        	free(list);
        	tmp = removeData(tmp, num);
        	return tmp;
    	}
   	 else
    	{
      	list->next = removeData(list->next, num);
        	return list;
    	}
}

ListeRes reconstruire(ListeSouv souv, int numDep, int numArr, Station * plan)
{
   	ListeRes p = NULL;
    	int x;
    	p = ajouterRes(p,numArr);
    	if ( numDep == numArr)
    	{
		p = completer(p, plan);
        	return p;
    	}
    	x = getSouv(souv,numArr);
    	p = ajouterRes(p,x);
    	while ( x != numDep)
    	{
      	x = getSouv(souv,x);
        	p = ajouterRes(p,x);
    	}
    	p = completer(p, plan);
    	p = simplifier(p);
    	return p;
}


ListeRes completer(ListeRes resultat, Station * plan)
{
	ListeRes p = resultat;
	Station  station;
    	ListeArcs liaisons = NULL;

    

	while ( p != NULL)
	{
		station = plan[p->num];
        	if (p->next != NULL)
        	{
            		liaisons = plan[p->num].arcs;
           		/*On se place au bon endroit sur la liste des arcs*/
           		while (liaisons != NULL)
            		{
                		if ( liaisons->num == p->next->num)
                    			break;
                			liaisons = liaisons ->next;
            		}
            		setRes(p, p->num, station.lat, station.lon, station.nom, station.line, liaisons->cout);
			p = p->next;
        	}
       		else
        	{
        		setRes(p, p->num, station.lat, station.lon, station.nom, station.line, 0);
			break;
        	}
		
	}
	return resultat;

}

ListeRes simplifier( ListeRes resultat )
{
	if ( resultat == NULL || resultat->next == NULL)
		return resultat;
	ListeRes p =resultat;

	/* Suppression correspondance inutile au départ */
	while(strcasecmp(resultat->nom,(resultat->next)->nom) == 0)
    	{
      		resultat = suppTeteRes(resultat);
    	}
	/* Simplifier correspondance inutile à l'arrivée */
	if (resultat->next == NULL || resultat->next->next ==  NULL)
		return resultat;
	while ( p->next->next != NULL )
	{
		p = p->next;
	}
	if (strcasecmp(p->nom,(p->next)->nom) == 0)
	{
		resultat = suppQueueRes(resultat);
	}
	return resultat;

}


double absDouble( double a)
{
	if (a <0)
		return -a;
	else
		return a;
}

double heuristic(int numDep,int numArr,Station * plan)
{
	double xDep,yDep,xArr,yArr;
	xDep = plan[numDep].lat;
	yDep = plan[numDep].lon;
	xArr = plan[numArr].lat;
	yArr = plan[numArr].lon;
	return (absDouble(xDep-xArr)+absDouble(yDep-yArr))/2;
}

ListeRes ajouterRes( ListeRes l, int num)
{
	ListeRes p = malloc(sizeof(*p));
	if (p == NULL)
		return p;
	p->num = num;
	p->next = l;

	return p;
}

ListeRes suppTeteRes( ListeRes l )
{
	if (l == NULL)
		return  NULL;
	ListeRes p = NULL;
	p = l->next;
	free(l);
	return p;
}

ListeRes suppQueueRes( ListeRes l )
{
	if ( l == NULL || l->next == NULL )
	{
		free(l);
		return NULL;
	}
	ListeRes s = l;
	ListeRes p = l->next;
	while ( p->next != NULL )
	{
		s = s->next;
		p = p->next;
	}
	free(p);
	s->next = NULL;
	return l;
}

ListeRes setRes(ListeRes l, int num , double lat, double lon, char nom[TAILLE_NOM], char line[TAILLE_LINE], double coutIciToSuivant)
{
	ListeRes p = l;
	while ( p != NULL )
	{
		if ( p->num == num)
		{
			p->lat = lat;
			p->lon = lon;
			strcpy(p->nom, nom);
			strcpy(p->line, line);
			p->coutIciToSuivant = coutIciToSuivant;
			return l;
		}
		p = p->next;
	}
    return l;
}

void suppRes(ListeRes list)
{
	ListeRes buff;
    while(list != NULL)
    {
        buff = list->next;
        free(list);
        list = buff;
    }

}

ListeSouv ajouterSouv( ListeSouv l, int numFils, int numPere)
{
	ListeSouv p = malloc(sizeof(*p));
	if (p == NULL)
		return p;
	p->num = numFils;
	p->numPere = numPere;
	p->next = l;

	return p;
}

void suppSouv(ListeSouv list)
{
	ListeSouv  buff;
    while(list != NULL)
    {
        buff = list->next;
        free(list);
        list = buff;
    }

}

ListeData setData(ListeData l, int num , double a , double h)
{
	ListeData p = l;
	while ( p != NULL )
	{
		if ( p->num == num)
		{
			p->a = a;
			p->h = h;
			p->c = a+h;
			return l;
		}
		p = p->next;
	}

	ListeData nouveau = (ListeData)malloc(sizeof(*nouveau));
	nouveau->num = num;
	nouveau->a =a;
	nouveau->h = h;
	nouveau->c = a + h;
	nouveau->next = l;
	return nouveau;
}

void suppData(ListeData list)
{
	ListeData buff;
    while(list != NULL)
    {
        buff = list->next;
        free(list);
        list = buff;
    }

}

int isInListe(ListeData l,int num)
{
	ListeData p = l;
	while (p != NULL)
	{
		if ( p->num == num )
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

double getCscore(ListeData l,int num)
{
	ListeData p = l;
	while ( p != NULL)
	{
		if ( p->num == num)
		{
			return p->c;
		}
		p = p->next;
	}
	return -1;
}

int getSouv(ListeSouv l, int num)
{
	ListeSouv p = l;
	while ( p != NULL)
	{
		if ( p->num == num)
		{
			return p->numPere;
		}
		p = p->next;
	}
	return -1;

}

void afficherRes(ListeRes resultat)
{
	ListeRes p = resultat;
	while ( p != NULL)
	{
		/* Affichage des données de la station */
		printf("%i  %lf   %lf   %s   %s\n",p->num, p->lat, p->lon, p->nom, p->line);
        	printf("---->%lf\n", p->coutIciToSuivant);

		p = p->next;
	}
}

int nomToNum( char * nom, Station * plan , int nbStation)
{
    int i,choix;
    int* proba = calloc(nbStation,sizeof(*proba));
    SearchName best[TAILLE_LISTE_PROPOSITION];

    /* Initialisation du tableau de resemblances */
    for ( i = 0 ; i <  nbStation ; i++)
    {
        proba[i] = abs(strncasecmp(nom,plan[i].nom,strlen(nom)));
    }
    /* Initialisation du tableau des 5 meilleures ressemblances */
    for ( i = 0 ; i <  TAILLE_LISTE_PROPOSITION ; i++)
    {
        best[i].prob = proba[i];
        best[i].num = i;
        strcpy(best[i].nom,plan[i].nom);
    }
    triABulles(best,TAILLE_LISTE_PROPOSITION);
    /* Recherche des 5 meilleures ressemblances */
    for ( i = 5 ; i <  nbStation ; i++)
    {
        if (proba[i] < best[TAILLE_LISTE_PROPOSITION-1].prob && sontDifferents(best,plan[i].nom))
        {
            best[TAILLE_LISTE_PROPOSITION-1].prob = proba[i];
            best[TAILLE_LISTE_PROPOSITION-1].num = i;
            strcpy(best[TAILLE_LISTE_PROPOSITION-1].nom,plan[i].nom);
            triABulles(best,TAILLE_LISTE_PROPOSITION);
        }
    }
    /* Affichage des 5 meilleures avec choix */
    for ( i = 0 ; i < TAILLE_LISTE_PROPOSITION ; i++)
    {
        printf("%i:  %s\n",i,best[i].nom);
    }
    /* Demande du choix */
    scanf("%i",&choix);
    if (choix < 0 || choix > TAILLE_LISTE_PROPOSITION-1)
    {
		printf("choix invalide, valeur par defaut : 0");  
		choix = 0;
    }
    /* libération mémoire */
    free(proba);
    /* Retour du numéro correspondant */
    return best[choix].num;
}

void triABulles(SearchName * tab, int taille)
{
    int fini = 0;
    int i;
    while(!fini)
    {
        fini = 1;
        for(i=0 ; i < taille-1 ; i++)
        {
            if(tab[i].prob > tab[i+1].prob)
            {
                swap(&tab[i],&tab[i+1]);
                fini = 0;
            }
        }
        taille--;
    }
}

void swap(SearchName * a, SearchName * b)
{
    SearchName tmp = *a;
    *a = *b;
    *b = tmp;
}

int sontDifferents(SearchName * best, char * nom)
{
    int i;
    for (i = 0 ; i < TAILLE_LISTE_PROPOSITION ; i++)
    {
        if (strcasecmp(best[i].nom,nom) == 0)
            return 0;
    }
    return 1;
}






