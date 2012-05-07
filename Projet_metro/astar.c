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

	/*On ajoute le premier point à la liste ouverte, a est donc nul*/
	open = setData(open, numDep, 0, heuristic(numDep,numArr,plan));

	/*Tant que la liste ouverte n'est pas nulle, on prend le point qui a le meilleur cout*/
	while (open != NULL)
	{
		k  = getLowestC(open);
		//puts("1");///DEBUG
        //printf("k = %i\n", k.num);
		if (k.num == numArr)//si on est arrivé
		{
		    //puts("trouve ...");///DEBUG
			res = reconstruire(souvenir, numDep, numArr);//reconstruction du chemin grace a la liste souv
			suppData(open);
			suppData(close);
			suppSouv(souvenir);
			return res;
		}
		open = removeData(open,k.num);//inutile ou pas, suivant ce que fait getLowestC()
		//puts("2"); ///DEBUG
		/*On ajoute ce point dans la liste fermée*/
		close = setData(close, k.num, k.a, k.h); //la copie de a,h et c est inutile : à améliorer par la suite

		//s = plan[k.num].arcs; // = la liste de ses fils
		//afficherListeArcs(s); ///DEBUG
		/* Pour tout les fils s de k*/
		for (s = s = plan[k.num].arcs ; s != NULL ; s = s->next)
		{
			if (isInListe(close,s->num))
				continue; //on passe au fis suivant

			tentativeCscore = k.c + s->cout;

			if (!isInListe(open,s->num))
			{
				//open = ajouterData(open ,s->num, -1, heuristic(s->num, numArr, plan)); //-1 sera defini plus tard
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

			//s = s->next;
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

ListeData removeData(ListeData list ,int num) // Par recurrence : inutile, à changer !!
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

/*ListeData removeData(ListeData list ,int num)
{
	ListeData p = list;
	ListeData tmp = NULL;
	if (p != NULL)
		return NULL;
	ListeData q = list->next;
	while (q != NULL)
	{
		if ( q->num == num )
		{
			p->next = q->next;
			free(q);

		}

		p = p->next;
		q = q->next;
	}
return list;


}*/

ListeRes reconstruire(ListeSouv souv, int numDep, int numArr)
{
    ListeRes p = NULL;
    int x;
    p = ajouterRes(p,numArr);
    x = getSouv(souv,numArr);
    p = ajouterRes(p,x);
    while ( x != numDep)
    {
        x = getSouv(souv,x);
        p = ajouterRes(p,x);
    }
    return p;
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
	//printf("heuristic : %lf\n",(absDouble(xDep-xArr)+absDouble(yDep-yArr)));///DEBUG
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

void afficherRes(ListeRes resultat, Station * plan)
{
	ListeRes p = resultat;
	Station  station;
    ListeArcs liaisons = NULL;
	while ( p != NULL)
	{
		station = plan[p->num];
		/*Affichage des données de la station*/
		printf("%i  %lf   %lf   %s   %s\n",station.num, station.lat, station.lon, station.nom, station.line);
		/*Afiichage du cout entre deux stations*/
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
            /*Et on affiche le cout*/
            printf("---->%lf\n", liaisons->cout);
        }
		p = p->next;
	}
}







